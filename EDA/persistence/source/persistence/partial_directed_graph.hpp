#ifndef SOURCE_PERSISTENCE_PARTIAL_DIRECTED_GRAPH_HPP_
#define SOURCE_PERSISTENCE_PARTIAL_DIRECTED_GRAPH_HPP_

#include <utility>
#include <iostream>
#include <limits>



namespace ADE {
namespace Persistence {
//////////////////////////////////
// foward declaration para crear la tabla de modificaciones
template <typename Type>
class PartialNode;
/////////////////////////////////

template <typename Type, typename Node = PartialNode<Type>>
class TableMods{
public:
    int version;
    int tamanho;
    int indice;
    std::pair<Type, Node*> *table;

    TableMods(){}
    TableMods(int cant){
        table = new std::pair<Type, Node*>[cant];
        tamanho = cant;
        indice = 0;
        for(int i=0; i<cant; ++i)
            table[i] = std::pair<Type, Node*>(0, nullptr);
    }

    void setValue(Type const data){
        table[indice].first = data;
        indice++;
        tamanho--;
    }

    void setPointer(Node* u){
        table[indice].second = u;
        indice++;
        tamanho--;
    }

    bool size_(){
        return tamanho>0;
    }

};


template <typename Type>
class PartialNode {
 public:
  typedef Type data_type;

  PartialNode() {}

  PartialNode(data_type const& data, std::size_t const& out_ptrs_size,
              std::size_t const& in_ptrs_size) :
              data_(new data_type(data)), out_ptrs_size_(out_ptrs_size), in_ptrs_size_(in_ptrs_size)
               {

    forward_ = new PartialNode<Type>*[out_ptrs_size]();
    backward_ = new PartialNode<Type>*[in_ptrs_size]();
  }

  data_type get_data(unsigned int version) { return *data_; }

  bool set_data(data_type const& data) { 
    data_ = data;
    return true; 
  }

  // insertar un vertice en la ultima version
  PartialNode* insert_vertex(std::size_t const& position,
                             data_type const& data) {

    std::cout << ":'c se pierde un puntero no es justo :'( " <<std::endl;
    if (this->out_ptrs_size_ != out_ptrs_size_) {
      throw std::logic_error("Node with different number of out pointers.");
    }
    if (out_ptrs_size_ < position) {
      throw std::out_of_range("Insert position out of node edges range.");
    }

    PartialNode* new_node = new PartialNode(data, out_ptrs_size_, in_ptrs_size_);
    update_edge(position, new_node);
    return new_node; 
  }

  bool update_edge(std::size_t const& position, PartialNode* v) { 
    if (out_ptrs_size_ < position && in_ptrs_size_ < position) {
          throw std::out_of_range("Insert position is out of edges range.");
      }

    forward_[position] = v;
    v->backward_[position] = this;
    std::cout<< "test :x"<<std::endl;
    return true;    
    
  }

  PartialNode& operator[](
      std::pair<std::size_t, unsigned int> const& position_version) const {

        if(out_ptrs_size_ < position_version.first){
          throw std::out_of_range("Index out of node edges range.");
        }
        if(forward_[position_version.first]){
          throw std::logic_error("Access to null reference.");
        }
        
        // return *forward_[position_version.first];
        return *forward_[position_version.first];
  }

  data_type* data_;
  std::size_t out_ptrs_size_;
  PartialNode** forward_;

  std::size_t in_ptrs_size_;
  std::size_t current_modifications_size_;
  std::size_t current_back_pointer_size_;

  PartialNode** backward_;
  // TODO: Table mods, 2 * in_ptrs_size_

  TableMods<Type> mods;
  unsigned int version_nodo;
};

template <typename Type, typename Node>
class PartialDirectedGraph {
 public:
  typedef Type data_type;

  PartialDirectedGraph(data_type const data, 
                        std::size_t const& out_ptrs_size,
                       std::size_t const& in_ptrs_size) : root_ptr_(new Node(data, out_ptrs_size, in_ptrs_size)) {
                         out_ptrs_size_ = out_ptrs_size;
                         in_ptrs_size_ = in_ptrs_size;
                         *current_version_ = 0;
                       }

  Node* get_root_ptr(unsigned int const& version) { 
    return root_ptr_;
  }

  Node get_root(unsigned int const& version) { 
    return *root_ptr_;
  }

  Node* insert_vertex(data_type const data, Node* u, std::size_t position) {
    ++(*current_version_);
    return u->insert_vertex(position, data);
  }

  bool add_edge(Node* u, Node* v, std::size_t position) {
    ++(*current_version_);
    if (u->out_ptrs_size_ < position) {
      throw std::out_of_range("Position out of first argument node.");
    }
    u->update_edge(position, v);
    return true;
  }


 protected:
  unsigned int* current_version_;
  std::size_t in_ptrs_size_;

  Node* root_ptr_;
  std::size_t out_ptrs_size_;
};

}  // namespace Persistence
}  // namespace ADE

#endif  // SOURCE_PERSISTENCE_PARTIAL_DIRECTED_GRAPH_HPP_