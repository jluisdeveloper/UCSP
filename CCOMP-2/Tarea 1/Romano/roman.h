#ifndef ROMAN_H_INCLUDED
#define ROMAN_H_INCLUDED

class Roman{
	public:
		Roman(int);
		void print();

	private:
		int number;
		int units;
		int tens;
		int hundreds;
		int thousands;
		int backrest;
};

#endif