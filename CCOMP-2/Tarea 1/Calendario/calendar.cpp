#include <iostream>
#include "calendar.h"

Calendar::Calendar(int _year, int _month){
	year = _year;
	month = _month;
}

int Calendar::zeller(int _month){
	int aux = (14 - _month) / 12;
	int y = year - aux;
	int m = _month + 12 * aux - 2;
	int day = 1;
	int result;
	result = (day + y + y/4 - y/100 + y/400 + (31 * m)/12 ) % 7;

	return result;
}

bool Calendar::leap_year(int _year){
	if (_year % 4 == 0){
		if (_year % 100 == 0){
			if (_year % 400 == 0){
				return true;
			}
			else{
				return false;
			}
		}
		else {
			return true;
		}		
	}
	else {
		return false;
	}
}

int Calendar::days_for_month(int month){
	int result;
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12 ){
		result = 31;
	} 
	else if (month == 2){
		if (leap_year(year)){
			result = 29;
		}
		else {
			result = 28;
		}
	}
	else {
		result = 30;
	}
	return result;
}

std::string Calendar::set_month_name(int _month){
	std::string result;

	switch (_month){
		case 1:
			result = "Enero";
			return result;

		case 2:
			result = "Febrero";
			return result;

		case 3:
			result = "Marzo";
			return result;

		case 4:
			result = "Abril";
			return result;

		case 5:
			result = "Mayo";
			return result;

		case 6:
			result = "Junio";
			return result;

		case 7:
			result = "Julio";
			return result;

		case 8:
			result = "Agosto";
			return result;

		case 9:
			result = "Septiembre";
			return result;

		case 10:
			result = "Octubre";
			return result;

		case 11:
			result = "Noviembre";
			return result;

		case 12:
			result = "Diciembre";
			return result;
	
		default:
			result = "Mes Incorrecto";
			return result;
	}
}

void Calendar::print_month(){
	std::cout<< set_month_name(month) << " del " << year << std::endl;
	std::cout<< "Dom\tLun\tMar\tMie\tJue\tVie\tSab" << std::endl;
	int days = days_for_month(month);
	int aux = 0;
	int space_count = zeller(month);
	for(int j = 1; j <= space_count; j++){			
		std::cout<< "\t";
		aux++;
	}
	for(int k = 1; k <= days; k++){
		if (k < 10) {
			std::cout<< " ";
		}

		std::cout << k << "\t";
		aux++;
		if (aux ==7 ){
			std::cout<< std::endl;
			aux = 0;
		}
	}
	std::cout<< std::endl;
}

void Calendar::print_year(){
	std::cout<< "Calendario del Año  " << year << std::endl;
	for(int i = 1; i <= 12; i++){
		std::cout<< std::endl;
		std::cout<< "Mes : " << set_month_name(i) << std::endl;
		std::cout<< "Dom\tLun\tMar\tMie\tJue\tVie\tSab" << std::endl;
		int days = days_for_month(i);
		int aux = 0;
		int space_count = zeller(i);
		for(int j = 1; j <= space_count; j++){			
			std::cout<< "\t";
			aux++;
		}
		for(int k = 1; k <= days; k++){
			if (k < 10) {
				std::cout<< " ";
			}
			std::cout << k << "\t";
			aux++;
			if (aux ==7 ){
				std::cout<< std::endl;
				aux = 0;
			}
		}
		std::cout<< std::endl;		
	}	
}