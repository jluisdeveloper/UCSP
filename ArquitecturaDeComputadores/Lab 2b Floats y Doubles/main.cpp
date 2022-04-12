#include <bits/stdc++.h>
using namespace std;

void printTest(vector<bool> arr){
    for (int i = 0; i < arr.size(); ++i) {
        cout<< arr[i];
    }
    cout << endl;
}

vector<bool> completeBits(vector<bool> arr, int bits){
    vector<bool> result;
    if (arr.size() >= bits){
        result = arr;
        return result;
    }else {
        stack<bool> stckAux;
        int i = arr.size()-1;
        while (i>=0){
            stckAux.push(arr[i]);
            i--;
        }
        for (int j = 0; j <= bits - arr.size()-1; ++j) {
            stckAux.push(0);
        }
        while (!stckAux.empty()){
            result.push_back(stckAux.top());
            stckAux.pop();
        }
    }
    return result;
}

bool getSign(float num){
    return num > 0 ? 0 : 1;
}

int getPartInt(float num){
    return abs((int)(num));
}

vector<bool> toBinary(int num) {
    vector<bool> result;
    stack<bool> stckAux;
    int aux = num;

    while (aux >= 1){
        stckAux.push(aux%2);
        aux = aux/2;
    }
    while (!stckAux.empty()){
        result.push_back(stckAux.top());
        stckAux.pop();
    }
    return result;
}

float getPartDecimal(float num){
    return num < 0 ? num * (-1) - getPartInt(num) : num - getPartInt(num);
}

vector<bool> DecimalToBinary(float num){
    vector<bool> result;
    float auxPivot = getPartDecimal(num);

    for (int i = 0; i < 23; ++i) {
        auxPivot *= 2;
        if (auxPivot > 1){
            result.push_back(getPartInt(auxPivot));
            auxPivot -= 1;
        }else{
            result.push_back(getPartInt(auxPivot));
        }
    }
    return result;
}

int calculateExponent(string numberComplete){
    int result;

    int foundBitSignificativo = numberComplete.find('1');
    int foundComa = numberComplete.find(',');

    result = foundComa - foundBitSignificativo;
    result -=1;
    result += 127;
    return result;
}

vector<bool> calculateSignificando(string numberComplete){
    vector<bool> result;
    string aux = numberComplete;

    int initFromStr = aux.find('1') + 1;

    aux.erase(remove(aux.begin(), aux.end(), ','), aux.end());

    for (int i = initFromStr; i <aux.size() ; ++i) {
        result.push_back(aux[i] == '0' ? 0 : 1 );
    }

    return result;
}

void floatToBinaryNotation(float num){
    int parteEntera = getPartInt(num);
    int signo = getSign(num);

    vector<bool> parteEnteraBinaria = completeBits(toBinary(parteEntera), 8);
    vector<bool> parteDecimalBinaria = DecimalToBinary(num);



    string numberComplete;
    for (int i = 0; i < parteEnteraBinaria.size(); ++i) {
        numberComplete += parteEnteraBinaria[i] ? '1' : '0' ;
    }
    numberComplete.push_back(',');
    for (int i = 0; i < parteDecimalBinaria.size(); ++i) {
        numberComplete += parteDecimalBinaria[i] ? '1' : '0' ;
    }

    int exponente = calculateExponent(numberComplete);
    vector<bool> exponenteBinario = completeBits(toBinary(exponente),8);


    cout << "Signo :" << signo << endl;


    cout << "Exponente " << endl;
    printTest(exponenteBinario);


    vector<bool> significandoOrdenado = calculateSignificando(numberComplete);
    cout << "Significando Ordenado : " << endl;
    printTest(calculateSignificando(numberComplete));

    vector<bool> resultante;

    resultante.push_back(signo);

    // Parseo de 23 Bits
    for (int i = 0; i < exponenteBinario.size(); ++i) {
        resultante.push_back(exponenteBinario[i]);
    }
    for (int i = 0; i < significandoOrdenado.size(); ++i) {
        resultante.push_back(significandoOrdenado[i]);
    }

    for (int i = 0; i < resultante.size(); ++i) {
        cout << resultante[i];
    }

    cout << endl;

}

int main()
{

    float num;
    cin >> num;

    floatToBinaryNotation(num);

    return 0;
}