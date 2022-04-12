#include <iostream>
#include "MergeSort/mergesort.h"
#include "Palindrome/palindrome.h"


int main(){
    char cad[] = "anita lava la tinajsdhf";    
    delete_blanks(cad);
    printChain(cad);
		std::cout<<palindrome(cad)<<std::endl;

    int a[]= {12,30,40,42,48};
    int b[]= {211,213,215,217,219};    
    int c[10];
    int len = sizeof(a)/sizeof(a[0]);


    merge(a,b,c,len);
    print(c,10);
    std::cout<<std::endl;

		//std::cout<<1%4<<std::endl;
    return 0;
}