#ifndef QUICKSORT_H_INCLUDED
#define QUICKSORT_H_INCLUDED

#include <iostream>
#include "../Tools/helpers.hpp"

using namespace std;

template<class adapter>
class QuickSort {
public:
    typedef typename adapter::T T;
    typedef typename adapter::Functor F;
    T* arr;
    int left, right;
    F cmp;

    QuickSort(T*, int, int);
    int Separacion(T*, int, int);
    void sort(T*, int, int);
    void printArray(T*, int);


};
template<typename adapter>
QuickSort<adapter>::QuickSort(T* arr, int left, int right)
{
    this->arr = arr;
    this->left = left;
    this->right = right;
}

template<class adapter>
int QuickSort<adapter>::Separacion(T* arr, int left, int right){
    int pivote = arr[right];
    int iterator = (left - 1);
    for (auto j = left; j <= right - 1; j++)
    {
        if (cmp(arr[j], pivote))
        {
            iterator++;
            swap(&arr[iterator], &arr[j]);
        }
    }
    swap(&arr[iterator + 1], &arr[right]);
    return (iterator + 1);
}


template<class adapter>
void QuickSort<adapter>::sort(T* arr, int left, int right){
    if (left < right)
    {
        int masterPivote = Separacion(arr, left, right);
        sort(arr, left, masterPivote - 1);
        sort(arr, masterPivote + 1, right);
    }
}

template<class adapter>
void QuickSort<adapter>::printArray(T* arr, int size){
    for (int i = 0; i < size; i++)
        cout << arr[i] << endl;
    cout << endl;
}

#endif