#include <bits/stdc++.h>

#include "../RandomNumbersGen/RNGen.hpp"
#include "../Tools/helpers.hpp"

using namespace std;

template<typename T>
class Greater {
    public:
        inline bool operator()(T a, T b){
            return a <= b;
        }
};

template<typename T>
class Lower {
    public:
        inline bool operator()(T a, T b){
            return a >= b;
        }
};

template<typename adapter>
class PowerSort {
    public:
        typedef typename adapter::T T;
        typedef typename adapter::F F;

        T* arr;
        int n;
        F cmp;

        PowerSort(T*, int);
        ~PowerSort();
        void insertionSort(int min, int max);

        void mergeOriginal(int , int , int );
        void mergeSortO(int min, int max, int limit);

        void mergeModified(int , int , int);
        void mergeSortM(int min, int max, int limit);
        void print();
};

template<typename adapter>
PowerSort<adapter>::PowerSort(T* arr, int n){
    this->arr = arr;
    this->n = n;
}

template<typename adapter>
PowerSort<adapter>::~PowerSort(){
    // compilador malo malo malo xD -_- :v
}

template<typename adapter>
void PowerSort<adapter>::insertionSort( int min, int max) {
    int key;
    for (int j = min + 1; j <= max; j++){
        key = arr[j];
        int i = j - 1;

        while (i >= min && arr[i] > key){
            arr[i + 1] = arr[i];
            i--;
        }
        arr[i + 1] = key;
    }
}

template <typename adapter>
void PowerSort<adapter>::mergeOriginal(int min, int max, int mid){
    int * temp = new int [max + 1];
    int i = min;
    int j = mid + 1;

    for (int index = min; index <= max; index++) {
        if (cmp(i,mid) && (j > max || cmp(arr[i], arr[j]))) {
            temp[index] = arr[i];
            i = i + 1;
        }

        else{
            temp[index] = arr[j];
            j = j + 1;
        }
    }

    for (int index = min ; index <= max ; index++)
        arr[index] = temp[index];
}

template<typename adapter>
void PowerSort<adapter>::mergeSortO( int min, int max, int limit){
    if ((max - min + 1) <= limit){
        insertionSort( min, max);
    }
    else{
        int mid = (max + min) / 2;
        mergeSortO(min, mid, limit);
        mergeSortO(mid + 1, max, limit);
        mergeOriginal(min, max, mid);
    }
}

template<typename adapter>
void PowerSort<adapter>::mergeModified( int min, int max, int mid ){
    int i = min, j = mid + 1, k = 0, k1=k;
    int* temp = new int[max - min + 1];

    while (i <= mid && j <= max){
        if (cmp(arr[i] , arr[j]) && i < j){
            temp[k++] = arr[i++];
        }

        else
            k1++;
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];


    while (j <= max)
        temp[k++] = arr[j++];


    for (i = min; i <= max; i++)
        arr[i] = temp[i - min];

    cout << endl;
    cout << k1 << " este es el numero de Inversiones "<< endl;

    return;
}

template<typename adapter>
void PowerSort<adapter>::mergeSortM( int min, int max, int limit){
    if ((max - min + 1) <= limit){
        insertionSort( min, max);
    }
    else{
        int mid = (max + min) / 2;
        mergeSortM(min, mid, limit);
        mergeSortM(mid + 1, max, limit);
        mergeModified(min, max, mid);
    }
}

template<typename adapter>
void PowerSort<adapter>::print(){
    for (int i = 0; i < n; i++){
        cout << *(arr + i) << " ";
    }
}

struct adapter {
    typedef int T;
    typedef Greater<T> F;
};

int main() {
    int n = 50;
    int limit = 10;

    int* arr = NULL;
    arr = new int[n];

    RNGen<int> randonNumbers(arr,n);

    PowerSort<adapter> orden(arr, n);
    orden.print();
    orden.mergeSortM(0, n - 1, limit);

    cout << endl;

    orden.print();

    return 0;
}