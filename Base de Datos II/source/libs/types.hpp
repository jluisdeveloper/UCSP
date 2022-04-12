#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <utility>
#include <fstream>
#include <cstdio>
#include <ctime>
#include "../core/tree.hpp"

//defines mainly used for comparators
#define SMALLER <
#define EQUAL ==
#define GREATER >


//foward declaration of future implementations
class Table;
struct VCHAR;

//types
typedef std::string str;
typedef long long LL;
typedef unsigned int u_int;
typedef unsigned short u_short;
typedef std::pair <str, str> str_pair; //pair: type, name
typedef std::pair <str, u_int> char_name; //pair: name_of_CHAR, bytes
typedef std::vector<str_pair> strp_vec;
typedef std::vector<char_name> char_name_vec;
typedef std::vector<Table*> table_vec;
typedef std::vector<u_int> uint_vec;
typedef std::vector<VCHAR*> vchar_vec;
typedef std::vector<str> str_vec;
typedef std::vector<int> int_vec;
typedef std::stringstream ss;
typedef std::ofstream txt_file;
typedef std::ifstream read_file;
typedef AVLtree<std::string> str_tree;
typedef std::vector<str_tree*> tree_vec;