#ifndef ITERATOR_H_INCLUDED
#define ITERATOR_H_INCLUDED

#include "../Node/node.h"

template<class T>
class Iterator{
public:
	Node<T>* ptrNode;
	
	Iterator(){}
	Iterator(Node<T>* p){ ptrNode = p; }

	// Overloads
	bool operator!=(Iterator<T> iter_){ return ptrNode != iter_.ptrNode; }
	T operator*(){ return ptrNode->data; }
	Iterator<T>& operator++() {
		if (ptrNode) ptrNode = ptrNode->next;
		return *this;
	}
};

#endif // ITERATOR_H_INCLUDED