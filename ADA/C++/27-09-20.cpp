#include <bits/stdc++.h>
#include "./Plotter/plotter.hpp"

using namespace std;

int main () {
    //Plotter p; // instanciamos el plotter como un objeto independiente para escribir los comandos propios de gnuplot
//    p("plot \'./a.dat\' u 1:2 w l "); // ejecutamos el operador () con el comando de gnuplot
    //p("plot sin(x**2)");

    float a = 3.5;
    int b = 5;
    double c = 58989898;
    cout << typeid(a).hash_code() << endl;

    return 0;
}