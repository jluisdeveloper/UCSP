#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include "../Node/node.h"

template <typename T>
class LinkedList{  
  public:
    LinkedList();
		bool find(T, Node<T>* &);
		void add(T);
    void remove(T);
    void print();
    Node<T>* head;
    ~LinkedList();
};
 
#endif