//Reynas 17*17 1-2  //  caballo  23*23 1-1

#include <iostream>
#include <vector>
using namespace std;

#define row 41
#define col 41

class Bronco {
    public:
        Bronco();
        Bronco(unsigned int _rows, unsigned int _cols);
        void bronco_tour(unsigned int row_refx, unsigned int col_refx);
        void print_BroncoTour();
        unsigned int rows;
        unsigned int cols;
        unsigned int move;
        vector<vector<int> > tour;
        vector<vector<bool> > visited;
};

Bronco::Bronco() {
    this->rows = 8;
    this->cols = 8;
    this->move = 1;
    this->tour.assign(this->rows, vector<int>(this->cols, 0));
    this->visited.assign(this->rows, vector<bool>(this->cols, false));
}

Bronco::Bronco(unsigned int _rows, unsigned int _cols) {
    this->rows = _rows;
    this->cols = _cols;
    this->move = 1;
    this->tour.assign(_rows, vector<int>(_cols, 0));
    this->visited.assign(_rows, vector<bool>(_cols, false));
}

void Bronco::print_BroncoTour() {
    for (int i = 0; i < this->tour.size(); ++i) {
        for (int j = 0; j < this->tour.size(); ++j) {
            cout << this->tour[i][j] << "\t";
        }
        cout << endl;
    }
}

void Bronco::bronco_tour(unsigned int row_refx, unsigned int col_refx) {
    if(row_refx < 0 || row_refx >= this->rows ||
       col_refx < 0 || col_refx >= this->cols)
        return;

    if(this->visited[row_refx][col_refx])
        return;

    // marcamos la matriz de visitas y las enumeramos
    this->visited[row_refx][col_refx] = true;
    this->tour[row_refx][col_refx] = this->move++;

    // nos vamos a los laterales para asegurar que se pueda resolver

    //backtracking
    bronco_tour(row_refx + 2, col_refx + 1);
    bronco_tour(row_refx + 2, col_refx - 1);
    bronco_tour(row_refx - 2, col_refx + 1);
    bronco_tour(row_refx - 2, col_refx - 1);

    bronco_tour(row_refx + 1, col_refx + 2);
    bronco_tour(row_refx + 1, col_refx - 2);
    bronco_tour(row_refx - 1, col_refx + 2);
    bronco_tour(row_refx - 1, col_refx - 2);

}

int main() {
    Bronco caballito(row,col);


    unsigned t0, t1;
    t0=clock();
    caballito.bronco_tour(3,4);
    t1=clock();

    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "tiempo " << time << '\n';


    caballito.print_BroncoTour();
}

// G7  AEAAAAAA no mas dire :v