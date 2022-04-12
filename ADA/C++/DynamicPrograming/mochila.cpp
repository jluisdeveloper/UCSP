#include <bits/stdc++.h>

using namespace std;


// vivimos enganhados vector de vector es muy costoso :x :'(  se acabo el suenho XD

int mochila(int capacidad, vector<int>peso, vector<int>beneficio, int cant_objs){
    vector<vector<int>> resultMt;
    
    resultMt.assign(cant_objs + 1, vector<int>(capacidad + 1, 0));

    for(short i = 0; i <= cant_objs; ++i){
        for(short j = 0; j <= capacidad; ++j){
            if(i == 0 || j == 0)
                resultMt[i][j] = 0;
            else if(peso[i -1] <= j)
                resultMt[i][j] = max(beneficio[i -1] + resultMt[i -1][j - peso[i -1]], resultMt[i-1][j]);
            else 
                resultMt[i][j] = resultMt[i-1][j];
        }
    }
    return resultMt[cant_objs][capacidad];
}

// complejidad = capacidad x cantidad de objetos

int main(){
    vector<int> beneficio = {70, 30, 25, 75, 120, 60};
    vector<int> peso = {6, 5, 3, 1, 8, 9};
    int capacidad = 25;
    int n = beneficio.size();
    
    
    cout << mochila(capacidad,peso,beneficio,n);
    
    cout << endl;
}
