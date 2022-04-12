#ifndef PLOTTER_INCLUDED
#define PLOTTER_H_INCLUDED
#include <iostream>
#include <iostream>

using namespace std;

class Plotter {
    public:
        Plotter();
        ~Plotter();
        void operator () ( const string & command ) ;
    protected:
        FILE *gnuplotFile;
};

    Plotter::Plotter() {
        gnuplotFile = popen("gnuplot -persist", "w");
        if(!gnuplotFile)
        cerr<<("Gnuplot no instalado we xD");
    }

    Plotter::~Plotter() {
        fprintf(gnuplotFile, "exit\n");
        pclose(gnuplotFile);
    }

    void Plotter::operator() ( const string & command ) {
        fprintf(gnuplotFile, "%s\n", command.c_str());
        fflush(gnuplotFile);
    }
#endif