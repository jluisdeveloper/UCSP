#include <bits/stdc++.h>
#include "RandomNumbersGen/RNGen.hpp"

using namespace std;

void quicksort(int* Arr, int first, int last){
    int i = first;                              //n
    int j = last;                               //n
    int pivote = (Arr[i] + Arr[j])/2;           //
    int x;                                      //n
    while (i<j){
        while (Arr[i] < pivote ){
            i++;
        }
        while (Arr[j] > pivote ){
            j--;
        }
        if(i<=j){
            x = Arr[j];
            Arr[j] = Arr[i];
            Arr[i] = x;
            i++;
            j--;
        }
    }
    if (first < j){
        quicksort(Arr,first,j);   // logn
    }
    if (last > i){
        quicksort(Arr,i,last);   // logn 
    }
}

int colocar(int *v, int b, int t){
    int i;                      //
    int pivote, valor_pivote;   //
    int temp;                   //
    pivote = b;                 //
    valor_pivote = v[pivote];   //
    for (i=b+1; i<=t; i++){     //
        if (v[i] < valor_pivote){
            pivote++;
            temp=v[i];
            v[i]=v[pivote];
            v[pivote]=temp;
        }
    }
    temp=v[b];
    v[b]=v[pivote];
    v[pivote]=temp;
    return pivote;
}
void Quicksort(int* v, int b, int t){
    int pivote;
    if(b < t){
        pivote=colocar(v, b, t);
        Quicksort(v, b, pivote-1);
        Quicksort(v, pivote+1, t);
    }
}

void print(int* Arr, int len){
    for (int i = 0; i < len; ++i) {
        cout << Arr[i] << " ";
    }
    cout << endl;
}



int main () {
    int* arr;
    RNGen<int> A(arr, 50);


    quicksort(arr, arr[0], arr[50-1]);
    print(arr,50);

    cout << "hola we xD"<< endl;
    return 0;
}