#include <bits/stdc++.h>
using namespace std;


// Sin backtracking :/ 
void Mochila(int n, int weight[], int cost[], int maxBag){
    int *a = new int[maxBag];
    int *temp = new int[maxBag];

    for (int i = 0; i <= maxBag; i++){
        a[i] = 0;
        temp[i] = -1;
    }

    a[0] = 0;
    for (int i = 1; i <= maxBag; i++)
        for (int j = 0; j < n; j++)
            if ((weight[j] <= i) && (a[i] < a[i - weight[j]] + cost[j])){
                a[i] = a[i - weight[j]] + cost[j];
                temp[i] = j;
            }

    cout << "Se gana " << a[maxBag] << endl;
}


int knapSack(int W, vector<int> weight, vector<int> cost, int n)
{
    int i, w;

    vector<vector<int> >  K;

    for (i = 0; i <= n; i++){
        for (w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }

    return K[n][W];
}

int main() {
    int n, maxBag;
    cout<<"Ingrese la cantidad de objetos: ";
    cin>>n;
    int *weight = new int[n];
    int *cost = new int[n];
    for(int i=0; i<n; i++){
        cin >> weight[i];
        cin >> cost[i];
        cout << endl;
    }
    cout << "Ingrese el weight maximo de la mochila: ";
    cin >> maxBag;
    Mochila(n, weight, cost, maxBag);
    return 0;
}