// Copyright
#ifndef SOURCE_B_LINK_HPP_
#define SOURCE_B_LINK_HPP_

#include <bits/stdc++.h>

namespace EDA {
namespace Concurrent {

template  <std::size_t B, typename Type> 
class BLinkNode {
  public:
    typedef Type data_type;
    typedef BLinkNode<B,Type> Node;  
    data_type* keys_;
    int size_arr_data_;
    Node** childs_ptr_;
    Node* right_ptr_;
    Node* aux_ptr_;
    Node* parent_;
    std::mutex barrier;
    bool locked;

    BLinkNode(Node* parent){
      size_arr_data_ = 0;
      keys_ = new data_type[B + 1];
      childs_ptr_ = new Node*[B + 2];
      right_ptr_ = nullptr;
      aux_ptr_ = nullptr;
      parent_ = parent;
      locked = false;
    }

    BLinkNode(){
      size_arr_data_ = 0;
      keys_ = new data_type[B + 1];
      childs_ptr_ = new Node*[B + 2];
      right_ptr_ = nullptr;
      aux_ptr_ = nullptr;
      parent_ = nullptr;
      locked = false;
    }

    bool leaf(Node* root)  {
      for( short i = 0 ; i <= B ; ++i)
        if( root->childs_ptr_[i] )
          return false;
      return true;
    }

    void sortKeys(Node* root) {
      data_type temp;
      for( short i = 0; i < root->size_arr_data_; ++i)
        for( short j = 0; j < root->size_arr_data_- i - 1; ++j)
          if(root->keys_[j] > root->keys_[j + 1]) {
            temp = root->keys_[j];
            root->keys_[j] = root->keys_[j+1];
            root->keys_[j+1] = temp;
          }
    }

    void sortPtrs(Node* root) {
      Node* temp;
      for(short i = 0; i <= root->size_arr_data_; ++i)
        for(short j = 0; j <= root->size_arr_data_ - i - 1; ++j)
          if(root->childs_ptr_[j]->keys_[0] > root->childs_ptr_[j + 1]->keys_[0])  {
            temp = root->childs_ptr_[j];
            root->childs_ptr_[j] = root->childs_ptr_[j + 1];
            root->childs_ptr_[j + 1] = temp;
          }
    }

    void addKey(data_type key) {
      this->keys_[this->size_arr_data_++] = key;
      sortKeys(this);
      if( !leaf(this) )
        sortPtrs(this);
      if( this->size_arr_data_ <= B)
        this->unlock();
    }

    // checar pensarlo despues
    void splitAddKey(Node* child,int k1,int k2) {
      for( short i = k1; i <= k2; ++i)
        child->keys_[child->size_arr_data_++] = this->keys_[i];
    }

    void splitAddPtr(Node* child,int k1,int k2) {
      short i = 0;
      for( short j = k1; j <= k2; ++j )
        child->childs_ptr_[i++]=this->childs_ptr_[j];
      if( !leaf(child) )
        for(i = 0; i <= child->size_arr_data_; i++)
          child->childs_ptr_[i]->parent_ = child;
    }

    void removePtr(Node* root) {
      root->size_arr_data_ = B / 2;
      if (leaf(root))
        return;
        
      for(short k = B / 2 + 1; k < B + 2; k++)
        root->childs_ptr_[k] = nullptr;
    }

    void addPtr(Node* &childs_ptr_,data_type key)	{
      int i;
      for(i = 0; i < B + 2; ++i)
        if(!this->childs_ptr_[i])
          break;
      this->childs_ptr_[i] = childs_ptr_;
      childs_ptr_->parent_ = this;
      this->addKey(key);
    }

    void lock() {
      barrier.lock();
      locked = true;
    }

    void unlock() {
      if(!locked)
        return;
      locked = false;
      barrier.unlock();
    }
  private:
    // data_type* keys_;
    // int size_arr_data_;
    // Node** childs_ptr_;
    // Node* right_ptr_;
    // Node* aux_ptr_;
    // Node* parent_;
    // std::mutex barrier;
    // bool locked;
};


template <std::size_t B, typename Type>
class BLinkTree {
 public:
  typedef Type data_type;
  typedef BLinkNode<B,Type> Node;

  Node* root_ptr_;  

  BLinkTree() { root_ptr_ = new Node; }

  ~BLinkTree() {}

  //std::size_t size() const {}

  Node* splitNode(Node* root) {
    Node* temp = root;
    Node* parent = root->parent_;
		if( !parent ){
			parent = new Node(nullptr);
			parent->childs_ptr_[0] = root;
			root->parent_ = parent;
		}
		parent->lock();
		Node* child = new Node(parent);
		if( root->leaf(root) ) {
			child->lock();
			child->addKey(root->keys_[B/2]);
		}
    temp->splitAddKey( child, B / 2 + 1, B);
    temp->splitAddPtr( child, B / 2 + 1, B + 1);
    child->right_ptr_ = root->right_ptr_;
    root->right_ptr_ = child;
		child->aux_ptr_ = root;
		if( child->right_ptr_ )
			child->right_ptr_->aux_ptr_ = child;
    root->removePtr( root );
    Node* parent1 = parent;
		while( parent1->right_ptr_ && parent1->right_ptr_->keys_[0] < root->keys_[B/2] )
			parent1 = parent1->right_ptr_;
		if( parent!=parent1 )	{
			parent->unlock();
			parent1->lock();
		}

		parent1->addPtr( child, root->keys_[B/2]);
		root->unlock();
		return parent1;
  }

  void insert(const data_type& value) {
    Node* root = root_ptr_;
		bool flag = false;
		root->lock();
		while( !root->leaf(root) ) {
			flag = false;
      {
				for( short i = 0; i < root->size_arr_data_; ++i )
					if(value < root->keys_[i]) {
						root->unlock();
						root = root->childs_ptr_[i];
						root->lock();
						flag = true;
						break;
					}
				if( !flag && value >= root->keys_[root->size_arr_data_ - 1] ) {
					root->unlock();
					root = root->childs_ptr_[root->size_arr_data_];
					root->lock();
				}
			}
		}
		Node* root1 = root;
		while( root->right_ptr_ && root->right_ptr_->keys_[0] < value )
			root = root->right_ptr_;
		if( root != root1)	{
			root1->unlock();
			root->lock();
		}
    root->addKey(value);
		while( root && root->size_arr_data_ > B )	{
			root1 = root;
			root = splitNode(root);
		}
		while( root1->parent_ )
			root1 = root1->parent_;
	}

  bool empty() const { return root_ptr_->keys_[0] == 0; }

  bool search( const data_type& value ) const {
    if( empty() ){
        std::cout<<"Arbol Vacio " << "\n";
        return false;
    }
    else{
      Node* pivot = root_ptr_;
      pivot->lock();
      while(!pivot->leaf(pivot)) {
        for(short i = 0 ; i < pivot->size_arr_data_ ; ++i) {
          if(value < pivot->keys_[i]) {
            pivot->unlock();
            pivot = pivot->childs_ptr_[i];
            pivot->lock();
            break;
          }
          else if(i + 1 == pivot->size_arr_data_) {
            pivot->unlock();
            pivot = pivot->childs_ptr_[i+1];
            pivot->lock();
            break;
          }
        }
      }
      for(int i = 0 ; i < pivot->size_arr_data_ ; ++i)
        if(pivot->keys_[i]==value) {

          pivot->unlock();
          return true;
        }

      pivot->unlock();
      return false;
    }
  }



  void remove(const data_type& value) {
    if( empty() ) {
      std::cout<<"Arbol Vacio" << "\n";
      return;
    }
    if(!search(value)) {
      std::cout<< value <<" No encontrado " << "\n";
      return;
    }
    int i;
    BLinkNode<B, Type>* pivot = root_ptr_;
    BLinkNode<B, Type>* parent = nullptr;
    int left_ = -1;
    int right_ = -1;
    while(!pivot->is_leaf_) {
      parent = pivot;
      for(i = 0; i < pivot->size_arr_data_ ; ++i) {
        if(value < pivot->keys_[i]) {
          left_ = i-1;
          right_ = i+1;
          pivot=pivot->childs_ptr_[i];
          break;
        }
        else if(i+1 == pivot->size_arr_data_) {
          left_ = i;
          right_ = i+2;
          pivot = pivot->childs_ptr_[i+1];
          break;
        }
      }
    }
    for(i = 0; i < pivot->size_arr_data_ ; ++i)
      if(pivot->keys_[i] == value)
        break;
    
    pivot->size_arr_data_--;
    for(; i < pivot->size_arr_data_ ; ++i)
      pivot->keys_[i] = pivot->keys_[i+1];
    pivot->childs_ptr_[pivot->size_arr_data_] = pivot->childs_ptr_[pivot->size_arr_data_+1];
    pivot->childs_ptr_[pivot->size_arr_data_+1] = nullptr;
    std::cout<<"Eliminado , eliminado...!!! soy un shinigami :v  "<<value<<"\n";  // COMENTAME
    if(pivot->size_arr_data_ < (B+1)/2) {
      std::cout<<"Underflow" << "\n";  // COMENTAME
      //std::cout<<left_ <<" "<<right_<<"\n"; // COMENTAME
      if(pivot == root_ptr_) {
        if(pivot->size_arr_data_ == 0) {
          BLinkNode<B, Type>* temp = root_ptr_;
          root_ptr_ = nullptr;
          delete(temp);
        }
      }
      if(left_ >= 0) {
        BLinkNode<B, Type>* aux_left_ = parent->childs_ptr_[left_];
        if(aux_left_->size_arr_data_ > (B+1)/2) {
          for(i = pivot->size_arr_data_ ; i > 0 ; i--)
            pivot->keys_[i] = pivot->keys_[i-1];
          pivot->childs_ptr_[pivot->size_arr_data_+1] = pivot->childs_ptr_[pivot->size_arr_data_];
          pivot->childs_ptr_[pivot->size_arr_data_] = nullptr;
          pivot->size_arr_data_++;
          aux_left_->size_arr_data_--;
          parent->keys_[left_] = aux_left_->keys_[aux_left_->size_arr_data_];
          pivot->keys_[0] = aux_left_->keys_[aux_left_->size_arr_data_];
          aux_left_->childs_ptr_[aux_left_->size_arr_data_] = aux_left_->childs_ptr_[aux_left_->size_arr_data_+1];
          aux_left_->childs_ptr_[aux_left_->size_arr_data_ + 1] = nullptr;
          return;
        }
      }
      if(right_ <= parent->size_arr_data_) {
        BLinkNode<B, Type> * aux_right = parent->childs_ptr_[right_];
        if(aux_right->size_arr_data_ > (B+1)/2) {
          pivot->childs_ptr_[pivot->size_arr_data_ + 1] = pivot->childs_ptr_[pivot->size_arr_data_];
          pivot->childs_ptr_[pivot->size_arr_data_] = nullptr;
          pivot->keys_[pivot->size_arr_data_] = aux_right->keys_[0];
          parent->keys_[right_-1] = aux_right->keys_[0];
          pivot->size_arr_data_++;
          aux_right->size_arr_data_--;
          for(i = 0 ; i < aux_right->size_arr_data_ ; ++i)
            aux_right->keys_[i] = aux_right->keys_[i+1];
          aux_right->childs_ptr_[aux_right->size_arr_data_] = aux_right->childs_ptr_[aux_right->size_arr_data_+1];
          aux_right->childs_ptr_[aux_right->size_arr_data_+1] = nullptr;
          return;
        }	
      }
      if(left_>=0) {
        BLinkNode<B, Type> * aux_left_ = parent->childs_ptr_[left_];
        if(aux_left_->size_arr_data_ + pivot->size_arr_data_ < B+1) {
          for(i = 0; i < pivot->size_arr_data_ ; ++i)
            aux_left_->keys_[aux_left_->size_arr_data_ + i] = pivot->keys_[i];
          aux_left_->childs_ptr_[aux_left_->size_arr_data_] = nullptr;
          aux_left_->size_arr_data_ = aux_left_->size_arr_data_ + pivot->size_arr_data_;
          aux_left_->childs_ptr_[aux_left_->size_arr_data_] = pivot->childs_ptr_[pivot->size_arr_data_];
          removeAuxFunction(parent->keys_[left_],parent);
          return;
        }
      }
      if(right_<=parent->size_arr_data_) {
        BLinkNode<B, Type> * aux_right=parent->childs_ptr_[right_];
        if(pivot->size_arr_data_ + aux_right->size_arr_data_ < B+1) {
          for(i = 0; i < aux_right->size_arr_data_ ; ++i)
            pivot->keys_[pivot->size_arr_data_ + i] = aux_right->keys_[i];
          pivot->childs_ptr_[pivot->size_arr_data_] = nullptr;
          pivot->size_arr_data_ = pivot->size_arr_data_ + aux_right->size_arr_data_;
          pivot->childs_ptr_[pivot->size_arr_data_] = aux_right->childs_ptr_[aux_right->size_arr_data_];
          removeAuxFunction(parent->keys_[right_-1], parent);
          return;
        }
      }          
    }
    return;
  }

 private:
  Node* findParent(Node* pivot, Node* child) {
    if(pivot->is_leaf_==true)
      return nullptr;
    Node* parent = nullptr;
    for(int i = 0 ; i < pivot->size_arr_data_ + 1 ; ++i) {
      if (pivot->childs_ptr_[i] == child)
        return pivot;
      else {
        parent = findParent(pivot->childs_ptr_[i],child);
        if(parent)
          return parent;
      }
    }
    return nullptr;
  }

  void removeAuxFunction(int value, Node* pivot) {
    int i;
    for(i = 0 ; i < pivot->size_arr_data_; ++i)
      if(pivot->keys_[i] == value)
        break;
    pivot->size_arr_data_--;
    Node *temp = pivot->childs_ptr_[i + 1];  // i++ no funciona xq// :/ 
    for(int j = i; j < pivot->size_arr_data_ ; j++) {
      pivot->keys_[j] = pivot->keys_[j + 1];
      pivot->childs_ptr_[j+1] = pivot->childs_ptr_[j + 2];
    }
    delete(temp);
    if(pivot->size_arr_data_ < (B+1)/2) {
      std::cout<<"Underflow " << "\n";
      if(pivot == root_ptr_) {
        if(pivot->size_arr_data_ == 0) {
          temp = root_ptr_;
          root_ptr_ = pivot->childs_ptr_[0];
          delete(temp);
        }
      }
      else {
        Node * parent=findParent(root_ptr_,pivot);
        int left_ = -1;
        int right_ = -1;
        for(i = 0; i < parent->size_arr_data_ + 1; ++i) {
          if(pivot==parent->childs_ptr_[i]) {
            left_ = i--;
            right_ = i++;
            break;
          }
          else if( i + 1 == parent->size_arr_data_ + 2) {
            left_ = i;
            right_ = i + 2;
            break;
          }
        }
        if(left_ >= 0) {
          Node* left_aux=parent->childs_ptr_[left_];
          if(left_aux->size_arr_data_>(B+1)/2) {
            for(i = pivot->size_arr_data_ ; i > 0 ; i--)
              pivot->keys_[i] = pivot->keys_[i-1];
            for(i = pivot->size_arr_data_ + 1; i > 0; ++i)
              pivot->childs_ptr_[i] = pivot->childs_ptr_[i-1];
            pivot->size_arr_data_++;
            left_aux->size_arr_data_--;
            parent->keys_[left_] = left_aux->keys_[left_aux->size_arr_data_];
            pivot->keys_[0] = left_aux->keys_[left_aux->size_arr_data_];
            pivot->childs_ptr_[0] = left_aux->childs_ptr_[left_aux->size_arr_data_+1];
            left_aux->childs_ptr_[left_aux->size_arr_data_+1] = nullptr;
            return;
          }
        }
        if(right_<=parent->size_arr_data_) {
          Node* right_aux = parent->childs_ptr_[right_];
          if(right_aux->size_arr_data_ > (B+1)/2) {
            pivot->keys_[pivot->size_arr_data_] = parent->keys_[right_-1];
            pivot->childs_ptr_[pivot->size_arr_data_+1] = right_aux->childs_ptr_[0];
            parent->keys_[right_-1] = right_aux->keys_[0];
            pivot->size_arr_data_++;
            right_aux->size_arr_data_--;
            for(i = 0 ; i < right_aux->size_arr_data_ ; ++i)
              right_aux->keys_[i]=right_aux->keys_[i+1];

            for(i=0;i<right_aux->size_arr_data_+1;++i)
              right_aux->childs_ptr_[i]=right_aux->childs_ptr_[i+1];

            right_aux->childs_ptr_[right_aux->size_arr_data_+1] = nullptr;
            return;
          }	
        }
        if(left_ >= 0) {
          Node* left_aux = parent->childs_ptr_[left_];
          if(left_aux->size_arr_data_ + pivot->size_arr_data_ < B) {
            left_aux->keys_[left_aux->size_arr_data_] = parent->keys_[left_];
            for(i = 0 ; i < pivot->size_arr_data_ + 1 ; ++i)
              left_aux->keys_[left_aux->size_arr_data_ + 1 + i] = pivot->keys_[i];
            for(i = 0 ; i < pivot->size_arr_data_ + 2 ; ++i)
              left_aux->childs_ptr_[left_aux->size_arr_data_ + 1 + i] = pivot->childs_ptr_[i];
            left_aux->size_arr_data_ = left_aux->size_arr_data_ + pivot->size_arr_data_ + 1;
            removeAuxFunction(parent->keys_[left_], parent);
            return;
          }
        }
        if(right_<=parent->size_arr_data_) {
          Node * right_aux = parent->childs_ptr_[right_];
          if(pivot->size_arr_data_+right_aux->size_arr_data_ < B) {
            pivot->keys_[pivot->size_arr_data_] = parent->keys_[right_-1];
            for(i = 0 ; i < right_aux->size_arr_data_ + 1 ; ++i)
              pivot->keys_[pivot->size_arr_data_ + 1 + i] = right_aux->keys_[i];
            for(i = 0 ; i < right_aux->size_arr_data_ + 2 ; ++i)
              pivot->childs_ptr_[pivot->size_arr_data_ + 1 + i] = right_aux->childs_ptr_[i];                  
            pivot->size_arr_data_ = pivot->size_arr_data_ + right_aux->size_arr_data_ + 1;
            removeAuxFunction(parent->keys_[right_-1], parent);
            return;
          }
        }	
      }
    }
    return;
  }

};

}  // namespace Concurrent
}  // namespace EDA

#endif  // SOURCE_B_LINK_HPP_
