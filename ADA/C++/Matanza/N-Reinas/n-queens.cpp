#include <iostream>
#include <setjmp.h>

jmp_buf env;
int x,y;

using namespace std;

// tamaño del tablero
#define N 31

// Se amenazan o no
bool noSeAmenazan(char tab[][N], int r, int c)
{
    // si comparten la misma columna
    for (int i = 0; i < N; i++)
        if (tab[i][c] == 'R')
            return false;

    // si comparten la misma fila
    for (int i = 0; i < N; i++)
        if (tab[r][i] == 'R')
            return false;

    // revisamos diagonales
    for(int p=0; p < N; p++){
        for(int q=0; q < N; q++){
            if((tab[p][q] == 'R' ) && ((p+q == r+c) || (p-q == r-c))){
                return false;
            }
        }
    }
    return true;
}

void nReinas(char tab[][N], int r)
{
    // si tiene solucion la imprimimos
    if (r == N && (tab[x][y]=='R'))
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                cout << tab[i][j] << " ";
            cout << endl;
        }
        cout << endl;
        longjmp(env, 1);
    }

    // probamos con la reina en cada fila r
    // y la recorremos si es valida
    for (int c = 0; c < N; c++)
    {
        // si no se amenazan
        //cout << "R: " << r << " " <<"C: " << c << endl;
        if (noSeAmenazan(tab, r, c) || (x==r && y==c))
        {
            // le damos la posicion a la reina
            tab[r][c] = 'R';
            // siguiente fila
            nReinas(tab, r + 1);
            // backtracking, y sacamos a la ultima reina
            if (x!=r && y!=c)
            {
                tab[r][c] = '-';
            }
        }
    }
}

int main()
{
    unsigned t0, t1;
    char tab[N][N];

    cout << "Ingrese la pos. inicial (fila): ";
    cin >> x;
    cout << "Ingrese la pos. inicial (columna): ";
    cin >> y;

    cout << "x: " << x << " " << "y: " << y << endl;

    // tablero vacio
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            tab[i][j] = '-';
        }

    }

    // posicionamos la primera reina
    tab[x][y] = 'R';

    cout << "Inicio: " << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << tab[i][j] << " ";
        cout << endl;
    }
    cout << endl;

    t0=clock();
    if(!setjmp(env)) nReinas(tab, 0);
    t1=clock();

    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "tiempo: " << time << '\n';

    //impresion de la solucion


    return 0;
}