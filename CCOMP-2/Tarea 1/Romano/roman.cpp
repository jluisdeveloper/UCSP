#include <iostream>

#include "roman.h"

Roman::Roman(int _number){
  number = _number;
  backrest = number;
  units = number % 10;
  number = number / 10;
  tens = number % 10;
  number = number / 10;
  hundreds = number % 10;
  number = number / 10;
  thousands = number % 10;
  number = number / 10;
}

void Roman::print(){
  std::cout<<"Numero a convertir :" << backrest <<std::endl;

  switch (thousands) {
    case 1: std::cout<<"M"; break;
    case 2: std::cout<<"MM"; break;
    case 3: std::cout<<"MMM"; break;
    case 4: std::cout<<"IV"; break;
    case 5: std::cout<<"V"; break;
  }
 
  switch (hundreds) {
    case 1: std::cout<<"C"; break;
    case 2: std::cout<<"CC"; break;
    case 3: std::cout<<"CCC"; break;
    case 4: std::cout<<"CD"; break;
    case 5: std::cout<<"D"; break;
    case 6: std::cout<<"DC"; break;
    case 7: std::cout<<"DCC"; break;
    case 8: std::cout<<"DCCC"; break;
    case 9: std::cout<<"CM"; break; 
  }
 
  switch (tens) {
    case 1: std::cout<<"X"; break;
    case 2: std::cout<<"XX"; break;
    case 3: std::cout<<"XXX"; break;
    case 4: std::cout<<"XL"; break;
    case 5: std::cout<<"L"; break;
    case 6: std::cout<<"LX"; break;
    case 7: std::cout<<"LXX"; break;
    case 8: std::cout<<"LXXX"; break;
    case 9: std::cout<<"XC"; break; 
  }
 
  switch (units) {
    case 1: std::cout<<"I"; break;
    case 2: std::cout<<"II"; break;
    case 3: std::cout<<"III"; break;
    case 4: std::cout<<"IV"; break;
    case 5: std::cout<<"V"; break;
    case 6: std::cout<<"VI"; break;
    case 7: std::cout<<"VII"; break;
    case 8: std::cout<<"VIII"; break;
    case 9: std::cout<<"IX"; break;
  }

  std::cout<< std::endl;
}