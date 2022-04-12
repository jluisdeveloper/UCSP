#include <bits/stdc++.h>
#include "TimeTester/Timer.hpp"

using namespace std;

void homework(vector<string>alphabet, int n_combs, string aux="" ) {
  /* TIEMPOS */
  //  Para 10 :
  //  0.00162004
  //  Para 15 :
  //  0.0221654
  //  Para 20 :
  //  0.544612
  //  Para 25 :
  //  17.4235
  //  Para 30 :
  //  586.383 => CASI 10 MINUTOS..!!

  // con 30 muere :'v satoru iwata xq me has abandonado :c


  string res = aux;
  if (n_combs > 0){
    for (int i = 0; i < alphabet.size(); ++i) {
      homework(alphabet,n_combs-1,aux+alphabet[i]);
    }
  }
//  else {
//    cout << endl;
//    cout << res;
//  }
}

void check_time( vector<int>cases ){
  for (int i = 0; i < cases.size(); ++i) {
    cout<< "Para "<< cases[i]<< " : ";
    Timer t;
    homework({"0", "1"},cases[i]);
  }
}


int main(){
  vector<int> cases = { 10, 15, 20, 25, 30 };
  check_time(cases);

  return 0;
}