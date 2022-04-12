#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

template <typename T>
class Node{  
  public:
    Node(T,Node<T>*);
    Node(T);
    Node<T>* next;  
    T data;
};

template<typename T>
Node<T>::Node(T _data, Node<T>* _next){
  this->data = _data;
  next = _next;
}

template<typename T>
Node<T>::Node(T _data){
  this->data = _data;
  next = this;
}

template class Node<int>;
template class Node<double>;
template class Node<float>;

#endif // NODE_H_INCLUDED