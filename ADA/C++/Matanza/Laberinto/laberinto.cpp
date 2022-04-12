#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <sstream>

#define rows 50
#define cols 30


using namespace std;

int StartX, StartY, DestX, DestY, MoveX[4] = {0, 1, 0, -1}, MoveY[4] = {1, 0, -1, 0};

vector<vector<int>> Maze;
vector<vector<int>> Sol;

void init(){
    Maze.assign(rows, vector<int>(cols, 0));
    Sol.assign(rows, vector<int>(cols, 0));
}

vector<vector<int>> loadMaze(string _lab){
    std::vector<std::vector<int>> _Maze;
    std::ifstream ifs(_lab);
    std::string tempstr;
    int tempint;

    while (std::getline(ifs, tempstr)) {
        std::istringstream iss(tempstr);
        std::vector<int> tempv;
        while (iss >> tempint) {
            tempv.push_back(tempint);
        }
        _Maze.push_back(tempv);
    }

    return _Maze;
}


void PrintSolution () {
    cout << "Laberinto resuelto:" << '\n';
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // limpiamos de los rastros de BT
            if ( Sol[i][j] == 1){
                Sol[i][j] = 0;
            }
            // **************
            cout << Sol[i][j] << " ";
        }
        cout << '\n';
    }
}

bool IsSafe (int x, int y) {
    if (x >= 0 && x < rows && y >= 0 && y < cols && (Maze[x][y] == 0) && (Sol[x][y] == 0)) {
        return true;
    }
    return false;
}

bool MazeSolveUtility (int X, int Y) {
    if ((X == DestX) && (Y == DestY)) {
        Sol[X][Y] = 7;
        return true;
    }
    for (int i = 0; i < 4; i++) {
        int NextX = X + MoveX[i];
        int NextY = Y + MoveY[i];
        if (IsSafe (NextX, NextY)) {
            Sol[NextX][NextY] = 7;
            if (MazeSolveUtility (NextX, NextY)) {
                return true;
            } else {
                Sol[NextX][NextY] = 1; // cuando regresa y ve q no hay camino BT se marca 1
            }
        }
    }
    return false;
}

void MazeSolve () {
    if (IsSafe (StartX, StartY) && IsSafe (DestX, DestY)) {
        Sol[StartX][StartY] = 7;
        if (MazeSolveUtility (StartX, StartY) == false) {
            cout << "El laberinto no tiene solucion, Habil te crees -_- :v" << '\n';
        }
    } else {
        cout << "El destino es invalido." << '\n';
    }
}

int main () {
    init();
    Maze = loadMaze("laberinto.txt");
    cout << "Ingresa las coordenadas de inicio y las coordenadas de llegada (0,0) -> (n-1, n-1) :" << '\n';
    cin >> StartX >> StartY >> DestX >> DestY;

    //auto start = std::chrono::system_clock::now();
    //MazeSolve ();
    //auto end = std::chrono::system_clock::now();
    //std::chrono::duration<double> elapsed_seconds = end - start;
    //cout << "tiempo " << elapsed_seconds.count() << endl;

    unsigned t0, t1;
    t0=clock();
    MazeSolve ();
    t1=clock();

    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "tiempo " << time << '\n';
    PrintSolution ();

    return 0;
}