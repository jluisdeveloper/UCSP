#include <bits/stdc++.h>

using namespace std;

int moneda(int cant_dev, vector<int> monedas){
   vector<vector<int>> T;

   T.assign(monedas.size()+1, vector<int>(cant_dev+1, -1));
   
   for(short i = 0; i <= monedas.size(); ++i ){
       T[i][0] = 0;
   }

   /* 0 x x x x x
    * 0 x x x x x
    * 0 x x x x x
    * 0 x x x x x
    * */


   for(short j=1; j<= cant_dev; ++j ){
       T[0][j] = 999999;
   }

   /* 0 Y Y Y Y Y Y
    * 0 x x x x x x
    * 0 x x x x x x
    * 0 x x x x x x
    *
    * Y = infinito o algo muy grande 999999
    * */

   /* for(int i = 0; i < T.size(); i++ ){ */
   /*     for(int j = 0; j < T[0].size(); j++){ */
   /*         cout << T[i][j]<< " "; */
   /*     } */
   /*     cout << endl; */
   /* } */


   for(int i = 1; i <= monedas.size(); ++i){
       for(int j=1; j<= cant_dev; ++j){
           // Si la moneda es mayor a la cantidad del vuelto
           if(monedas[i-1] > j){
               T[i][j] = T[i-1][j];                
           }else {
               // caso contrario se calcula cual es el minimo
               T[i][j] = min(T[i-1][j], T[i][j-monedas[i-1]] + 1 ); 
           }
       }
   }
   
    
   return T[monedas.size()][cant_dev];
}


int main(){

    vector<int> mons = {2, 3, 5};
    int ctdv = 11;

    cout << moneda(ctdv, mons)<<endl;


    return 0;
}
