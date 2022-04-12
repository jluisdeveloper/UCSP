#ifndef SOURCE_TABLE_HPP_
#define SOURCE_TABLE_HPP_

#include "../libs/structs.hpp"

class Table{
  private:
    str name;
    Data* t_data;
  public:
    Table(str name, strp_vec& vec, uint_vec nums, char_name_vec& cvec){
      this->name = name;
      Data *temp = new Data(nums.at(0), nums.at(1), vec, cvec);
      this->t_data = temp;
    };

    str getName(){
      return this->name;
    };

    void desc(){
      int camps;
      camps = this->t_data->n + this->t_data->v;
      std::cout << "Tabla: " << this->name << '\n';
      std::cout << "Hay " << camps << " atributos.\n"; 
      print_vec(this->t_data->names, this->t_data->vchars);
    };

    friend void writeTable(txt_file& file, Table* t){
      int j = 0;
      file << t->name << '\n';
      for(int i = 0; i < t->t_data->names.size(); i++){
        file << t->t_data->names.at(i).second << ' '; //STORED: DATA_NAME DATA_TYPE ENDL 
        if (t->t_data->names.at(i).first == "CHAR" ){
          file << "CHAR(" << t->t_data->vchars.at(j).second << ")" << '\n';
          j++;
        } else file << t->t_data->names.at(i).first << '\n'; //TIPO DE DATO
      }
      file << "-----------------------------------------"; //SEPARATION BETWEEN TABLES 
      file << '\n' << std::endl;  //so the next one starts at the next line
    };

    friend void writeHeaderTable(txt_file& file, Table* t){
      int j = 0;
      str alg;
      alg.clear();
      for(int i = 0; i < t->t_data->names.size(); i++){
        //alg += (t->t_data->names.at(i).second + ',');
        if (i != t->t_data->names.size()-1){
          //file << t->t_data->names.at(i).second << ','; //STORED: DATA_NAME,DATA_NAME,... ENDL 
          alg += (t->t_data->names.at(i).second + ',');
        }
        else {
          //file << t->t_data->names.at(i).second;
          alg += t->t_data->names.at(i).second;
        }
      }
      //while (alg.size() <= 59) alg += ' ';
      alg += '\n'; //SEPARATION FOR THE DATA TO BE STORED
      file << alg;
    };
};

#endif