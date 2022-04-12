#include <iostream>
#include "node.h"

template<typename T>
Node<T>::Node(T _data, Node<T>* _next){
  this->data = _data;
  next = _next;
}

template<typename T>
Node<T>::Node(T _data){
  this->data = _data;
  next = NULL;
}

template class Node<int>;
template class Node<double>;
template class Node<float>;