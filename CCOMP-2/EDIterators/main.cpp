#include <iostream>
#include "Node/node.h"
#include "Iterator/iterator.h"
#include "LinkedList/linkedlist.h"

typedef LinkedList<int, Greater<int>> ListaPro;

int main(){
	//LinkedList<int, Greater<int>> linkedList;
  ListaPro Lista;
	//for (int i = 0; i < 10; ++i) Lista.insert(i);
	//linkedList.print();

  Lista.insert(5);
  Lista.insert(5);
  Lista.insert(5);
  Lista.insert(4);
  Lista.insert(10);
  Lista.insert(3);
  Lista.insert(8);

  //Lista.print();

  //std::cout<< std::endl;
	LinkedList<int, Less<int>>::Iterador i;
	for (i = Lista.begin(); i != Lista.end(); ++i)
		std::cout << *i << std::endl;

	return 0;
}