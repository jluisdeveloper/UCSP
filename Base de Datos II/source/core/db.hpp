#ifndef SOURCE_DB_HPP_
#define SOURCE_DB_HPP_
#include "table.hpp"
#include <ctype.h>

str create_tab = "CREATE TABLA ";
str insert_into = "INSERTAR EN "; //11
str insert_index = "INSERTAR CON INDICE EN ";
str select_q = "SELECT * FROM ";
str del = "DELETE FROM ";
str delete_index = "ELIMINAR CON INDICE EN ";
str upd = "UPDATE FROM ";
str upd_index = "UPDATE CON INDICE EN ";
str multi_insert = "INSERTAR VARIOS EN ";
str create_index = "CREATE INDEX ";
str a_ram = "A RAM (";

txt_file tables_txt;
read_file tables_txt2;
unsigned t0, t1;

bool index_query;
namespace UCSP{
  namespace BD2{
    class DataBase{
      private:
        table_vec tables;
        tree_vec indices;
        bool query_index, query_where, to_insert, index_eval, id_index;
        str_vec values_to_compare;	
        int comparator; //0: EQUAL, 1: GREATER, 2: EQUAL
        
        bool interpret_query(str query, str& name, strp_vec& vec, char_name_vec& cvec, uint_vec& num) {
          str temp, type, type_name, char_num;
          int i, int_count, char_count;
          int_count = char_count = 0;
          vec.clear();
          temp.clear();
          temp = query.substr(0, 13); //temp = "CREATE TABLE "
          if (temp != create_tab){
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
            return 0;
          }
          i = 13;
          name.clear();
          while (query[i] != ' '){
            name += query[i];
            i++;
          }
          i++; //so query[i] != ' '
          while (query[i] != ';' && query[i] != ' '){
            type.clear();
            type_name.clear();
            str_pair data_name_pair; //pair of str(type), str(name)
            char_name char_name_pair;
            while (query[i] != ' ' && query[i] != '('){ //filling with type
              type += query[i];
              i++;
            }
            i++;
            if (type == "INTEGER"){
              int_count++; //i++ because next is a space
              while (query[i] != ' ' && query[i] != ';'){ //filling with the name chosen
                type_name += query[i];
                i++;
              }
              data_name_pair.first = type;
              data_name_pair.second = type_name;
              vec.push_back(data_name_pair);
              i++;
            } else if (type == "CHAR") {
              char_count++;
              char_num.clear();
              while (query[i] != ')' && query[i] != ';'){ //filling with the amount of bytes chosen
                char_num += query[i];
                i++;
              }
              i++; //i is now ' ' 
              i++; //i is now the letter
              while (query[i] != ' ' && query[i] != ';'){
                type_name += query[i];
                i++;
              }
              
              data_name_pair.first = type;
              data_name_pair.second = type_name;
              
              char_name_pair.first = type_name;
              char_name_pair.second = stringToUint(char_num); //n chars
              
              vec.push_back(data_name_pair);
              cvec.push_back(char_name_pair);
              
              i++;
            } else {
              std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
              return 0;
            }
          }
          num.at(0) = (int_count);
          num.at(1) = (char_count);
          //num.at(2) = (date_count);
          return 1;
        };
        
        bool interpret_query_index(str query, str& name_index, str& name_table, str& name_col) {
          str temp, type, type_name, char_num;
          int i, int_count, char_count;
          int_count = char_count = 0;

          temp.clear();
          
          //CREATE INDEX indi2 ON persona (dpto);
          //CREATE INDEX indi1 ON persona (id);
          //optiene en nombre del index
          i = 13;
          name_index.clear();
          while (query[i] != ' '){
            name_index += query[i];
            i++;
          }
          i++; //so query[i] != ' '
          //end

          temp += query[i]; 
          temp += query[i+1];
          std::cout << " temp: " << temp << '\n';
          if(temp != "ON")
          {
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.1\n";
            return 0;
          }
          i += 3;

          name_table.clear();
          while (query[i] != ' '){
            name_table += query[i];
            i++;
          }
          i++; //so query[i] != ' '

          if (query[i] != '(')
          {
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.2\n";
            return 0;
          }
          i++;
          name_col.clear();
          while (query[i] != ')'){
            name_col += query[i];
            i++;
          }
          i++;
          if (query[i] != ';')
          {
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.3\n";
            return 0;
          }

          return 1;
        };
        
        bool interpret_query_aRam(str query, str& name_index) {  
          str temp, temp_name_table, temp_name_col;
          u_int i;	

          i = 7;
          name_index.clear();
          while (query[i] != ')'){
            name_index += query[i];
            i++;
          }
          
          
          if (query[i+1] != ';')
          {
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.3\n";
            return 0;
          }
          
          if (name_index[0] == 'i' && name_index[1] == 'd'){
            this->id_index = 1; //id tree
            std::cout << "index name: " << name_index << '\n';
          }

          return 1;
        };
        
        bool interpret_query_i(str query, str& name, str_vec& values) {
          str temp, temp2;
          int i;
          values.clear();
          temp = query.substr(0, 12); //temp = "INSERTAR EN "
          if (temp != insert_into){
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
            return 0;
          }
          i = 12;
          name.clear();
          while (query[i] != ' '){ //getting the name of the table
            name += query[i];
            i++;
          }
          i++; //so query[i] != ' '
          for (int j = 0; j < 8; j++){
            temp2 += query[i++];
          }
          if (temp2 != "VALORES "){
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
            return 0;
          }
          while (query[i] != ';' && query[i] != ' '){
            temp.clear();
            while (query[i] != ' ' && query[i] != ';'){ //filling with type
              temp += query[i];
              i++;
            }
            i++;
            values.push_back(temp);
          }
          return 1;
        };
        
        bool interpret_query_s(str query, str& name, str_vec& values, str& column) {
          str temp, temp2;
          int i;
          values.clear();
          temp = query.substr(0, 14); //temp = "SELECT * FROM "
          if (temp != select_q){
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
            return 0;
          }
          i = 14;
          name.clear();
          while (query[i] != ' '){ //getting the name of the table
            name += query[i];
            i++;
          }
          i++;


          if (query[i] == ';') return 1;
          //WHERE clause
          //WHERE clause should begin here
          temp.clear();
          for(int j = 0; j < 6; j++){
            temp += query[i++];
          }		   //IDX = 
          if (temp != "WHERE "){
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
            return 0;
          }
          this->query_where = 1; //WHERE SYNTAX ENABLED
          this->values_to_compare.clear(); //where the values to compare will be added
          char comp;
          column.clear();
          while (query[i] != ' '){
            column += query[i++]; //column name is being stored
          }
          i++; //i should now be the comparator
          comp = query[i++]; //comp is the comparator, and i is a space
          //this->comparator = findInArray(comp, comparisons, 3);
          this->comparator = 0;
          //if comp is not in comparisons std::cout << "Comparador no permitido.\n";
          i++;
          temp.clear(); //this should be inside another loop
          //Will be fixed when I have to do boolean operators
          while (query[i] != ' '){ //getting the value of the atribute
            temp += query[i];
            i++;
          }
          this->values_to_compare.push_back(temp);

          //index
          i++;
          if (query[i] == ';') 
          {
            this->query_index = 0;
            return 1;
          }
          this->query_index = 1;
          temp.clear();
          for(int j = 0; j < 6; j++){//"IDX = ""
            temp += query[i++];
          }
          if (temp != "IDX = "){
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
            return 0;
          }

          temp.clear(); //this should be inside another loop
          //Will be fixed when I have to do boolean operators
          while (query[i] != ' '){ //getting the value of the atribute
            temp += query[i];
            i++;
          }

          this->values_to_compare.push_back(temp);

          return 1;
        };
        
        bool interpret_query_d(str query, str& name, str_vec& values, str& column) {
          str temp, temp2;
          int i;
          values.clear();
          temp = query.substr(0, 12); //temp = "DELETE FROM "
          if (temp != del){
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
            return 0;
          }
          i = 12;
          name.clear();
          while (query[i] != ' '){ //getting the name of the table
            name += query[i];
            i++;
          }
          i++; //so query[i] != ' '
          //WHERE clause
          temp.clear();
          for(int j = 0; j < 6; j++){
            temp += query[i++];
          }
          if (temp != "WHERE "){
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
            return 0;
          }
          this->query_where = 1; //WHERE SYNTAX ENABLED
          this->values_to_compare.clear(); //where the values to compare will be added
          char comp;
          column.clear();
          while (query[i] != ' '){
            column += query[i++]; //column name is being stored
          }
          i++; //i should now be the comparator
          comp = query[i++]; //comp is the comparator, and i is a space
          this->comparator = 0;
          //if comp is not in comparisons std::cout << "Comparador no permitido.\n";
          i++;
          temp.clear(); //this should be inside another loop
          //Will be fixed when I have to do boolean operators
          while (query[i] != ' '){ //getting the value of the atribute
            temp += query[i];
            i++;
          }
          this->values_to_compare.push_back(temp);
          return 1;
        };
        
        bool interpret_query_u(str query, str& name, str_vec& values, str& column, str_vec& columns) {
          str temp, temp2;
          int i;
          values.clear();
          temp = query.substr(0, 12); //temp = "UPDATE FROM "
          if (temp != upd){
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
            return 0;
          }
          i = 12;
          name.clear();
          while (query[i] != ' '){ //getting the name of the table
            name += query[i];
            i++;
          }
          i++; //so query[i] != ' '
          for (int j = 0; j < 4; j++){
            temp2 += query[i++];
          }
          if (temp2 != "SET "){
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
            return 0;
          }
          while ( /*query[i] != 'W' && */query[i] != ' '){
            temp.clear();
            if (query[i] == 'W'){
              temp2.clear();
              for (int j = 0; j < 6; j++){
                temp2 += query[i+j];
              }
              if (temp2 == "WHERE ") break;
            }
            temp2.clear();
            while (query[i] != ' ' && query[i] != ';'){ //filling with type
              temp += query[i];
              i++;
            }
            i++;
            columns.push_back(temp);
            if (query[i] != '=') {
              std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
              return 0;
            }
            i++;
            i++; //i is not empty now
            temp2.clear();
            while (query[i] != ' '){ //value
              temp2 += query[i++];
            }
            values.push_back(temp2);
            i++; //space omitted
          }
          i += 6; //ommitting "WHERE "
          this->query_where = 1; //WHERE SYNTAX ENABLED
          this->values_to_compare.clear(); //where the values to compare will be added
          char comp;
          column.clear();
          while (query[i] != ' '){
            column += query[i++]; //column name is being stored
          }
          i++; //i should now be the comparator
          comp = query[i++]; //comp is the comparator, and i is a space
          //this->comparator = findInArray(comp, comparisons, 3);
          this->comparator = 0;
          //if comp is not in comparisons std::cout << "Comparador no permitido.\n";
          i++;
          temp.clear(); //this should be inside another loop
          //Will be fixed when I have to do boolean operators
          while (query[i] != ' '){ //getting the value of the atribute
            temp += query[i];
            i++;
          }
          this->values_to_compare.push_back(temp);
          return 1;
        };
        
        bool interpret_query_i_m(str query, str& name, str_vec& values) {
          str temp, temp2;
          int i;
          values.clear();
          temp = query.substr(0, 19); //temp = "INSERTAR EN "
          if (temp != multi_insert){
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
            return 0;
          }
          i = 19;
          name.clear();
          while (query[i] != ' '){ //getting the name of the table
            name += query[i];
            i++;
          }
          i++; //so query[i] != ' '
          /*for (int j = 0; j < 8; j++){
            temp2 += query[i++];
          }
          if (temp2 != "VALORES "){
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
            return 0;
          }*/
          while (query[i] != ';' && query[i] != ' '){
            temp.clear();
            while (query[i] != ' ' && query[i] != ';'){ //filling with I; Rnum1,num2 or C
              temp += query[i];
              i++;
            }
            i++;
            values.push_back(temp);
          }
          return 1;
        };
        
        bool interpret_query_i_index(str query, str& name, str_vec& values, str_vec& name_indices, int_vec& num_col, str& num_fila) {
          str temp, temp2, temp3, _num;
          int i;
          values.clear();
          temp = query.substr(0, 23); //temp = "INSERTAR CON INDICE EN "
          
          if (temp != insert_index){
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.1\n";
            return 0;
          }
          i = 23;
          name.clear();
          while (query[i] != ' '){ //getting the name of the table
            name += query[i];
            i++;
          }
          i++; //so query[i] != ' '
          for (int j = 0; j < 8; j++){
            temp2 += query[i++];
          }
          if (temp2 != "VALORES "){
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.2\n";
            return 0;
          }
          while (query[i] != 'I' && query[i] != ' '){
            temp.clear();
            while (query[i] != ' ' && query[i] != ';'){ //filling with type
              temp += query[i];
              i++;
            }
            i++;
            values.push_back(temp);
          }
          
          ///INSERTAR CON INDICE EN alumnos_maz_nah VALORES 1001 nombre1001 apellido1001 99 INDICE prueba_edad.idx(3) prueba_idx.idx(0) S1001 ;
          ///SELECT * FROM alumnos_maz_nah WHERE id = 1001 IDX = prueba_idx.idx ;	
          temp3 = "";
          for (int j = 0; j < 7; j++){
            temp3 += query[i++];
          }
          if (temp3 != "INDICE "){
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.3\n";
            return 0;
          }
          //"INSERTAR CON INDICE nombre VALUES val1 INDICE ind.idx(2) ind"
          while (query[i] != 'S' && query[i] != ' '){
            temp.clear();
            while (query[i] != ' ' && query[i] != ';'){ //filling with type
              if(query[i] == '(')
              {
                i++;
                _num.clear();
                while (query[i] != ')')
                {
                  _num += query[i];
                  i++;
                }
                num_col.push_back(stringToInt(_num));
                i++;
                break;
              }
              temp += query[i];
              i++;			
            }
            i++;
            name_indices.push_back(temp);
          }
          i++;
          num_fila.clear();
          while (query[i] != ' ' && query[i] != ';')
          {
            num_fila += query[i];
            i++;
          }	
          return 1;
        };
        
        bool interpret_query_d_index(str query, str& name, str_vec& values, str& column, str& name_index, str& num_col) {
          str temp, temp2,temp3;
          int i;
          values.clear();
          temp = query.substr(0, 23); //temp = "DELETE FROM "
          if (temp != delete_index){
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
            return 0;
          }
          i = 23;
          name.clear();
          while (query[i] != ' '){ //getting the name of the table
            name += query[i];
            i++;
          }
          i++; //so query[i] != ' '
          //WHERE clause
          temp.clear();
          for(int j = 0; j < 6; j++){
            temp += query[i++];
          }
          if (temp != "WHERE "){
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
            return 0;
          }
          this->query_where = 1; //WHERE SYNTAX ENABLED
          this->values_to_compare.clear(); //where the values to compare will be added
          char comp;
          column.clear();
          while (query[i] != ' '){
            column += query[i++]; //column name is being stored
          }
          i++; //i should now be the comparator
          comp = query[i++]; //comp is the comparator, and i is a space
          this->comparator = 0;
          //if comp is not in comparisons std::cout << "Comparador no permitido.\n";
          i++;
          temp.clear(); //this should be inside another loop
          //Will be fixed when I have to do boolean operators
          while (query[i] != ' '){ //getting the value of the atribute
            temp += query[i];
            i++;
          }
          num_col = temp;
          this->values_to_compare.push_back(temp);
          i++;
          //std::cout<<i<<std::endl;
          temp3 = "";
          for (int j = 0; j < 7; j++){
            temp3 += query[i++];
          }
          
          if (temp3 != "INDICE "){
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.3\n";
            return 0;
          }
          
          while (query[i] != ';'){ //getting the name of the table
            name_index += query[i];
            i++;
          }
          
          return 1;
        };
        
        bool interpret_query_u_index(str query, str& name, str_vec& values, str_vec& name_indices, str& column, str_vec& columns) {
          str temp, temp2, temp3, _num;
          int i;
          values.clear();              //UPDATE CON INDICE EN tabla SET atributo = valor WHERE atributo = valor INDICE index1-name.idx ;
          temp = query.substr(0, 21); //temp = "UPDATE CON INDICE EN "
          //UPDATE CON INDICE EN alumnos_maz_nah SET edad = 4 WHERE edad = 1 INDICE prueba_edad.idx ;
          if (temp != upd_index){
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.1\n";
            return 0;
          }
          i = 21;
          name.clear();
          while (query[i] != ' '){ //getting the name of the table
            name += query[i];
            i++;
          }
          i++; //so query[i] != ' '
          for (int j = 0; j < 4; j++){
            temp2 += query[i++];
          }
          if (temp2 != "SET "){
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.2\n";
            return 0;
          }
          while ( /*query[i] != 'W' && */query[i] != ' '){
            temp.clear();
            if (query[i] == 'W'){
              temp2.clear();
              for (int j = 0; j < 6; j++){
                temp2 += query[i+j];
              }
              if (temp2 == "WHERE ") break;
            }
            temp2.clear();
            while (query[i] != ' ' && query[i] != ';'){ //filling with type
              temp += query[i];
              i++;
            }
            i++;
            columns.push_back(temp);
            if (query[i] != '=') {
              std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
              return 0;
            }
            i++;
            i++; //i is not empty now
            temp2.clear();
            while (query[i] != ' '){ //value
              temp2 += query[i++];
            }
            values.push_back(temp2);
            i++; //space omitted
          }
          i += 6; //ommitting "WHERE "
          this->query_where = 1; //WHERE SYNTAX ENABLED
          this->values_to_compare.clear(); //where the values to compare will be added
          char comp;
          column.clear();
          while (query[i] != ' '){
            column += query[i++]; //column name is being stored
          }
          i++; //i should now be the comparator
          comp = query[i++]; //comp is the comparator, and i is a space
          //this->comparator = findInArray(comp, comparisons, 3);
          this->comparator = 0;
          //if comp is not in comparisons std::cout << "Comparador no permitido.\n";
          i++;
          temp.clear(); //this should be inside another loop
          //Will be fixed when I have to do boolean operators
          while (query[i] != ' '){ //getting the value of the atribute
            temp += query[i];
            i++;
          }
          this->values_to_compare.push_back(temp);
          i++;
          temp3 = "";
          for (int j = 0; j < 7; j++){
            temp3 += query[i++];
          }
          if (temp3 != "INDICE "){
            std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.3\n";
            return 0;
          }
          //"INSERTAR CON INDICE nombre VALUES val1 INDICE ind.idx(2) ind"
          temp.clear();
          while (query[i] != ' ' && query[i] != ';'){ //filling with type
            temp += query[i];
            i++;
          }
          name_indices.push_back(temp);
          return 1;
        };
        
        str_vec select_query(read_file& file, str_vec columns, str name, str column) {
          str temp, temp2, temp3, temp_name, vchar_value_found, vchar_val_to_compare;
          str_vec res;

          //A RAM (indi1.idx);
          //A RAM (indi2.idx);
          //SELECT * FROM persona WHERE id = 7933 ;
          //SELECT * FROM persona WHERE id = 7933 IDX = indi1.idx ;
          //SELECT * FROM persona WHERE dpto = 5 ;
          //SELECT * FROM persona WHERE dpto = 5 IDX = indi2.idx ;

          if (this->query_index) { 

            u_int pos_index = indices.size()+1;
            for (int i = 0; i < indices.size(); i++)
            {	
              if(indices[i]->m_name_index == values_to_compare[1]){			
                pos_index = i;
                break;
              }
            }

            if(pos_index == indices.size()+1) {
              std::cout << "No existe el indice" << std::endl;
              return res;
            }
            if(indices[pos_index]->m_name_table != name) {
              std::cout << "No coincide la tabla del indice" << std::endl;
              return res;
            }

            //indices[pos_index]->inOrder();
            index_query = 1;
            this->index_eval = 1;
            return indices[pos_index]->find(values_to_compare[0]);
          }

          uint_vec types (columns.size() );
          u_int type;
          int pos = -1, i; //so if there's not a WHERE clause, the IF will never begin
          LL value_found, val_to_compare;
          read_file getting_columns;
          bool broke = 0, last_col = 0;
          
          temp_name = name + ".tilinTable";
          char* file_name = new char[temp_name.size() + 1];
          for (i = 0; i < temp_name.size(); i++){
            file_name[i] = temp_name.at(i);
          }
          file_name[i] = '\0';
          
          getting_columns.open(file_name); //copy of file
          
          delete [] file_name;
          temp_name.clear();
          temp.clear();
          
          if (this->query_where){ //finding the atributes
            getline(getting_columns, temp2);
            for(i = 0; i < temp2.size(); i++){
              if (temp2.at(i) == ',') {
                if (temp == column ){
                  type = finding_atribute_type(temp, name, pos);//finding atribute type: 0->INTEGER, 1->CHAR(N), 2->DATE
                  broke = 1;
                  break;
                  //pos will store the number of column we have to check at the table
                } //else
                temp.clear();
              } else {
                temp += temp2.at(i);
              }
            }
            if (!broke){
              if (temp == column ){
                type = finding_atribute_type(temp, name, pos);//finding atribute type: 0->INTEGER, 1->CHAR(N), 2->DATE
              }
            }
          }
          bool first_line = true;
          while (! file.eof() ){
            temp2.clear();
            getline(file, temp2);
            temp.clear();
            int position = 0;
            temp_name.clear();
            last_col = 0;
            for(i = 0; i < temp2.size(); i++){
              if ( temp2.at(i) == ',' ) {
                temp3 = temp_name;
                //temp3.erase(std::remove_if(temp3.begin(), temp3.end(), isspace), temp3.end());
                temp3.erase(std::remove_if(temp3.begin(), temp3.end(), [](unsigned char x){return std::isspace(x);}), temp3.end());


                if (pos == position){
                  last_col = 1;
                  if (type == 0){ //do the cast to the type it is
                    value_found = stringToLL(temp3);
                    //value_found.erase(std::remove_if(value_found.begin(), value_found.end(), isspace), value_found.end())
                    val_to_compare = stringToLL(values_to_compare.at(0) );
                    this->query_where = 1;
                    if (this->comparator == 0){
                      if (value_found == val_to_compare) to_insert = 1;
                    }
                    else if (this->comparator == 1){
                      if (value_found > val_to_compare) to_insert = 1;
                    }
                    else {
                      if (value_found == val_to_compare){
                        to_insert = 1;
                      }
                    }
                  } else if (type == 1){
                    vchar_value_found = temp3;
                    //vchar_value_found.erase(std::remove_if(vchar_value_found.begin(), vchar_value_found.end(), isspace), vchar_value_found.end())
                    vchar_val_to_compare = values_to_compare.at(0);
                    if (this->comparator == 0){
                      if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
                    }
                    else if (this->comparator == 1){
                      if (vchar_value_found > vchar_val_to_compare) to_insert = 1;
                    }
                    else {
                      if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
                    }
                  } else {
                    ; //same as above but with date
                  }
                  
                  //do the respective comparison with this->comparator and the value
                  //THIS COMPARATOR: 0 <, 1 >, 2 =
                  //for now, the value is only this->values_to_compare.at(0)
                }
                position++;
                temp += ' ';
                temp3.clear();
                temp_name.clear();
              } else { //storing values
                temp += temp2.at(i);
                temp_name += temp2.at(i); 
              }
            }
            if (! last_col ){ //doing one last iteration
              temp3 = temp_name;
              //temp3.erase(std::remove_if(temp3.begin(), temp3.end(), isspace), temp3.end());
              temp3.erase(std::remove_if(temp3.begin(), temp3.end(), [](unsigned char x){return std::isspace(x);}), temp3.end());
              if (pos == position){
                last_col = 1;
                if (type == 0){ //do the cast to the type it is
                  value_found = stringToLL(temp3);
                  //value_found.erase(std::remove_if(value_found.begin(), value_found.end(), isspace), value_found.end())
                  val_to_compare = stringToLL(values_to_compare.at(0) );
                  this->query_where = 1;
                  if (this->comparator == 0){
                    if (value_found == val_to_compare) to_insert = 1;
                  }
                  else if (this->comparator == 1){
                    if (value_found > val_to_compare) to_insert = 1;
                  }
                  else {
                    if (value_found == val_to_compare){
                      to_insert = 1;
                    }
                  }
                } else if (type == 1){
                  vchar_value_found = temp3;
                  //vchar_value_found.erase(std::remove_if(vchar_value_found.begin(), vchar_value_found.end(), isspace), vchar_value_found.end())
                  vchar_val_to_compare = values_to_compare.at(0);
                  if (this->comparator == 0){
                    if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
                  }
                  else {
                    if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
                  }
                } 
              }
              
            }
            if (temp.empty() ){
              first_line = false;
              continue;
            }
            if (! this->query_where || first_line) res.push_back(temp);
            if (this->query_where && this->to_insert) res.push_back(temp);
            this->to_insert = 0;
            first_line = false;
          }
          return res;
        }; //each position at the vec returned is a row of data
        
        void select_query2(read_file& file, str_tree* m_tree, str column) {
          str temp_fila, temp;
          u_int pos_column, j, i;

          j = 0;
          pos_column = 0;
          temp.clear();
          getline(file, temp_fila);
          while(j < temp_fila.size())
          {
            if(temp_fila[j] != ',')
            {
              temp += temp_fila[j];
            }
            else if(temp != column)
            {
              pos_column++;
            }
            else
              break;
            j++;
          }
          int id_fila = 1;
          while (! file.eof() ){
            j = 0;
            i = 0;
            temp_fila.clear();
            temp.clear();
            getline(file, temp_fila);

            while(j <= temp_fila.size())
            {
              if(temp_fila[j] != ',' && j != temp_fila.size())
              {
                temp += temp_fila[j];
              }
              else if(i != pos_column)
              {
                temp.clear();
                i++;
              }
              else
              {
                //temp.erase(std::remove_if(temp.begin(), temp.end(), isspace), temp.end());
                temp.erase(std::remove_if(temp.begin(), temp.end(), [](unsigned char x){return std::isspace(x);}), temp.end());
                m_tree->insert(temp, intToString(id_fila));
                break;
              }
              j++;		
            }
            id_fila++;
          }
        };
        
        void read_index(read_file& file, str_tree* m_tree) {
          str temp_fila, temp_data, temp_f;
          u_int size_fila, j, i;
          j=1;

          while (! file.eof() ){
            getline(file, temp_fila);
            i = 0;
            size_fila = temp_fila.size();
            temp_data.clear();
            temp_f.clear();

            if(size_fila == 0)
              break;

            while(temp_fila[i] != ';')
            {
              temp_data += temp_fila[i];
              i++;
            }
            i++;

            temp_f.clear();
            while(i < size_fila)
            {
              if (temp_fila[i] != ';')
                temp_f += temp_fila[i];
              else
              {
                m_tree->insert(temp_data, temp_f);
                temp_f.clear();
              }
              i++;
            }
            m_tree->insert(temp_data, temp_f);
          }
        };
        
        void delete_query(read_file& file, txt_file& outfile, str_vec columns, str name, str column) {
          str temp, temp2, temp3, temp_name, vchar_value_found, vchar_val_to_compare;
          str_vec res;
          uint_vec types (columns.size() );
          u_int type;
          int pos = -1, i; //so if there's not a WHERE clause, the IF will never begin
          LL value_found, val_to_compare;
          read_file getting_columns;
          bool broke = 0, last_col = 0;
          
          temp_name = name + ".tilinTable";
          char* file_name = new char[temp_name.size() + 1];
          for (i = 0; i < temp_name.size(); i++){
            file_name[i] = temp_name.at(i);
          }
          file_name[i] = '\0';
          
          getting_columns.open(file_name); //copy of file
          
          delete [] file_name;
          temp_name.clear();
          temp.clear();
          
          //if (this->query_where){ //finding the atributes
          getline(getting_columns, temp2);
          for(i = 0; i < temp2.size(); i++){
            if (temp2.at(i) == ',') {
              //std::cout << "values_to_compare.at(0) is: " << this->values_to_compare.at(0) << std::endl;
              if (temp == column ){
                type = finding_atribute_type(temp, name, pos);//finding atribute type: 0->INTEGER, 1->CHAR(N), 2->DATE
                broke = 1;
                break;
                //pos will store the number of column we have to check at the table
              } //else
              temp.clear();
            } else {
              temp += temp2.at(i);
            }
          }
          if (!broke){
            if (temp == column ){
              type = finding_atribute_type(temp, name, pos);//finding atribute type: 0->INTEGER, 1->CHAR(N), 2->DATE
            }
          }
          //}
          bool first_line = true;
          while (! file.eof() ){
            temp2.clear();
            getline(file, temp2);
            temp.clear();
            int position = 0;
            temp_name.clear();
            last_col = 0;
            for(i = 0; i < temp2.size(); i++){
              if ( temp2.at(i) == ',' ) {
                temp3 = temp_name;
                //temp3.erase(std::remove_if(temp3.begin(), temp3.end(), isspace), temp3.end());
                temp3.erase(std::remove_if(temp3.begin(), temp3.end(), [](unsigned char x){return std::isspace(x);}), temp3.end());
                if (pos == position){
                  last_col = 1;
                  if (type == 0){ //do the cast to the type it is
                    value_found = stringToLL(temp3);
                    val_to_compare = stringToLL(values_to_compare.at(0) );
                    this->query_where = 1;
                    if (this->comparator == 0){
                      if (value_found == val_to_compare) to_insert = 1;
                    }
                    else if (this->comparator == 1){
                      if (value_found > val_to_compare) to_insert = 1;
                    }
                    else {
                      if (value_found == val_to_compare){
                        to_insert = 1;
                      }
                    }
                  } else if (type == 1){
                    vchar_value_found = temp3;
                    vchar_val_to_compare = values_to_compare.at(0);
                    if (this->comparator == 0){
                      if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
                    }
                    else if (this->comparator == 1){
                      if (vchar_value_found > vchar_val_to_compare) to_insert = 1;
                    }
                    else {
                      if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
                    }
                  } else {
                    ; //same as above but with date
                  }
                  
                  //do the respective comparison with this->comparator and the value
                  //THIS COMPARATOR: 0 <, 1 >, 2 =
                  //for now, the value is only this->values_to_compare.at(0)
                }
                position++;
                temp += ',';
                temp3.clear();
                temp_name.clear();
              } else {
                temp += temp2.at(i);
                temp_name += temp2.at(i);
              }
            }
            if (! last_col ){
              temp3 = temp_name;
              //temp3.erase(std::remove_if(temp3.begin(), temp3.end(), isspace), temp3.end());
              temp3.erase(std::remove_if(temp3.begin(), temp3.end(), [](unsigned char x){return std::isspace(x);}), temp3.end());
              if (pos == position){
                last_col = 1;
                if (type == 0){ //do the cast to the type it is
                  value_found = stringToLL(temp3);
                  val_to_compare = stringToLL(values_to_compare.at(0) );
                  this->query_where = 1;
                  if (this->comparator == 0){
                    if (value_found == val_to_compare) to_insert = 1;
                  }
                  else if (this->comparator == 1){
                    if (value_found > val_to_compare) to_insert = 1;
                  }
                  else {
                    if (value_found == val_to_compare){
                      to_insert = 1;
                    }
                  }
                } else if (type == 1){
                  vchar_value_found = temp3;
                  vchar_val_to_compare = values_to_compare.at(0);
                  if (this->comparator == 0){
                    if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
                  }
                  else if (this->comparator == 1){
                    if (vchar_value_found > vchar_val_to_compare) to_insert = 1;
                  }
                  else {
                    if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
                  }
                } else {
                  ; //same as above but with date
                }
              }
              
            }
            if (first_line)outfile << temp << std::endl;
            if ( ! this->to_insert && !first_line) outfile << temp << std::endl;
            else{
              if (!first_line){
                temp.clear();
                while (temp.size() <= 59){
                  temp += ' ';
                }
                temp += '\n';
                outfile << temp;
              }
            }
            this->to_insert = 0;
            first_line = false;
          }
        };
        
        void update_query(read_file& file, txt_file& outfile, str_vec columns, str_vec values, str name, str column) {
          str temp, temp2, temp3, temp_name, vchar_value_found, vchar_val_to_compare;
          str_vec res;
          uint_vec types (columns.size() ); //types: if boolean operators are used
          uint_vec positions (columns.size()); //positions: positions of the columns in the table
          u_int type, j;
          u_int it;
          int pos = -1, i; //so if there's not a WHERE clause, the IF will never begin
          LL value_found, val_to_compare;
          read_file getting_columns;
          bool broke = 0, last_col = 0;
          
          temp_name = name + ".tilinTable";
          char* file_name = new char[temp_name.size() + 1];
          for (i = 0; i < temp_name.size(); i++){
            file_name[i] = temp_name.at(i);
          }
          file_name[i] = '\0';
          
          getting_columns.open(file_name); //copy of file
          
          delete [] file_name;
          temp_name.clear();
          temp.clear();
          
          //if (this->query_where){ //finding the atributes
          getline(getting_columns, temp2);
          for(i = 0; i < temp2.size(); i++){
            if (temp2.at(i) == ',') {
              if (temp == column ){
                type = finding_atribute_type(temp, name, pos);//finding atribute type: 0->INTEGER, 1->CHAR(N)
                broke = 1;
                break;
                //pos will store the number of column we have to check at the table
              } //else
              if (broke) {
                break;
              }
              temp.clear();
            } else {
              temp += temp2.at(i);
            }
          }
          if (!broke){
            if (temp == column ){
              type = finding_atribute_type(temp, name, pos);//finding atribute type: 0->INTEGER, 1->CHAR(N), 2->DATE
            }
          }
          temp.clear();
          for (it = 0; it < columns.size(); it++){ //getting positions of columns to update
            broke = 0;
            int k = 0;
            for(j = 0; j < temp2.size(); j++){
              if (temp2.at(j) == ',') {
                if (temp == columns.at(it) ){
                  positions.at(it) = k; //keeping a relation: columns[it] position is in positions[it]
                  broke = 1;
                  break;
                  //pos will store the number of column we have to check at the table
                } //else
                temp.clear();
                k++;
              } else {
                temp += temp2.at(j);
              }
            }
            if (!broke){
              if (temp == columns.at(it) ){
                positions.at(it) = k;
              }
            }
          }
          bool first_line = true;
          while (! file.eof() ){
            temp2.clear();
            getline(file, temp2);
            temp.clear();
            int position = 0;
            temp_name.clear();
            last_col = 0;
            for(i = 0; i < temp2.size(); i++){ //getting the lines of data
              if ( temp2.at(i) == ',' ) {
                temp3 = temp_name;
                //temp3.erase(std::remove_if(temp3.begin(), temp3.end(), isspace), temp3.end());
                temp3.erase(std::remove_if(temp3.begin(), temp3.end(), [](unsigned char x){return std::isspace(x);}), temp3.end());
                if (pos == position){
                  last_col = 1;
                  if (type == 0){ //do the cast to the type it is
                    value_found = stringToLL(temp3);
                    val_to_compare = stringToLL(values_to_compare.at(0) );
                    this->query_where = 1;
                    if (this->comparator == 0){ //in this case: to_insert = to_update
                      if (value_found == val_to_compare) to_insert = 1;
                    }
                    else if (this->comparator == 1){
                      if (value_found > val_to_compare) to_insert = 1;
                    }
                    else {
                      if (value_found == val_to_compare){
                        to_insert = 1;
                      }
                    }
                  } else if (type == 1){
                    vchar_value_found = temp3;
                    vchar_val_to_compare = values_to_compare.at(0);
                    if (this->comparator == 0){
                      if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
                    }
                    else if (this->comparator == 1){
                      if (vchar_value_found > vchar_val_to_compare) to_insert = 1;
                    }
                    else {
                      if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
                    }
                  } else {
                    ; //same as above but with date
                  }
                  
                  //do the respective comparison with this->comparator and the value
                  //THIS COMPARATOR: 0 <, 1 >, 2 =
                  //for now, the value is only this->values_to_compare.at(0)
                }
                position++;
                temp += ',';
                temp3.clear();
                temp_name.clear();
              } else {
                temp += temp2.at(i);
                temp_name += temp2.at(i);
              }
            }
            if (! last_col ){ //lines to 579 to 620 (aprox)
              temp3 = temp_name;
              //temp3.erase(std::remove_if(temp3.begin(), temp3.end(), isspace), temp3.end());
              temp3.erase(std::remove_if(temp3.begin(), temp3.end(), [](unsigned char x){return std::isspace(x);}), temp3.end());
              if (pos == position){
                last_col = 1;
                if (type == 0){ //do the cast to the type it is
                  value_found = stringToLL(temp3);
                  val_to_compare = stringToLL(values_to_compare.at(0) );
                  this->query_where = 1;
                  if (this->comparator == 0){
                    if (value_found == val_to_compare) to_insert = 1;
                  }
                  else if (this->comparator == 1){
                    if (value_found > val_to_compare) to_insert = 1;
                  }
                  else {
                    if (value_found == val_to_compare){
                      to_insert = 1;
                    }
                  }
                } else if (type == 1){
                  vchar_value_found = temp3;
                  vchar_val_to_compare = values_to_compare.at(0);
                  if (this->comparator == 0){
                    if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
                  }
                  else if (this->comparator == 1){
                    if (vchar_value_found > vchar_val_to_compare) to_insert = 1;
                  }
                  else {
                    if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
                  }
                } else {
                  ; //same as above but with date
                }
              }
              
            }
            if (first_line)outfile << temp << std::endl;
            if ( this->to_insert && !first_line){
              temp = updateRow(temp, positions, values);
              outfile << temp << std::endl;
            } else if (!first_line) outfile << temp << std::endl;
            
            this->to_insert = 0;
            first_line = false;
          }
        };
        
        u_int finding_atribute_type(str type_name, str table_name, int& pos) {
          //pos will store the number of the column at the file 
          //say we're looking for the "ABCD" column, and data is stored like "AHD,ACB,ABCD,AHD"
          //pos will save the value 2
          read_file tables_file;
          tables_file.open("tables.tilin");
          str temp, temp2;
          while(! tables_file.eof() ){
            getline(tables_file, temp);
            if (temp == table_name) break; //we've found the table we want to look at
          }
          pos = 0;
          while(! tables_file.eof() ){
            temp2.clear();
            int i = 0;
            getline(tables_file, temp);
            if (temp[0] == '-') return -1;
            //for(i = 0; i < type_name.size(); i++){
            while(temp[i] != ' '){
              temp2 += temp[i++];
            }
            if (temp2 == type_name){
              i++; //temp[i] should be the letter of the type
              if (temp[i] == 'I') return 0; //it is an integer!
              else if (temp[i] == 'C') return 1; //it is a CHAR!
            }
            pos++;
          }
        };
          
      public:
        DataBase(){ ; };

        void i_query(str query) { //main interpret query
          str temp;
          temp = query.substr(0, 13); //temp = "CREATE TABLE "
          if (temp == create_tab){
            createTable(query);
            return;
          }
          temp = query.substr(0, 13); //temp = "CREATE INDEX "
          if (temp == create_index){
            createIndex(query); 
            return;
          }
          temp = query.substr(0, 7); //temp = "A RAM ("
          if (temp == a_ram){
            aRam(query); 
            return;
          }
          temp = query.substr(0, 12); //temp = "INSERTAR EN "
          if (temp == insert_into){
            insert_row(query);
            return;
          }
          temp = query.substr(0, 23); //temp = insert_index = "INSERTAR CON INDICE EN nombre_tabla VALORES ;"
          if (temp == insert_index){
            insert_row_index(query);
            return;
          }
          temp = query.substr(0, 23); //temp = insert_index = "ELIMINAR CON INDICE EN nombre_tabla VALORES ;"
          if (temp == delete_index){
            delete_data_index(query);
            return;
          }
          temp = query.substr(0, 21); //"UPDATE CON INDICE EN "
          if (temp == upd_index){
            update_data_index(query);
            return;
          }
          temp = query.substr(0, 14); //temp = "SELECT * FROM "
          if (temp == select_q) {
            t0=clock();
            
            select_data(query);
            
            t1 = clock();
            double time = (double(t1-t0)/CLOCKS_PER_SEC);
            std::cout << "Execution Time: " << time << std::endl;

            return;
          }
          temp = query.substr(0, 12); //temp = "DELETE FROM "
          if (temp == del){
            delete_data(query);
            return;
          }
          temp = query.substr(0, 12); //temp = "DELETE FROM "
          if (temp == upd){
            update_data(query);
            return;
          }
          temp = query.substr(0, 19); //temp = "INSERTAR VARIOS EN "
          if (temp == multi_insert){
            insert_multiple(query);
            return;
          }
          std::cout << "Sintaxis incorrecta. Vuelva a intentarlo\n";
          return;
        }; 

        void createTable(str query) {
          str name;
          strp_vec vec;
          char_name_vec cvec;
          uint_vec num (2);
          int i;
          
          if (!interpret_query(query, name, vec, cvec, num)) return;
          Table* temp = new Table(name, vec, num, cvec);
          //add_table(temp); 
          
          tables_txt.open("tables.tilin", std::fstream::app); //adding to the file in hdd
          writeTable(tables_txt, temp);
          tables_txt.close();
          
          name += ".tilinTable";
          char* file_name = new char[name.size() + 1];
          for (i = 0; i < name.size(); i++){
            file_name[i] = name.at(i);
          }
          file_name[i] = '\0';

          tables_txt.open(file_name);
          writeHeaderTable(tables_txt, temp);
          tables_txt.close();
          
          delete [] file_name;
          
          std::cout << "Tabla " << temp->getName() << " creada.\n";
          temp->desc();
        };
        
        void createIndex(str query) {
          str name_index, name_table, name_col, tex, temp_name_table;
          str_vec vec_data, vec_filas, vec_col;
          int i;
          
          if (!interpret_query_index(query, name_index, name_table, name_col)) return;
          
          name_index += ".idx";
          char* file_name = new char[name_index.size() + 1];
          for (i = 0; i < name_index.size(); i++){
            file_name[i] = name_index.at(i);
          }
          file_name[i] = '\0';

          temp_name_table = name_table;
          name_table += ".tilinTable";

          char* file_tabe = new char[name_table.size() + 1];
          for (i = 0; i < name_table.size(); i++){
            file_tabe[i] = name_table.at(i);
          }
          file_tabe[i] = '\0';

          str_tree *m_tree =  new str_tree(name_index, name_col, temp_name_table);
          
          tables_txt2.open(file_tabe, std::fstream::app);
          this->select_query2(tables_txt2, m_tree, name_col);
          tables_txt2.close();
          

          tables_txt.open(file_name, std::fstream::app);	
          m_tree->writeFile(tables_txt);
          tables_txt.close();
          
          delete [] file_name;
          
          indices.push_back(m_tree);

          std::cout << "Se creo el INDEX\n";
        };
        
        void insert_row(str query) {
          str name;
          str_vec vec;
          int i;
          
          if (!interpret_query_i(query, name, vec)) return;
          name += ".tilinTable";
          char* file_name = new char[name.size() + 1];
          for (i = 0; i < name.size(); i++){
            file_name[i] = name.at(i);
          }
          
          file_name[i] = '\0';
          tables_txt.open(file_name, std::fstream::app);
          //write the info retrieved to file_name
          writeInsert(tables_txt, vec);
          tables_txt.close();
          
          delete [] file_name;
          //std::cout << "Datos insertados.\n";
        };
        
        void insert_row_index(str query) {
          ///INSERTAR CON INDICES EN nombre_tabla VALUES value_1 caluer2 INDICES name.idx(2) nameidx(1)
          str name;
          str_vec vec;
          str_vec name_index;
          int_vec num_col;
          str num_fila;
          int i;
          
          if (!interpret_query_i_index(query, name, vec, name_index, num_col, num_fila)) return;
          name += ".tilinTable";
          char* file_name = new char[name.size() + 1];
          for (i = 0; i < name.size(); i++){
            file_name[i] = name.at(i);
          }
          
          file_name[i] = '\0';
          tables_txt.open(file_name, std::fstream::app);
          //write the info retrieved to file_name
          writeInsert(tables_txt, vec);
          tables_txt.close();
          
          delete [] file_name;
          
          for (int i = 0; i < indices.size(); i++) 
          {	
            for(int j = 0; j < name_index.size(); j++)
            {
              if(indices[i]->m_name_index == name_index[j])			
              {
                indices[i]->insert(vec[num_col[j]], num_fila);
              }					
            }	
          }
          
          //std::cout << "Datos insertados.\n";
        };
        
        void select_data(str query) {
          str name, result, column, temp_name;
          str_vec vec;
          char* index_q;
          int i;
          result.clear();

          if (!interpret_query_s(query, name, vec, column)) return;

          temp_name = name;
          name += ".tilinTable";
          char* file_name = new char[name.size() + 1];
          for (i = 0; i < name.size(); i++){
            file_name[i] = name.at(i);
          }
          file_name[i] = '\0';
          tables_txt2.open(file_name, std::fstream::app);
          //get the info from the select clause
          vec = this->select_query(tables_txt2, vec, temp_name, column);
          //tables_txt2.close();

          delete [] file_name;
          
          //if (index_query){
          if (this->index_eval){
            char* first_row = new char[24];
            tables_txt2.seekg(0);
            tables_txt2.read(first_row, 24);
            std::cout.write(first_row, 24);
            delete[] first_row;
            if (vec.size() == 1 && vec.at(0) == "-1"){
              std::cout << "No se encontro el valor buscado.\n";
            } else {
              for (int i = 0; i < vec.size(); i++){
                index_q = new char[61];
                //std::cout << "iter: " << i << std::endl;
                //std::cout << "column: " << vec.at(i) << std::endl;
                //std::cout << "seekg: " << 24 + i + 60 * (stringToInt(vec.at(i))-1) << std::endl;
                tables_txt2.seekg(24 + (61 * (stringToInt(vec.at(i))-1)), std::ios_base::beg);
                tables_txt2.read(index_q, 61);
                //std::cout << index_q << '\n';
                std::cout.write(index_q,61);
                delete[] index_q;
              }
            }
            index_query = 0;
          } else {
            for (int i = 0; i < vec.size(); i++){
              std::cout << vec.at(i) << '\n';
            }
          }
          this->query_where = 0;
          index_query = 0;
          this->index_eval = 0;
          tables_txt2.close();
        };
        
        void delete_data(str query) {
          str name, result, column, temp_name;
          str_vec vec;
          txt_file outfile;
          int i;
          result.clear();
          
          if (!interpret_query_d(query, name, vec, column)) return;
          temp_name = name;
          temp_name = temp_name + "_temp.tilinTable"; //to create name_temp.tilinTable
          
          char* file_temp = new char[temp_name.size() + 1]; //data will be temporarily stored there
          char* file_name = new char[name.size() + 1];
          for (i = 0; i < temp_name.size(); i++){
            file_temp[i] = temp_name.at(i);
          }
          file_temp[i] = '\0';
          outfile.open(file_temp);
          
          temp_name = name;
          
          name += ".tilinTable";
          for (i = 0; i < name.size(); i++){
            file_name[i] = name.at(i);
          }
          file_name[i] = '\0';
          tables_txt2.open(file_name, std::fstream::app);
          //copy to a temp file all values but deleted one
          this->delete_query(tables_txt2, outfile, vec, temp_name, column); //PRETTY MUCH the same as select_query
          tables_txt2.close();
          outfile.close();
          
          remove(file_name); //removing old data
          std::rename(file_temp, file_name); //renaming so name.tilinTable still exists with the new data
          //std::rename(file_name, file_temp); //renaming so name.tilinTable still exists with the new data
          
          delete [] file_name;
          delete [] file_temp;
          
          std::cout << "Valores eliminados.\n";
          
          this->query_where = 0;
        };
        
        void delete_data_index(str query) {
          str name, result, column, temp_name, name_index, num_col;
          str_vec vec;
          txt_file outfile;
          int i;
          result.clear();
          
          if (!interpret_query_d_index(query, name, vec, column, name_index, num_col)) return;
          
          /*std::cout<<"NAME: "<<name<<std::endl;
          std::cout<<"column: "<<column<<std::endl;
          std::cout<<"NAME_INDEX: "<<name_index<<std::endl;
          std::cout<<"NUM COL: "<<num_col<<std::endl;
          */
          
          temp_name = name;
          temp_name = temp_name + "_temp.tilinTable"; //to create name_temp.tilinTable
          
          char* file_temp = new char[temp_name.size() + 1]; //data will be temporarily stored there
          char* file_name = new char[name.size() + 1];
          for (i = 0; i < temp_name.size(); i++){
            file_temp[i] = temp_name.at(i);
          }
          file_temp[i] = '\0';
          outfile.open(file_temp);
          
          temp_name = name;
          
          name += ".tilinTable";
          for (i = 0; i < name.size(); i++){
            file_name[i] = name.at(i);
          }
          file_name[i] = '\0';
          tables_txt2.open(file_name, std::fstream::app);
          //copy to a temp file all values but deleted one
          this->delete_query(tables_txt2, outfile, vec, temp_name, column); //PRETTY MUCH the same as select_query
          tables_txt2.close();
          outfile.close();
          
          remove(file_name); //removing old data
          std::rename(file_temp, file_name); //renaming so name.tilinTable still exists with the new data
          //std::rename(file_name, file_temp); //renaming so name.tilinTable still exists with the new data
          
          delete [] file_name;
          delete [] file_temp;
          
          
          
          int numcol = stringToInt(num_col);
          std::cout<<numcol<<std::endl;
          
          for (int i = 0; i < indices.size(); i++) {	
            std::cout<<indices[i]->m_name_index<<std::endl;
            
            if(indices[i]->m_name_index == values_to_compare[0]){// && vec[numcol] == num_col){	
              indices[i]->deleteKey(vec[numcol]);
            }	
          }
          
          std::cout << "Valores eliminados.\n";
          
          this->query_where = 0;
        };
        
        void update_data(str query) {
          str name, result, column, temp_name;
          str_vec columns, values;
          txt_file outfile;
          int i;
          result.clear();
          
          if (!interpret_query_u(query, name, values, column, columns)) return;
          temp_name = name;
          temp_name = temp_name + "_temp.tilinTable"; //to create name_temp.tilinTable
          
          char* file_temp = new char[temp_name.size() + 1]; //data will be temporarily stored there
          char* file_name = new char[name.size() + 1];
          for (i = 0; i < temp_name.size(); i++){
            file_temp[i] = temp_name.at(i);
          }
          file_temp[i] = '\0';
          outfile.open(file_temp);
          
          temp_name = name;
          
          name += ".tilinTable";
          for (i = 0; i < name.size(); i++){
            file_name[i] = name.at(i);
          }
          file_name[i] = '\0';
          tables_txt2.open(file_name, std::fstream::app);
          this->update_query(tables_txt2, outfile, columns, values, temp_name, column); //PRETTY MUCH the same as delete_query
          tables_txt2.close();
          outfile.close();
          
          remove(file_name); //removing old data
          std::rename(file_temp, file_name); //renaming so name.tilinTable still exists with the new data
          
          delete [] file_name;
          delete [] file_temp;
          
          std::cout << "Valores actualizados.\n";
          
          this->query_where = 0;
        };
        
        void update_data_index(str query) {
          str name, result, column, temp_name;
          str_vec columns, values, name_indices;
          txt_file outfile;
          std::vector< std::string > temp;
          int i;
          result.clear();
          
          if (!interpret_query_u_index(query, name, values, name_indices, column, columns)) return;
          temp_name = name;
          temp_name = temp_name + "_temp.tilinTable"; //to create name_temp.tilinTable
          
          char* file_temp = new char[temp_name.size() + 1]; //data will be temporarily stored there
          char* file_name = new char[name.size() + 1];
          for (i = 0; i < temp_name.size(); i++){
            file_temp[i] = temp_name.at(i);
          }
          file_temp[i] = '\0';
          outfile.open(file_temp);
          
          temp_name = name;
          
          name += ".tilinTable";
          for (i = 0; i < name.size(); i++){
            file_name[i] = name.at(i);
          }
          file_name[i] = '\0';
          tables_txt2.open(file_name, std::fstream::app);
          this->update_query(tables_txt2, outfile, columns, values, temp_name, column); //PRETTY MUCH the same as delete_query
          tables_txt2.close();
          outfile.close();
          
          remove(file_name); //removing old data
          std::rename(file_temp, file_name); //renaming so name.tilinTable still exists with the new data
          
          delete [] file_name;
          delete [] file_temp;
          
          std::cout << "Valores actualizados.\n";
          
          this->query_where = 0;
          
          for (int i = 0; i < indices.size(); i++)
          {
            if(indices[i]->m_name_index == name_indices[0])
            {
              temp=indices[i]->find(values_to_compare.at(0));
              indices[i]->deleteKey(values_to_compare.at(0));
              for(int o=0; o < temp.size(); o++){
                std::cout<<temp[o]<<std::endl;
                indices[i]->insert(values[0], temp[o]);
              }
            }
            
          }
        };
        
        void insert_multiple(str query) {  //INSERTAR VARIOS EN tabla I/Rnum1,num2/C ;
          str name;
          str_vec vec;
          int i;
          
          if (!interpret_query_i_m(query, name, vec)) return;
          std::cout << "Insertando varias filas en " << name << std::endl;
          name += ".tilinTable";
          char* file_name = new char[name.size() + 1];
          for (i = 0; i < name.size(); i++){
            file_name[i] = name.at(i);
          }
          
          file_name[i] = '\0';
          tables_txt.open(file_name, std::fstream::app);
          tables_txt2.open(file_name);
          //write the info retrieved to file_name
          //writeInsert(tables_txt, vec);
          write_multiple(tables_txt, tables_txt2, vec);
          tables_txt.close();
          
          delete [] file_name;
          //std::cout << "Datos insertados.\n";
        };
        
        void aRam(str query) {
          str name_index, temp, temp_name_table, temp_name_col;
          u_int i;
          
          if (!interpret_query_aRam(query, name_index)) return;

          for (int i = 0; i < indices.size(); i++)
          {	
            if(indices[i]->m_name_index == name_index)			
              return ;		
          }

          temp.clear();
          char* file_name = new char[name_index.size() + 1];
          for (i = 0; i < name_index.size(); i++){
            file_name[i] = name_index.at(i);
          }
          file_name[i] = '\0';
          
          tables_txt2.open(file_name, std::fstream::app);

          i=0;
          getline(tables_txt2, temp);
          

          temp_name_table.clear();
          while (temp[i] != ','){
            temp_name_table += temp[i];
            i++;
          }

          i++;
          temp_name_col.clear();
          while (i < temp.size()){
            temp_name_col += temp[i];
            i++;
          }

          str_tree *m_tree =  new str_tree(name_index, temp_name_col, temp_name_table);
          std::cout << "init read" << std::endl;
          if (this->id_index){
            //std::cout << "id index\n";
            str_vec values;
            values.clear();
            values = this->id_values(file_name);
            std::cout << "id index. values read. starting to build tree\n";
            values.erase(values.begin() + values.size()-1);
            std::cout << "amount of values: " << values.size() << std::endl;
            std::cout << "first value: " << values.at(0) << ", last: " << values.at(values.size()-1) << std::endl;
            m_tree->build_from_vec(values, m_tree->root);
            //m_tree->build_from_vec2(values,0,values.size()-1);
            //std::cout << "root value: " << m_tree->root->key << std::endl;
          }
          else this->read_index(tables_txt2, m_tree);
          std::cout << "end read" << std::endl;
          tables_txt2.close();
          //m_tree->printPreorder(m_tree->root);
          indices.push_back(m_tree);
          //m_tree->inOrder();
          this->id_index = 0;
        };
        
        str_vec id_values(char* name) {
          str_vec values;
          str value, real_value;
          int i;
          read_file index_file;
          
          index_file.open(name);
          getline(index_file, value);
          while (! index_file.eof() ){
            //std::cout << "pushing value\n";
            i = 0;
            real_value.clear();
            getline(index_file, value);
            //std::cout << "line read: " << value << std::endl;
            while (value[i] != ';'){
              real_value += value[i];
              i++;
            }
            values.push_back(real_value);
            //std::cout << real_value << "pushed\n";
          }
          index_file.close();
          return values;
        };
      };
  }
}
#endif
