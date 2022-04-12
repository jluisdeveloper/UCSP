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
 
#endif