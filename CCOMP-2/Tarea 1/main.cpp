#include <iostream>
#include <string>
#include <vector>

#include "Calendario/calendar.h"
#include "Vuelto/change.h"
#include "Romano/roman.h"
#include "Letras/letters.h"
#include "Calculadora/calculator.h"
#include "Cifrado/cypher.h"


int main(){

  Calendar Date(1976,2);
  Date.print_year();
  //Date.print_month();

  /* std::string S = "1554.90";
	Change A(S);
	A.print(); */

  /* int S = 1974;
	Roman A(S);
	A.print(); */

	/* Letters A(125689415); */

	/* Calculator A(79,7,256);
	std::cout << A.inverse() <<std::endl;  */	

	/* Cypher A(21);
	std::cout<< A.crypt() <<std::endl;
	std::cout<< A.decrypt(A.crypt(),A.publicKey) <<std::endl; */

	return 0;

	/* g++ main.cpp Calendario/calendar.cpp Vuelto/change.cpp Romano/roman.cpp Letras/letters.cpp Calculadora/calculator.cpp Cifrado/cypher.cpp -o Main */
}

