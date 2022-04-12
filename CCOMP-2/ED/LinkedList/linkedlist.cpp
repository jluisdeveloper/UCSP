#include <iostream>
#include "linkedlist.h"

template <typename T>
LinkedList<T>::LinkedList(){
	head = NULL;
}

template <typename T>
bool LinkedList<T>::find(T _data, Node<T>* &reference){
	reference = NULL;
	for (Node<T> *p = head; p && p->data <= _data; reference = p, p = p->next)
		if(p->data == _data)
			return true;
		return false; 
}

template <typename T>
void LinkedList<T>::add(T _data){
  Node<T> *pos;
  //pos = head;
  if(!find(_data,pos)){
    if(!pos){
      head = new Node<T>(_data,head);
    }else{
      pos->next = new Node<T>(_data,pos->next);
    }
  }  
}

template <typename T>
void LinkedList<T>::remove(T _data){
  Node<T> *aux, *temp;
  //aux = head;
  if(find(_data, aux)){
    if(!aux){
      temp = head;
      head = head->next;
      delete temp;
    }else{
      temp = aux->next;
      aux->next = temp->next;
      delete temp;
    }
  }
}

template <typename T>
void LinkedList<T>::print(){
  Node<T>* aux;
  aux = head;
  while(aux){
    std::cout << aux->data << " ";
    aux = aux->next;
  }
  std::cout<<std::endl; 
}

template <typename T>
LinkedList<T>::~LinkedList(){
  while(head){
    remove(head->data);
  }
}

template class LinkedList<int>;
template class LinkedList<float>;
template class LinkedList<double>;