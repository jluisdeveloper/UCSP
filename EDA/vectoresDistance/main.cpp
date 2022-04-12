#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>
#include <math.h>

#include "./Timer/Timer.hpp"

void set_data_random(std::vector< std::vector<int>> &vec,int N, int dimensions ) {
    vec.resize(N);
    for(auto &aux : vec){
      generate(aux.begin(),aux.end(),rand);
      //sort(aux.begin(),aux.end(), std::greater<int>());
    }

}

double euclidean_distance(std::vector<int> &from, std::vector<int> &to) {
    double distance = 0.0;
    for (short i = 0; i < from.size() ; i++) {
        distance += pow(from[i] - to[i],2);
    }
    return sqrt(distance);
}

void get_time_for(std::vector< std::vector<int> > data_){
    Timer T;
    for (auto &iter : data_){ 
      for (auto &iter2 : data_){
	euclidean_distance(iter, iter2);
      }
    }
}

int main() {
 
    std::vector<std::vector<std::vector<int>>> VEC;
    int tamanos[3] = { 10000,20000,25000 };
    int dimensiones[4] = { 5,10,15,20 };
    for (int tam = 0; tam < 3; tam++) {
        for (int dim = 0; dim < 4; dim++) {
	    std::vector<std::vector<int>> DS;
            set_data_random(DS, tamanos[tam], dimensiones[dim]);
            VEC.push_back(DS);
        }
    }


    for (auto &svec : VEC) {
      get_time_for(svec);
    }


  //get_time_for(vec10K);


  // srand((unsigned int)time(NULL));
  //const int kSize = 10;
  //std::vector<int> array(kSize);
  //generate(array.begin(), array.end(),
   //        rand);  // generamos 10 numeros aleatorios
  //sort(array.begin(), array.end(), std::greater<int>());  // de mayor a menor
  
  //std::vector<int> array;
  //set_data_random(array, 5);
  
  //std::vector<int> array2;
  //set_data_random(array2, 5);

  //std::cout<< euclidean_distance(array, array2)<<"\n";

  //copy(array.begin(), array.end(), std::ostream_iterator<int>(std::cout, "\n"));

  return 0;
}
