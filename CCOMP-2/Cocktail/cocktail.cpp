#include <iostream>
#include "cocktail.h"

void print(int* Array, int size){
	int* tam = Array + size-1;
	for(; Array <= tam; Array++){
		std::cout << *Array << std::endl;
	}
}

void swap(int &a, int &b){
	int aux;
	aux = a;
	a = b;
	b = aux;
}

void cocktail(bool(*mode)(int,int), int* ptr, int size) {
	bool goingright = true;
	int i = 0;
	int cont = 0;
	while (true) {

		if (mode(*(ptr + i), *(ptr + i+1))) {
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