#include <iostream>
#include "circularlinkedlist.h"

template <typename T>
CircularLinkedList<T>::CircularLinkedList(){
  head = NULL;
}

template <typename T>
bool CircularLinkedList<T>::find(T _data, Node<T>* &reference){
  reference = NULL;
	for (Node<T> *p = head; p && p->data <= _data; reference = p, p = p->next)
		if(p->data == _data)
			return true;
		return false; 
}

template <typename T>
void CircularLinkedList<T>::add(T _data){
  Node<T> *pos, *temp;

  if(!find(_data, pos)){
    if(!pos){
      head = new Node<T>(_data);
      /* if(!pos->next){
        head->next = head;
      } */
    }
    else {   
      //head->next = pos;   
      /* std::cout<<head->data<<"="<<std::endl;
      head->next = pos; 
      std::cout<<head->next->data<<"=="<<std::endl; */
      pos->next = new Node<T>(_data,head->next); 
      temp = pos->next;
      if (!temp->next){
        temp->next = head;
        std::cout<<temp->data<<" = = "<<std::endl;
      }
    }
      
  } 
    
    //pos = head->next; 
  //pos = head;
   /* if ((pos))
    std::cout<<pos->data<<" = "<<std::endl;  */
}

template <typename T>
void CircularLinkedList<T>::print(){
  Node<T>* aux;
  aux = head;
  while(aux->next != head){
    std::cout << aux->data << " ";
    aux = aux->next;
  }
  std::cout<<std::endl;
}

template class CircularLinkedList<int>;