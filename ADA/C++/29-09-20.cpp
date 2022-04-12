#include <bits/stdc++.h>

using namespace std;

void insertionSort( int min, int max)
{
    int key;
    for (int j = min + 1; j <= max; j++)
    {
        key = arr[j];
        int i = j - 1;

        while (i >= min && arr[i] > key)
        {
            arr[i + 1] = arr[i];
            i--;
        }
        arr[i + 1] = key;
    }
}

int main(){
    cout << "compilando"<<endl;
    return 0;
}