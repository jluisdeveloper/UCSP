#include <bits/stdc++.h>

#include "RandomNumbersGen/RNGen.hpp"
#include "TimeTester/Timer.hpp"
#include "Tools/helpers.hpp"
// #include "QuickSort/quicksort.hpp"
// #include "HeapSort/heapsort.hpp"


using namespace std;


template<class T1>
struct Adapter {
    typedef T1 T;
    typedef Des<int> Functor;
};

template<class T1>
struct Adapter2 {
    typedef T1 T;
    typedef Asc<int> Functor;
};

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



void quick(int tam){
	float* arr = NULL;
	arr = new float[tam];
	RNGen<float> random(arr, tam);
	QuickSort<Adapter<float>> SORT(arr, 0, tam);
	SORT.sort(arr, 0, tam - 1);
}

void check_time(vector<int>cases ){
  for (int i = 0; i < cases.size(); ++i) {
    cout<< "Para QuickSort"<< cases[i]<< " : ";
    Timer t;
    quick(cases[i]);
  }
}

void heap(int tam){
	float* arr = NULL;
	arr = new float[tam];
	RNGen<float> random(arr, tam);
	HeapSort<Adapter<float>> SORT(arr, tam);
	SORT.sort();
}

void check_time2(vector<int>cases ){
  for (int i = 0; i < cases.size(); ++i) {
    cout<< "Para HeapSort"<< cases[i]<< " : ";
    Timer t;
    heap(cases[i]);
  }
}




int main(){
	// int tam = 100;
	// float* arr = NULL;
	// arr = new float[tam];

	// RNGen<float> random(arr, tam);
	// QuickSort<Adapter<float>> quickS(arr, 0, tam);
	// HeapSort<Adapter2<float>> heapS(arr, tam);

	// vector<int> cases = { 10, 100, 1000, 10000, 100000, 1000000 };

	// check_time(cases);
	// check_time2(cases);

	// for (int i = 0; i < cases.size(); ++i) {
  //   cout<< "Para "<< cases[i]<< " : ";
  //   Timer t;
  //   quickS.sort(arr, 0, cases[i]);
  // }

	// clock_t inicio;
	// float duracion;
	// int tam = 100;

	// float* arr = NULL;
	// arr = new float[tam];

	// RNGen<float> random(arr, tam);


	// QuickSort<Adapter<float>> orden(arr, 0, tam);
	// //cout << "desordenado" << endl;
	
	// cout << "sorting... \n";
	// //cout << "ordenado" << endl;
	// inicio = clock();
	// orden.sort(arr,0,tam-1);
	// orden.printArray(arr, tam);

	// cout << "\n";
	// duracion = (clock() - inicio) / (float)CLOCKS_PER_SEC;
	// cout << " Tiempo :" << duracion << endl;
	// cout << "-------------------------------------" << endl;

	return 0;
}