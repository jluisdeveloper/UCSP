/* #include <iostream>  
#include "cocktail.h"


template <typename T, typename C>
Cocktail<T,C>::Cocktail(T* _ptr, T _size){
  ptr = _ptr;
  size = _size;
}

template <typename T, typename C>
void Cocktail<T,C>::sort(){
  bool goingright = true;
  int i = 0;
  int cont = 0;
  while (true) {

    if (cmp(*(ptr + i), *(ptr + i+1))) {
      swap(*(ptr + i), *(ptr + i + 1));
      cont++;
    }
    if (goingright)
      i++;
    else
      i--;
    if (i == size - 2) {
      if (goingright)
        goingright = false;
      if (cont == 0) {
        break;
      }
    }
    if (i == 0) {
      goingright = true;
      cont = 0;
    }
  }
}


template <typename T, typename C>
void Cocktail<T,C>::print(){
	for(int i = 0; i < size; i++)	{
		std::cout << *ptr << std::endl;
		ptr++;
	}
}

template class Cocktail<int,bool>;
template class Cocktail<double,bool>;
template class Cocktail<float,bool>; */