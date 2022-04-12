#include <iostream>
#include "cocktail.h"

bool asc(int a, int b) {
	return a > b;
}

bool desc(int a, int b) {
	return a < b;
}

int main(){

  int A[] = {5,9,8,10,4};
	cocktail(asc, A, 5);
  print(A,5);
}