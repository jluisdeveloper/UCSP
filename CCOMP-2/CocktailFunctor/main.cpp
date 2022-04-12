#include <iostream>
#include "cocktail.h"
using namespace std;

template<typename T>
class asc{
public:
	bool operator()(T a , T b){
		return a > b;
	}
};

template<typename T>
class desc{
public:
	bool operator()(T a , T b){
		return a < b;
	}
};

int main() {
	int A[]={5,9,7,8,1};

	Cocktail <int,asc<int>> coctailxD(A,5);
	coctailxD.sort();
  coctailxD.print();
	return 0;
}