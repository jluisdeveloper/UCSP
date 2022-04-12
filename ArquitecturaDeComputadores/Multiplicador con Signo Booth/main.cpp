#include <bits/stdc++.h>

using namespace std;

template <int x>
void shift_add(bitset<x>& A, bitset<x>& Q, int& Q1) {
    int p, q, r;
    p = A[x-1];
    q = A[0];
    (A >>= 1);
    A[x-1] = p;
    r = Q[0];
    (Q >>= 1);
    Q[x-1] = q;
    Q1 = r;
}

template <int y>
bitset<y> add_binary(bitset<y> _ax, bitset<y> _by) {
    bool carry = 0;
    bitset<y> res;

    auto i = 0;
    while (i < y){
        res[i] = ((_ax[i] ^ _by[i]) ^ carry);
        carry = ((_ax[i]) & (_by[i]) | ((_ax[i]) & carry) | ((_by[i]) & carry));
        i++;
    }

    return res;
}

template <int z>
bitset<z> complement_twos(bitset<z> num) {
    return add_binary<z>((~num), 1);
}

template <int n>
void booth(int _M, int _Q) {
    bitset<n> M = _M, Q = _Q, A;
    int Q_1 = 0, Q_0;
    auto i = 0;
    while (i < n){
        //Q_0 = (Q & (1 << 0))
        Q_0 = Q[0];
        cout << A <<" "<< Q <<" "<< Q_1 <<" "<< M<<endl;
        if (Q_0 > Q_1) {
            A = add_binary<n>(A,complement_twos<n>(M)); // resta '10'
        }else if(Q_0 < Q_1) {
            A = add_binary<n>(A, M); // suma '01'
        }
        shift_add<n>(A,Q,Q_1);
        i++;
    }

    pair<bitset<n>, int>res(Q, (int)(Q.to_ullong()));
    cout << "Respuesta en Binario: "<<res.first << endl;
    cout << "Respuesta en Decimal: " << res.second << endl;
}


int main(){
//    bitset<8>b (-15) ;
//    bitset<8>c (1) ;
//    bitset<8>d = (~b|c)  ;
//
//
//    cout << b <<" - " << (int)(d.to_ullong()) <<endl;

    const auto bits = 8;
    int M, Q;
    cout << "Algoritmo de Booth's: " << endl;
    cout << "M: "; cin >> M; cout << endl;
    cout << "Q: "; cin >> Q; cout << endl;
    booth<bits>(M, Q);
}