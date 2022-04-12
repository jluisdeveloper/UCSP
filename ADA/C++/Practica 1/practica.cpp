#include <bits/stdc++.h>
using namespace std;

void display(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1)
            cout << "+";
    }
    cout << endl;
}

void combination(int n, int i=0, int arrSize=1) {
    static int* arr = new int[arrSize]; 
    if(n == 0)
        display(arr, i);
    else if (n > 0) {
        int k;
        for (k = arrSize; k > 0; k--) {
            arr[i] = k;
            combination(n - k, i + 1, k);
        }
    }
}

int main(){
    int n = 17;
    combination(n,0,n);
    return 0;
}

//#include <bits/stdc++.h>
//
//using namespace std;
//
//int contiguousAdder(vector<int> a){
//    int last_value = 0, accumulator = 0, index_start =0, index_end = 0, s = 0 ;
//
//    for (int i = 0; i < a.size(); i++ ){
//        accumulator += a[i];
//
//        if (last_value < accumulator){
//            last_value = accumulator;
//            index_start = s;
//            index_end = i;
//        }
//
//        if (accumulator < 0){
//            accumulator = 0;
//            s = i + 1;
//        }
//    }
//    cout<< "Rango: Inicio "<< index_start + 1 << endl;
//    cout << "Rango: Final "<< index_end + 1<< endl;
//    return last_value;
//}
//
//int main(){
//    vector<int> a = { 31,-41, 59, 26, -53, 58, 97, -93 ,-23, 84 };
//    int max_sum = contiguousAdder(a);
//    cout << "La suma maxima contigua es: " << max_sum<< endl;
//    return 0;
//}