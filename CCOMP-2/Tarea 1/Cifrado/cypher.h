#ifndef CYPHER_H_INCLUDED
#define CYPHER_H_INCLUDED

#include <string>
#include <vector>

class Cypher{
	public:
		Cypher(int);
		int publicKey;
		int privateKey;
		std::string message;
		int calculateModule(int, int);
		std::vector<int> euclidesExtended(int, int);
		int inverse(int ,int );

		std::string crypt();
		std::string decrypt(std::string, int );

	private:
		
};

#endif