#include <iostream>
#include "./core/db.hpp"
using namespace std;

// for testing
// #include "./libs/functions.hpp"

void faker30k(){
	str query_createTable = "CREATE TABLA Tb_estudiante_30000 INTEGER ID_est CHAR(30) nom CHAR(30) ape INTEGER edad ;";
													//INSERTAR EN Tb_estudiante_30000 VALORES 1 nombre1 ape1 1 ;
	
	UCSP::BD2::DataBase DBF;

	DBF.i_query(query_createTable);

	for (int i = 1; i <= 30000; ++i) {
		str pivot = "INSERTAR EN Tb_estudiante_30000 VALORES ";
		str pivot_edad = intToString(1 + rand() % 80);

		str pivot_iterator = intToString(i);
		pivot += pivot_iterator;
		pivot += " nombre" + pivot_iterator + " apellido" + pivot_iterator + " " + pivot_edad + " ;";
		DBF.i_query(pivot);
	}
	cout << "Datos generados para 30K registros \n";
}

<<<<<<< HEAD
void faker30ki(){
	str query_createTable = "CREATE TABLA Tb_estudiante_30000_idx INTEGER ID_est CHAR(30) nom CHAR(30) ape INTEGER edad ;";
=======
void faker80k(){
	str query_createTable = "CREATE TABLA Tb_estudiante_80000 INTEGER ID_est CHAR(30) nom CHAR(30) ape INTEGER edad ;";
>>>>>>> 1ee85d788502ab00eb43eff1e9dbac2f2a202106
													//INSERTAR EN Tb_estudiante_30000 VALORES 1 nombre1 ape1 1 ;
	
	UCSP::BD2::DataBase DBF;

	DBF.i_query(query_createTable);

<<<<<<< HEAD
	for (int i = 1; i <= 30000; ++i) {
		str pivot = "INSERTAR EN Tb_estudiante_30000_idx VALORES ";
=======
	for (int i = 1; i <= 80000; ++i) {
		str pivot = "INSERTAR EN Tb_estudiante_80000 VALORES ";
>>>>>>> 1ee85d788502ab00eb43eff1e9dbac2f2a202106
		str pivot_edad = intToString(1 + rand() % 80);

		str pivot_iterator = intToString(i);
		pivot += pivot_iterator;
		pivot += " nombre" + pivot_iterator + " apellido" + pivot_iterator + " " + pivot_edad + " ;";
		DBF.i_query(pivot);
	}
<<<<<<< HEAD
	cout << "Datos generados para 30K_idx registros \n";
}


void faker80k(){
    str query_createTable = "CREATE TABLA Tb_estudiante_80000 INTEGER ID_est CHAR(30) nom CHAR(30) ape INTEGER edad ;";
                                                    //INSERTAR EN Tb_estudiante_30000 VALORES 1 nombre1 ape1 1 ;

    UCSP::BD2::DataBase DBF;

    DBF.i_query(query_createTable);

    for (int i = 1; i <= 80000 ; ++i) {
        str pivot = "INSERTAR EN Tb_estudiante_80000 VALORES ";
        str pivot_edad = intToString(1 + rand() % 80);

        str pivot_iterator = intToString(i);
        pivot += pivot_iterator;
        pivot += " nombre" + pivot_iterator + " apellido" + pivot_iterator + " " + pivot_edad + " ;";
        DBF.i_query(pivot);
    }
    cout << "Datos generados para 80K registros \n";
}

void faker80ki(){
    str query_createTable = "CREATE TABLA Tb_estudiante_80000_idx INTEGER ID_est CHAR(30) nom CHAR(30) ape INTEGER edad ;";
                                                    //INSERTAR EN Tb_estudiante_30000 VALORES 1 nombre1 ape1 1 ;

    UCSP::BD2::DataBase DBF;

    DBF.i_query(query_createTable);

    for (int i = 1; i <= 80000 ; ++i) {
        str pivot = "INSERTAR EN Tb_estudiante_80000_idx VALORES ";
        str pivot_edad = intToString(1 + rand() % 80);

        str pivot_iterator = intToString(i);
        pivot += pivot_iterator;
        pivot += " nombre" + pivot_iterator + " apellido" + pivot_iterator + " " + pivot_edad + " ;";
        DBF.i_query(pivot);
    }
    cout << "Datos generados para 80K_idx registros \n";
}


int main(){

	faker30k();
	faker80k();
	faker30ki();
	faker80ki();

=======
	cout << "Datos generados para 80K registros \n";
}


int main() {
	faker80k();
>>>>>>> 1ee85d788502ab00eb43eff1e9dbac2f2a202106
	UCSP::BD2::DataBase DB;
	while (true){
		str query;
		getline(std::cin, query);
		DB.i_query(query);
	}

	
	return 0;
}
