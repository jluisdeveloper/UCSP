#include <iostream>
#include "../Node/node.h"
#include "../Iterator/iterator.h"


template<class T>
class Less{
	public:
    bool operator()(T a, T b) { return a <= b; }
};

template<class T>
class Greater{
	public:
    bool operator()(T a, T b) { return a >= b; }
};

template<class T, class C>
class LinkedList{
public:
	Node<T>* head;
	C comparator;

	LinkedList(){ head = nullptr; }
	bool find(T , Node<T>*&);
	bool insert(T);
	bool remove(T);
	void print();

	// Iterator
	typedef Iterator<T> Iterador;
	Iterador begin();
	Iterador end();
};

template<class T, class C>
bool LinkedList<T, C>::find(T _data, Node<T>* &reference){
  reference = NULL;
	for (Node<T> *p = head; p && comparator(p->data, _data);reference = p , p = p->next)
		if(p->data == _data)
			return true;
		return false;    
}

template<class T, class C>
bool LinkedList<T, C>::insert(T _data){
  Node<T> *pos;
  //pos = head;
  if(!find(_data,pos)){
    if(!pos){
      head = new Node<T>(_data,head);
      return 1;
    }else{
      pos->next = new Node<T>(_data,pos->next);
      return 1;
    }
  }
  return 0; 
}

template<class T, class C>
bool LinkedList<T, C>::remove(T _data){
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

template<class T, class C>
void LinkedList<T, C>::print(){
	Node<T>* aux;
  aux = head;
  while(aux){
    std::cout << aux->data << " ";
    aux = aux->next;
  }
  std::cout<<std::endl; 
}

template<class T, class C>
Iterator<T> LinkedList<T, C>::begin(){
	return Iterador(head);
}

template<class T, class C>
Iterator<T> LinkedList<T, C>::end(){
	return Iterador(NULL);
}

