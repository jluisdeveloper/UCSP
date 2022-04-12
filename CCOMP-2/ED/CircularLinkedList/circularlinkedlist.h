#ifndef CIRCULARLINKEDLIST_H_INCLUDED
#define CIRCULARLINKEDLIST_H_INCLUDED

#include "../Node/node.h"

template <typename T>
class CircularLinkedList{  
  public:
    CircularLinkedList();
		bool find(T, Node<T>* &);
		void add(T);
    void remove(T);
    void print();
    Node<T>* head;
    //~CircularLinkedList();
};
 
#endif