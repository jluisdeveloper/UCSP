#ifndef CALENDAR_H_INCLUDED
#define CALENDAR_H_INCLUDED

#include <string>

class Calendar{	
	public:
		Calendar(int, int);
		bool leap_year(int);
		int zeller(int);
		int days_for_month(int);		
		std::string set_month_name(int);
		void print_month();
		void print_year();	
	
	private:
		int year;
		int month;
};


#endif