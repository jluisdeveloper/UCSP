#include <bits/stdc++.h>
using namespace std;

#define N 50
#define M 30

bool solveMazeUtil(int maze[N][M], int x,int y, int sol[N][M], int final_x, int final_y);

void printSolution(int sol[N][M]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            printf(" %d ", sol[i][j]);
        printf("\n");
    }
}

bool isSafe(int maze[N][M], int x, int y, int sol[N][M])
{
    if (x >= 0 && x < N && y >= 0 && y < M ) {
        if (maze[x][y] == 1 && sol[x][y] == 0) {
            return true;
        }
    }
    return false;
}

bool solveMaze(int maze[N][M], int inicio_x, int inicio_y, int final_x, int final_y)
{
    int sol[N][M];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            sol[i][j]=0;
        }
    }
    if (solveMazeUtil(maze, inicio_x, inicio_y, sol, final_x, final_y) == false) {
        printf("Solution doesn't exist");
        return false;
    }

    printSolution(sol);
    return true;
}

bool solveMazeUtil(int maze[N][M], int x, int y, int sol[N][M], int final_x, int final_y)
{

    if (isSafe(maze, x, y, sol) == true) {
        sol[x][y] = 1;


        if (x == N - 1 && y == M - 1 && maze[x][y] == 1) {
            sol[x][y] = 1;
            return true;
        }

        if (solveMazeUtil(maze, x + 1, y, sol, final_x, final_y) == true)
            return true;

        if (solveMazeUtil(maze, x - 1, y, sol, final_x, final_y) == true)
            return true;

        if (solveMazeUtil(maze, x, y + 1, sol, final_x, final_y) == true)
            return true;

        if (solveMazeUtil(maze, x, y - 1, sol, final_x, final_y) == true)
            return true;

        sol[x][y] = 0;
        return false;
    }

    return false;
}


int main()
{




    int maze[N][M];

    ifstream laberinto;
    string line;
    laberinto.open("laberinto.txt");

    if (laberinto.is_open())
    {
        int fila = 0;
        while (getline(laberinto, line))
        {

            for (int i = 0, j=0; i < line.size(); i++) {
                if (line[i] == '0') {
                    maze[fila][j] = 0;
                    j++;
                }
                else if (line[i] == '1') {
                    maze[fila][j] = 1;
                    j++;
                }
            }

            cout << line << '\n';
            fila++;
        }
        laberinto.close();
    }


    auto start = chrono::steady_clock::now();

    solveMaze(maze, 0, 0, 49, 29);

    auto end = chrono::steady_clock::now();

    cout << "Puntero funcion Elapsed time in seconds 1000 elements : "
         << chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000000.0
         << " seconds" << endl;


    return 0;
}