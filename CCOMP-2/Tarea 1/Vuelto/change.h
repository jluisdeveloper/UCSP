#ifndef CHANGE_H_INCLUDED
#define CHANGE_H_INCLUDED
#include <string>

class Change{
	public:
		Change(std::string);
		int getPen(std::string);
		std::string getCents(std::string);
		void print();

	private:
		std::string amount;
		int pen;
		int cents;
};

#endif