#include <iostream>
#include <vector>
using namespace std;

#define NRow 31  // filas
#define NCol 31  // columnas
#define startX 3 // inicio en x
#define startY 4 // inicio en y


void bronco_tour(vector<vector<int> >& tour,
                 vector<vector<bool> >& ref_visit,
                 unsigned int row, unsigned int col, unsigned int& move,
                 unsigned int start_inX, unsigned int start_inY )
{
    if(start_inX < 0 || start_inX >= row ||
       start_inY < 0 || start_inY >= col)
        return;

    if(ref_visit[start_inX][start_inY])
        return;

    ref_visit[start_inX][start_inY] = true;
    tour[start_inX][start_inY] = move++;

    // backtracking
    // marcamos luego back back back en caso de q no haya camino disponible backeamos hasta q haya un camino libre
    bronco_tour(tour, ref_visit, row, col, move, start_inX + 1, start_inY + 2);
    bronco_tour(tour, ref_visit, row, col, move, start_inX + 1, start_inY - 2);
    bronco_tour(tour, ref_visit, row, col, move, start_inX - 1, start_inY + 2);
    bronco_tour(tour, ref_visit, row, col, move, start_inX - 1, start_inY - 2);

    bronco_tour(tour, ref_visit, row, col, move, start_inX + 2, start_inY + 1);
    bronco_tour(tour, ref_visit, row, col, move, start_inX + 2, start_inY - 1);
    bronco_tour(tour, ref_visit, row, col, move, start_inX - 2, start_inY + 1);
    bronco_tour(tour, ref_visit, row, col, move, start_inX - 2, start_inY - 1);
}

void print_tour(vector< vector<int> > tour_checked){
    for (int i = 0; i < tour_checked.size(); ++i) {
        for (int j = 0; j < tour_checked[0].size(); ++j) {
//            cout << tour_checked[i][j] << "\t";
//              cuenta la leyenda q printf es 5 veces mas rapido que std::cout :x
            printf("%i\t",tour_checked[i][j]);
        }
        // cout << endl;
        printf("\n");
    }
}

int main(){
    unsigned int move = 1;

    vector<vector<int> > tour;
    tour.assign(NRow, vector<int>(NCol, 0));

    vector<vector<bool> > ref_visit;
    ref_visit.assign(NRow, vector<bool>(NCol, false));

    unsigned t0, t1;
    t0=clock();
    bronco_tour(tour, ref_visit, NRow, NCol, move,startX, startY);
    t1=clock();

    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "tiempo " << time << '\n';

    print_tour(tour);

    return 0;
}