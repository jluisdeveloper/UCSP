#include <iostream>
#include "palindrome.h"

int lenChain(char* a){
	int result=0;
	for(char* i = a; *i != '\0'; i++){
		result++;
	}
	return result;    
}

void printChain(char* a){
	for(char* i = a; *i != '\0'; i++) {
		std::cout<<*i;
	}
	std::cout<<std::endl;
}

int space_blanks(char* a){
	int result;
	for(char* i = a; *i != '\0'; i++){
		if(*i == ' '){
			result++;
		}
	}
	return result;
}

void delete_blanks(char* a){    
	int len = lenChain(a);
	for(int i = 0; i < space_blanks(a); i++){  
		char* p = a;
		char tmp;    
		for(; p < a+len ; p++){
			if(*p == ' '){
				tmp = *p;
				*p = *(p+1);
				*(p+1) = tmp;
			}
		}
	}  
}

bool palindrome(char* a){
	delete_blanks(a);
	char* start = a;
	char* end = a+lenChain(a)-1;
	for(; start != end ; start++,end--){
		if(*start==*end){
			return true;
		}
		return false;
	}
}