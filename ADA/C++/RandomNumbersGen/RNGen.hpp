#ifndef RNGEN_H_INCLUDED
#define RNGEN_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

template<class T>
class RNGen {

  public:
    RNGen(T* arr, int len){
        for (int i = 0; i < len; ++i) {
            *(arr + i) = (float)(rand() % 1000000)/10000;
        }
        
    }

};

#endif
