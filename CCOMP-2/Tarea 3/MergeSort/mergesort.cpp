#include <iostream>
#include "mergesort.h"

void print(int* Array, int size){
	int* len = Array + size-1;
	for(; Array <= len; Array++){
		std::cout << *Array << " ";
	}
}

void merge(int* a, int* b, int* c, int size){
	int* end = c + (2*size);
	int *endPair = a + size - 1;
    int *endNoPair = b + size - 1;
	bool stateMachine = true;
	while(stateMachine){
		if(*a < *b){
			*c = *a;
			if(a <= endPair){
				a++;
				stateMachine = true;
			}
		}else{
			*c = *b;
			if(b <= endNoPair){
				b++;
				stateMachine = true;
			}else{
				*c=*a;
				a++;
				stateMachine = true;			
			}		
		}
		c++;			
		if(c == end){
			stateMachine = false;
		}		
	}
}

void fibonacci(int* arr, int size){
    int* end = arr+size;
    while(arr < end-2){
			*(arr+2) = *arr + *(arr+1);
			arr++;
    }
}
