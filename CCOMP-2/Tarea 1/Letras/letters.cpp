#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "letters.h"

Letters::Letters(int _number){
    number = _number;
    unidad = number % 10;
    decena = (number % 100 - unidad) / 10;
    centena = (number % 1000 - unidad - decena) / 100;
    unidad_millar = (number % 10000 - unidad - decena - centena) / 1000;
    decena_millar = (number % 100000 - unidad - decena - centena - unidad_millar) / 10000;
    centena_millar = (number % 1000000 - unidad - decena - centena - unidad_millar - decena_millar) / 100000;
    unidad_millon = (number % 10000000 - unidad - decena - centena - unidad_millar - decena_millar - centena_millar) / 1000000;
    decena_millon = (number % 100000000 - unidad - decena - centena - unidad_millar - decena_millar - centena_millar - unidad_millon) / 10000000;
    centena_millon = (number % 1000000000 - unidad - decena - centena - unidad_millar - decena_millar - centena_millar - unidad_millon - decena_millon) / 100000000;

    vector<string> Expresion_Unidades = {"un","uno","dos","tres","cuatro","cinco","seis","siete","ocho","nueve"};
    vector<string> Expresion_Decenas = {"diez","veinte","treinta","cuarenta","cincuenta","sesenta","setenta", "ochenta", "noventa"};
    vector<string> Expresion_Decenas_Especiales = {"once","doce","trece","catorce","quince"};
    vector<string> Expresion_Decenas_Compuestas = {"dieci","veinti"};
    vector<string> Expresion_Centenas = {"cien","ciento", "doscientos", "trescientos", "cuatrocientos", "quinientos", "seiscientos", "setecientos", "ochocientos", "novecientos"};
    vector<string> Expresion_Millares = {"mil"};
    vector<string> Expresion_Millones = {"millon", "millones"};

    string result = "";

    switch (centena_millon){
			case 1:
				if (decena_millon == 0 and unidad_millon == 0) {
					result += Expresion_Centenas[0];
					result += " ";
				}else{
					result += Expresion_Centenas[1];
					result += " ";
				}          
				break;
			case 2:
				result += Expresion_Centenas[2];
				result += " ";
				break;
			case 3:
				result += Expresion_Centenas[3];
				result += " ";
				break;
			case 4:
				result += Expresion_Centenas[4];
				result += " ";
				break;
			case 5:
				result += Expresion_Centenas[5];
				result += " ";
				break;
			case 6:
				result += Expresion_Centenas[6];
				result += " ";
				break;
			case 7:
				result += Expresion_Centenas[7];
				result += " ";
				break;
			case 8:
				result += Expresion_Centenas[8];
				result += " ";
				break;
			case 9:
				result += Expresion_Centenas[9];
				result += " ";
				break;
			default:
					break;
    }
		switch (decena_millon){
			case 0:
				switch (unidad_millon){
					case 1:
						result += Expresion_Unidades[0];
						result += " ";					
						break;
					case 2:
						result += Expresion_Unidades[2];
						result += " ";						
						break;
					case 3:
						result += Expresion_Unidades[3];
						result += " ";						
						break;
					case 4:
						result += Expresion_Unidades[4];
						result += " ";						
						break;
					case 5:
						result += Expresion_Unidades[5];
						result += " ";						
						break;
					case 6:
						result += Expresion_Unidades[6];
						result += " ";						
						break;
					case 7:
						result += Expresion_Unidades[7];
						result += " ";						
						break;
					case 8:
						result += Expresion_Unidades[8];
						result += " ";						
						break;
					case 9:
						result += Expresion_Unidades[9];
						result += " ";						
						break;
				
					default:
						break;
				}
				break;
			case 1:
				switch (unidad_millon){
					case 0:
						result += Expresion_Decenas[0];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas_Especiales[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas_Especiales[1];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas_Especiales[2];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas_Especiales[3];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas_Especiales[4];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas_Compuestas[0];
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas_Compuestas[0];
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas_Compuestas[0];
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas_Compuestas[0];
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 2:
				switch (unidad_millon){
					case 0:
						result += Expresion_Decenas[1];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas_Compuestas[1];
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas_Compuestas[1];
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas_Compuestas[1];
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas_Compuestas[1];
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas_Compuestas[1];
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas_Compuestas[1];						
						result += Expresion_Unidades[6];
						result += " ";						
						break;
					case 7:
						result += Expresion_Decenas_Compuestas[1];
						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas_Compuestas[1];
						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas_Compuestas[1];
						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 3:
				switch (unidad_millon){
					case 0:
						result += Expresion_Decenas[2];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas[2];
						result += " y ";
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas[2];
						result += " y ";
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas[2];
						result += " y ";
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas[2];
						result += " y ";
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas[2];
						result += " y ";
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas[2];
						result += " y ";						
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas[2];
						result += " y ";						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas[2];
						result += " y ";						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas[2];
						result += " y ";						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 4:
				switch (unidad_millon){
					case 0:
						result += Expresion_Decenas[3];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas[3];
						result += " y ";
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas[3];
						result += " y ";
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas[3];
						result += " y ";
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas[3];
						result += " y ";
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas[3];
						result += " y ";
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas[3];
						result += " y ";						
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas[3];
						result += " y ";						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas[3];
						result += " y ";						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas[3];
						result += " y ";						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 5:
				switch (unidad_millon){
					case 0:
						result += Expresion_Decenas[4];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas[4];
						result += " y ";
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas[4];
						result += " y ";
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas[4];
						result += " y ";
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas[4];
						result += " y ";
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas[4];
						result += " y ";
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas[4];
						result += " y ";						
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas[4];
						result += " y ";						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas[4];
						result += " y ";						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas[4];
						result += " y ";						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 6:
				switch (unidad_millon){
					case 0:
						result += Expresion_Decenas[5];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas[5];
						result += " y ";
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas[5];
						result += " y ";
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas[5];
						result += " y ";
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas[5];
						result += " y ";
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas[5];
						result += " y ";
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas[5];
						result += " y ";						
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas[5];
						result += " y ";						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas[5];
						result += " y ";						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas[5];
						result += " y ";						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 7:
				switch (unidad_millon){
					case 0:
						result += Expresion_Decenas[6];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas[6];
						result += " y ";
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas[6];
						result += " y ";
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas[6];
						result += " y ";
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas[6];
						result += " y ";
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas[6];
						result += " y ";
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas[6];
						result += " y ";						
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas[6];
						result += " y ";						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas[6];
						result += " y ";						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas[6];
						result += " y ";						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 8:
				switch (unidad_millon){
					case 0:
						result += Expresion_Decenas[7];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas[7];
						result += " y ";
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas[7];
						result += " y ";
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas[7];
						result += " y ";
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas[7];
						result += " y ";
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas[7];
						result += " y ";
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas[7];
						result += " y ";						
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas[7];
						result += " y ";						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas[7];
						result += " y ";						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas[7];
						result += " y ";						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 9:
				switch (unidad_millon){
					case 0:
						result += Expresion_Decenas[8];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas[8];
						result += " y ";
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas[8];
						result += " y ";
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas[8];
						result += " y ";
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas[8];
						result += " y ";
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas[8];
						result += " y ";
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas[8];
						result += " y ";						
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas[8];
						result += " y ";						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas[8];
						result += " y ";						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas[8];
						result += " y ";						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}

		if (unidad_millon != 0 || decena_millon != 0 || centena_millon != 0){
			if (unidad_millon > 1 || unidad_millon == 0){
				result += Expresion_Millones[1];
				result += " ";
			}
			if (unidad_millon == 1){
				if (decena_millon == 0 && centena_millon == 0){
					result += Expresion_Millones[0];
					result += " ";
				}else{
					result += Expresion_Millones[1];
					result += " ";
				}
			}
		}

		switch (centena_millar){
			case 1:
				if (decena_millar == 0 and unidad_millar == 0) {
					result += Expresion_Centenas[0];
					result += " ";
				}else{
					result += Expresion_Centenas[1];
					result += " ";
				}
				break;
			case 2:
				result += Expresion_Centenas[2];
				result += " ";
				break;
			case 3:
				result += Expresion_Centenas[3];
				result += " ";
				break;
			case 4:
				result += Expresion_Centenas[4];
				result += " ";
				break;
			case 5:
				result += Expresion_Centenas[5];
				result += " ";
				break;
			case 6:
				result += Expresion_Centenas[6];
				result += " ";
				break;
			case 7:
				result += Expresion_Centenas[7];
				result += " ";
				break;
			case 8:
				result += Expresion_Centenas[8];
				result += " ";
				break;
			case 9:
				result += Expresion_Centenas[9];
				result += " ";
				break;
			default:
					break;
		}
		switch (decena_millar){
			case 0:
				switch (unidad_millar){
					case 1:
						//result += "";
						result += "";					
						break;
					case 2:
						result += Expresion_Unidades[2];
						result += " ";						
						break;
					case 3:
						result += Expresion_Unidades[3];
						result += " ";						
						break;
					case 4:
						result += Expresion_Unidades[4];
						result += " ";						
						break;
					case 5:
						result += Expresion_Unidades[5];
						result += " ";						
						break;
					case 6:
						result += Expresion_Unidades[6];
						result += " ";						
						break;
					case 7:
						result += Expresion_Unidades[7];
						result += " ";						
						break;
					case 8:
						result += Expresion_Unidades[8];
						result += " ";						
						break;
					case 9:
						result += Expresion_Unidades[9];
						result += " ";						
						break;
				
					default:
						break;
				}
				break;
			case 1:
				switch (unidad_millar){
					case 0:
						result += Expresion_Decenas[0];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas_Especiales[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas_Especiales[1];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas_Especiales[2];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas_Especiales[3];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas_Especiales[4];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas_Compuestas[0];
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas_Compuestas[0];
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas_Compuestas[0];
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas_Compuestas[0];
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 2:
				switch (unidad_millar){
					case 0:
						result += Expresion_Decenas[1];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas_Compuestas[1];
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas_Compuestas[1];
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas_Compuestas[1];
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas_Compuestas[1];
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas_Compuestas[1];
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas_Compuestas[1];						
						result += Expresion_Unidades[6];
						result += " ";						
						break;
					case 7:
						result += Expresion_Decenas_Compuestas[1];
						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas_Compuestas[1];
						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas_Compuestas[1];
						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 3:
				switch (unidad_millar){
					case 0:
						result += Expresion_Decenas[2];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas[2];
						result += " y ";
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas[2];
						result += " y ";
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas[2];
						result += " y ";
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas[2];
						result += " y ";
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas[2];
						result += " y ";
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas[2];
						result += " y ";						
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas[2];
						result += " y ";						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas[2];
						result += " y ";						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas[2];
						result += " y ";						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 4:
				switch (unidad_millar){
					case 0:
						result += Expresion_Decenas[3];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas[3];
						result += " y ";
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas[3];
						result += " y ";
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas[3];
						result += " y ";
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas[3];
						result += " y ";
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas[3];
						result += " y ";
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas[3];
						result += " y ";						
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas[3];
						result += " y ";						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas[3];
						result += " y ";						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas[3];
						result += " y ";						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 5:
				switch (unidad_millar){
					case 0:
						result += Expresion_Decenas[4];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas[4];
						result += " y ";
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas[4];
						result += " y ";
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas[4];
						result += " y ";
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas[4];
						result += " y ";
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas[4];
						result += " y ";
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas[4];
						result += " y ";						
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas[4];
						result += " y ";						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas[4];
						result += " y ";						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas[4];
						result += " y ";						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 6:
				switch (unidad_millar){
					case 0:
						result += Expresion_Decenas[5];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas[5];
						result += " y ";
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas[5];
						result += " y ";
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas[5];
						result += " y ";
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas[5];
						result += " y ";
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas[5];
						result += " y ";
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas[5];
						result += " y ";						
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas[5];
						result += " y ";						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas[5];
						result += " y ";						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas[5];
						result += " y ";						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 7:
				switch (unidad_millar){
					case 0:
						result += Expresion_Decenas[6];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas[6];
						result += " y ";
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas[6];
						result += " y ";
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas[6];
						result += " y ";
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas[6];
						result += " y ";
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas[6];
						result += " y ";
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas[6];
						result += " y ";						
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas[6];
						result += " y ";						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas[6];
						result += " y ";						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas[6];
						result += " y ";						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 8:
				switch (unidad_millar){
					case 0:
						result += Expresion_Decenas[7];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas[7];
						result += " y ";
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas[7];
						result += " y ";
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas[7];
						result += " y ";
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas[7];
						result += " y ";
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas[7];
						result += " y ";
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas[7];
						result += " y ";						
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas[7];
						result += " y ";						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas[7];
						result += " y ";						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas[7];
						result += " y ";						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 9:
				switch (unidad_millar){
					case 0:
						result += Expresion_Decenas[8];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas[8];
						result += " y ";
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas[8];
						result += " y ";
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas[8];
						result += " y ";
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas[8];
						result += " y ";
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas[8];
						result += " y ";
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas[8];
						result += " y ";						
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas[8];
						result += " y ";						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas[8];
						result += " y ";						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas[8];
						result += " y ";						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}

		if (unidad_millar != 0 || decena_millar != 0 || centena_millar != 0){
			result += Expresion_Millares[0];
			result += " ";
		}
		
    
		switch (centena){
			case 1:
				if (decena == 0 and unidad == 0) {
					result += Expresion_Centenas[0];
					result += " ";
				}else{
					result += Expresion_Centenas[1];
					result += " ";
				}          
				break;
			case 2:
				result += Expresion_Centenas[2];
				result += " ";
				break;
			case 3:
				result += Expresion_Centenas[3];
				result += " ";
				break;
			case 4:
				result += Expresion_Centenas[4];
				result += " ";
				break;
			case 5:
				result += Expresion_Centenas[5];
				result += " ";
				break;
			case 6:
				result += Expresion_Centenas[6];
				result += " ";
				break;
			case 7:
				result += Expresion_Centenas[7];
				result += " ";
				break;
			case 8:
				result += Expresion_Centenas[8];
				result += " ";
				break;
			case 9:
				result += Expresion_Centenas[9];
				result += " ";
				break;
			default:
					break;
    }
		switch (decena){
			case 0:
				switch (unidad){
					case 1:
						result += Expresion_Unidades[1];
						result += " ";					
						break;
					case 2:
						result += Expresion_Unidades[2];
						result += " ";						
						break;
					case 3:
						result += Expresion_Unidades[3];
						result += " ";						
						break;
					case 4:
						result += Expresion_Unidades[4];
						result += " ";						
						break;
					case 5:
						result += Expresion_Unidades[5];
						result += " ";						
						break;
					case 6:
						result += Expresion_Unidades[6];
						result += " ";						
						break;
					case 7:
						result += Expresion_Unidades[7];
						result += " ";						
						break;
					case 8:
						result += Expresion_Unidades[8];
						result += " ";						
						break;
					case 9:
						result += Expresion_Unidades[9];
						result += " ";						
						break;
				
					default:
						break;
				}
				break;
			case 1:
				switch (unidad){
					case 0:
						result += Expresion_Decenas[0];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas_Especiales[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas_Especiales[1];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas_Especiales[2];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas_Especiales[3];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas_Especiales[4];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas_Compuestas[0];
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas_Compuestas[0];
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas_Compuestas[0];
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas_Compuestas[0];
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 2:
				switch (unidad){
					case 0:
						result += Expresion_Decenas[1];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas_Compuestas[1];
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas_Compuestas[1];
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas_Compuestas[1];
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas_Compuestas[1];
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas_Compuestas[1];
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas_Compuestas[1];						
						result += Expresion_Unidades[6];
						result += " ";						
						break;
					case 7:
						result += Expresion_Decenas_Compuestas[1];
						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas_Compuestas[1];
						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas_Compuestas[1];
						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 3:
				switch (unidad){
					case 0:
						result += Expresion_Decenas[2];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas[2];
						result += " y ";
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas[2];
						result += " y ";
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas[2];
						result += " y ";
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas[2];
						result += " y ";
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas[2];
						result += " y ";
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas[2];
						result += " y ";						
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas[2];
						result += " y ";						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas[2];
						result += " y ";						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas[2];
						result += " y ";						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 4:
				switch (unidad){
					case 0:
						result += Expresion_Decenas[3];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas[3];
						result += " y ";
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas[3];
						result += " y ";
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas[3];
						result += " y ";
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas[3];
						result += " y ";
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas[3];
						result += " y ";
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas[3];
						result += " y ";						
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas[3];
						result += " y ";						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas[3];
						result += " y ";						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas[3];
						result += " y ";						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 5:
				switch (unidad){
					case 0:
						result += Expresion_Decenas[4];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas[4];
						result += " y ";
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas[4];
						result += " y ";
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas[4];
						result += " y ";
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas[4];
						result += " y ";
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas[4];
						result += " y ";
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas[4];
						result += " y ";						
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas[4];
						result += " y ";						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas[4];
						result += " y ";						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas[4];
						result += " y ";						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 6:
				switch (unidad){
					case 0:
						result += Expresion_Decenas[5];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas[5];
						result += " y ";
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas[5];
						result += " y ";
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas[5];
						result += " y ";
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas[5];
						result += " y ";
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas[5];
						result += " y ";
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas[5];
						result += " y ";						
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas[5];
						result += " y ";						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas[5];
						result += " y ";						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas[5];
						result += " y ";						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 7:
				switch (unidad){
					case 0:
						result += Expresion_Decenas[6];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas[6];
						result += " y ";
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas[6];
						result += " y ";
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas[6];
						result += " y ";
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas[6];
						result += " y ";
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas[6];
						result += " y ";
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas[6];
						result += " y ";						
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas[6];
						result += " y ";						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas[6];
						result += " y ";						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas[6];
						result += " y ";						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 8:
				switch (unidad){
					case 0:
						result += Expresion_Decenas[7];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas[7];
						result += " y ";
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas[7];
						result += " y ";
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas[7];
						result += " y ";
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas[7];
						result += " y ";
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas[7];
						result += " y ";
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas[7];
						result += " y ";						
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas[7];
						result += " y ";						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas[7];
						result += " y ";						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas[7];
						result += " y ";						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			case 9:
				switch (unidad){
					case 0:
						result += Expresion_Decenas[8];
						result += " ";
						break;
					case 1:
						result += Expresion_Decenas[8];
						result += " y ";
						result += Expresion_Unidades[0];
						result += " ";
						break;
					case 2:
						result += Expresion_Decenas[8];
						result += " y ";
						result += Expresion_Unidades[2];
						result += " ";
						break;
					case 3:
						result += Expresion_Decenas[8];
						result += " y ";
						result += Expresion_Unidades[3];
						result += " ";
						break;
					case 4:
						result += Expresion_Decenas[8];
						result += " y ";
						result += Expresion_Unidades[4];
						result += " ";
						break;
					case 5:
						result += Expresion_Decenas[8];
						result += " y ";
						result += Expresion_Unidades[5];
						result += " ";
						break;
					case 6:
						result += Expresion_Decenas[8];
						result += " y ";						
						result += Expresion_Unidades[6];
						result += " ";
						
						break;
					case 7:
						result += Expresion_Decenas[8];
						result += " y ";						
						result += Expresion_Unidades[7];
						result += " ";
						break;
					case 8:
						result += Expresion_Decenas[8];
						result += " y ";						
						result += Expresion_Unidades[8];
						result += " ";
						break;
					case 9:
						result += Expresion_Decenas[8];
						result += " y ";						
						result += Expresion_Unidades[9];
						result += " ";
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}

    cout<<result<<endl;
}

// 910 999 999   => novecientos millones novecientos noventa y nueve mil 