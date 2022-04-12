#ifndef QUICKSORT_H_INCLUDED
#define QUICKSORT_H_INCLUDED

#include <iostream>
#include "../Tools/helpers.hpp"

using namespace std;

template<class adapter>
class HeapSort {
    public:
        typedef typename adapter::T T;
        typedef typename adapter::Functor F;

        T* arr;
        int n;
        F cmp;

        HeapSort(T*, int);
        void heapify(T arr[], int n, int i);
        void sort();
        void printArray();

};

template<typename adapter>
HeapSort<adapter>::HeapSort(T* arr, int n){
	this->arr = arr;
	this->n = n;
}

template<typename adapter>
void HeapSort<adapter>::heapify(T arr[], int n, int i){
	int largest = i; // Initialize largest as root 
	int l = 2 * i + 1; // left = 2*i + 1 
	int r = 2 * i + 2; // right = 2*i + 2 

	// If left child is larger than root 
	if (l < n && cmp(arr[l] , arr[largest]))
		largest = l;

	// If right child is larger than largest so far 
	if (r < n && cmp(arr[r] , arr[largest]))
		largest = r;

	// If largest is not root 
	if (largest != i)
	{
		swap(arr[i], arr[largest]);

		// Recursively heapify the affected sub-tree 
		heapify(arr, n, largest);
	}
}
template<typename adapter>
void HeapSort<adapter>::sort(){
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// One by one extract an element from heap 
	for (int i = n - 1; i > 0; i--)
	{
		// Move current root to end 
		swap(arr[0], arr[i]);

		// call max heapify on the reduced heap 
		heapify(arr, i, 0);
	}
}



template<typename adapter>
void HeapSort<adapter>::printArray(){
	for (int i = 0; i < n; i++)
	{
		cout << *(arr + i) << endl;
	}
	
}

#endif