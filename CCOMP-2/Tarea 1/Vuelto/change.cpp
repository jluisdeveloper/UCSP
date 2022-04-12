#include <iostream>
#include "change.h"

Change::Change(std::string _amount){
	amount = _amount;
	pen = getPen(amount);
	if (pen<0)
		pen = pen*(-1);
	cents = getPen(getCents(amount));
}

int Change::getPen(std::string _amount){
	int result;
  result = stoi(_amount);
  return result;
}

std::string Change::getCents(std::string _amount){
	std::string result;
	result.push_back(_amount[_amount.find('.')+1]);
	result.push_back(_amount[_amount.find('.')+2]);
	return result;
}

void Change::print(){

	std::cout<<"MONTO:  " <<pen<<"."<<cents<<std::endl<<std::endl;

	while(pen != 0 ){
		if (pen/200 == 1)
			std::cout << "Se necesitan "<<pen/200<<" billete de 200 S/."<<std::endl;
		if (pen/200 > 1)
			std::cout << "Se necesitan "<<pen/200<<" billetes de 200 S/."<<std::endl;
		pen = pen%200;

		if (pen/100 == 1)
			std::cout << "Se necesitan "<<pen/100<<" billete de 100 S/."<<std::endl;
		pen = pen%100;

		if (pen/50 > 0)
			std::cout << "Se necesitan "<<pen/50<<" billete de 50 S/."<<std::endl;
		pen = pen%50;

		if (pen/20 == 1)
			std::cout << "Se necesitan "<<pen/20<<" billete de 20 S/."<<std::endl;
		if (pen/20 > 1)
			std::cout << "Se necesitan "<<pen/20<<" billetes de 20 S/."<<std::endl;
		pen = pen%20;

		if (pen/10 > 0)
			std::cout << "Se necesitan "<<pen/10<<" billete de 10 S/."<<std::endl;
		pen = pen%10;

		if (pen/5 > 0)
			std::cout << "Se necesitan "<<pen/5<<" moneda de 5 S/."<<std::endl;
		pen = pen%5;

		if (pen/2 == 1)
			std::cout << "Se necesitan "<<pen/2<<" moneda de 2 S/."<<std::endl;
		if (pen/2 > 1)
			std::cout << "Se necesitan "<<pen/2<<" monedas de 2 S/."<<std::endl;
		pen = pen%2;

		if (pen/1 > 0)
			std::cout << "Se necesitan "<<pen/1<<" moneda de 1 S/."<<std::endl;
		pen = pen%1;
	}

	while(cents != 0 ){
		if (cents/50 == 1)
			std::cout << "Se necesitan "<<cents/50<<" moneda de 0.50 S/."<<std::endl;
		cents = cents%50;

		if (cents/20 == 1)
			std::cout << "Se necesitan "<<cents/20<<" moneda de 0.20 S/."<<std::endl;
		if (cents/20 > 1)
			std::cout << "Se necesitan "<<cents/20<<" monedas de 0.20 S/."<<std::endl;
		cents = cents%20;

		if (cents/10 > 0)
			std::cout << "Se necesitan "<<cents/10<<" moneda de 0.10 S/."<<std::endl;
		cents = cents%10;

		if (cents >= 0)
			break;
	}
}