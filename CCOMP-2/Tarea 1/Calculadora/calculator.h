#ifndef CALCULATOR_H_INCLUDED
#define CALCULATOR_H_INCLUDED

#include <vector>

class Calculator{
	public:
		Calculator(int, int, int);
		int calculateModule(int, int);
		int addition();
		int subtraction();
		int multiplication();
		std::vector<int> euclidesExtended();
		int inverse();

	private:
		int numb1;
		int numb2;
		int module;

};

#endif