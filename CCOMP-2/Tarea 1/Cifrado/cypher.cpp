#include <iostream>
#include <vector>
#include <string>

#include "cypher.h"

Cypher::Cypher(int _privateKey){

	privateKey = _privateKey;

	if (euclidesExtended(privateKey,256)[0] != 1){
		std::cout << "La llave escogida no es permitida :/" << std::endl;
		return;
	}
	else{
		FILE * file = fopen("mensaje.txt", "rb");
		if (file == NULL){
			message = "Hubo un error en cargar el archivo pero encripta este mensaje";
		}

		char aux;

		while(feof(file) == 0){
			aux = fgetc(file);
			message.push_back(aux);
		}

		fclose(file);

		int len = message.size();
		message.erase(len-1);

		
		publicKey = inverse(privateKey,256);
		

		std::cout<< "Llave Privada" <<std::endl;
		std::cout<< privateKey <<std::endl;
		std::cout<< "Llave Publica" <<std::endl;
		std::cout<< publicKey <<std::endl;
	}	
}

int Cypher::calculateModule(int _number, int _module){
	int aux;
	int result;

	aux = _number / _module;
	result = _number - (aux * _module);

	if (result < 0){
		aux--;
		result = result + _module;
	}

	return result;
}

std::vector<int> Cypher::euclidesExtended(int _number, int _module){
	int a = _number;
  int b = _module;
  int d=0,x=0,y=0;
  int x1=0,x2=0,y1=0,y2=0,q=0,r=0;
  std::vector<int> result;
  if (b ==0){
      d = a;
      x = 1;
      y = 0;
      result.push_back(d);
      result.push_back(x);
      result.push_back(y);
      return result;
  }
  x2 = 1;
  x1 = 0;
  y2 = 0;
  y1 = 1;

  while(b>0){
      q = a/b;
      r = a -(q*b);
      x = x2-(q*x1);
      y = y2-(q*y1);
      a = b;
      b = r;
      x2 = x1;
      x1 = x;
      y2 = y1;
      y1 = y;
  }
  d = a;
  x = x2;
  y = y2;
  result.push_back(d);
  result.push_back(x);
  result.push_back(y);
  return result;
}

int Cypher::inverse(int _number, int _module){
	int result = euclidesExtended(_number,_module)[1];

	if(result < 0){
    result = result + _module;
    return result;
  }
    return result;
}

std::string Cypher::crypt(){
	FILE * cipher = fopen("encriptado.txt", "w");
	std::string result;
	int len = message.size();
	int aux;
	char aux2;

	if (cipher == NULL){
		result = "Error al Crear Archivo Verifica el nombre";
		return result;
	}

	for (int i=0; i<len; i++){
		aux = message[i];
		aux = aux * privateKey;
		aux = calculateModule(aux,256);
		aux2 = aux;
		result += aux2;
		fputc(aux2, cipher);
	}
	fflush(cipher);
	fclose(cipher);
	return result;
}

std::string Cypher::decrypt(std::string _cipher, int _publicKey){
	FILE * decipher = fopen("desencriptado.txt", "w");
	std::string result;
	int len = _cipher.size();
	int aux;
	char aux2;

	if (decipher == NULL){
		result = "Error al Crear Archivo Verifica el nombre";
		return result;
	}

	for (int i = 0; i < len; i++){
		aux = _cipher[i];
		aux = aux * _publicKey;
		aux = calculateModule(aux,256);
		aux2 = aux;
		result += aux2;
		fputc(aux2, decipher);
	}
	fflush(decipher);
	fclose(decipher);

	return result;
}