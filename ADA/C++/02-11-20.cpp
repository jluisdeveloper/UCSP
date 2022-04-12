#include <bits/stdc++.h>
using namespace std;

// el tamanaho del contenedor de todas las combinaciones posibles, tiene tendencia fibonacci

void generateHelper(int K, char _chain[], int n){
    if (n  == K){
        _chain[n] = '\0' ;
        cout << _chain << " ";
        return ;
    }

    if (_chain[n-1] == '1'){
        _chain[n] = '0';
        generateHelper (K , _chain , n+1);
    }

    if (_chain[n-1] == '0') {
        _chain[n] = '0';
        generateHelper(K, _chain, n+1);
        _chain[n] = '1';
        generateHelper(K, _chain, n+1) ;
    }
}

void generateCombination(int K){
    if (K <= 0)
        return ;

    char chain[K];

    chain[0] = '0' ;
    generateHelper ( K , chain , 1 ) ;

    chain[0] = '1' ;
    generateHelper ( K , chain , 1 );
}


int main(){
    generateCombination(6);
    cout << endl;
    return 0;
}