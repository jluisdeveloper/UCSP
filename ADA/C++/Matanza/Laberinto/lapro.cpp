#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std;

class Maze {
    public:
        int startX, startY, endX, endY, rows, cols;
        vector<vector<int>> maze;
        vector<vector<int>> sol;
        vector<int>MoveX;
        vector<int>MoveY;

        Maze(string _lab);
        Maze(vector<vector<int>> _maze); // start 0 0 , end 29 49
        Maze(int _startX, int _startY, int _endX, int _endY, int _rows, int _cols);

        bool isSafe(int x, int y);
        bool mazeHelper(int x, int y);
        void mazeSolve();

        vector<vector<int>> loadMaze(string _lab);
        void getPoints(vector<vector<int>> &_maze);

        void printSolution();
};

Maze::Maze(string _lab) {
    this->maze = loadMaze(_lab);

    this->rows = this->maze.size();
    this->cols = this->maze[0].size();

    this->sol.assign(this->rows, vector<int>(this->cols, 0));

    this->getPoints(this->maze);

    this->MoveX = { 0, 1, 0, -1 };
    this->MoveY = { 1, 0, -1, 0 };


}



Maze::Maze(vector<vector<int>> _maze) {
    this->rows = 4;
    this->cols = 4;
    this->startX = 1;
    this->startY = 1;
    this->endX = 3;
    this->endY = 3;

//    this->maze.assign(this->rows, vector<int>(this->cols, 0));
    this->sol.assign(this->rows, vector<int>(this->cols, 0));
    this->maze = _maze;

    this->MoveX = { 0, 1, 0, -1 };
    this->MoveY = { 1, 0, -1, 0 };
}

Maze::Maze(int _startX, int _startY, int _endX, int _endY, int _rows, int _cols) {
    this->rows = _rows;
    this->cols = _cols;
    this->startX = _startX;
    this->startY = _startY;
    this->endX = _endX;
    this->endY = _endY;

    this->maze.assign(this->rows, vector<int>(this->cols, 0));
    this->sol.assign(this->rows, vector<int>(this->cols, 0));

    this->MoveX = { 0, 1, 0, -1 };
    this->MoveY = { 1, 0, -1, 0 };
}

bool Maze::isSafe(int x, int y) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->cols && (this->maze[x][y] == 0) && (this->sol[x][y] == 0)) {
        return true;
    }
    return false;
}

bool Maze::mazeHelper(int x, int y) {
    if ((x == this->endX) && (y == this->endY)) {
        this->sol[x][y] = 7;
        return true;
    }
    for (int i = 0; i < 4; i++) {
        int NextX = x + this->MoveX[i]; // probar si se puede mejorar antes del loop
        int NextY = y + this->MoveY[i];
        if (isSafe (NextX, NextY)) {
            this->sol[NextX][NextY] = 7;
            if (mazeHelper (NextX, NextY)) {
                return true;
            } else {
                this->sol[NextX][NextY] = 0; // cuando regresa
            }
        }
    }
    return false;
}

void Maze::mazeSolve() {
    if (isSafe (this->startX, this->startY) && isSafe(this->endX, this->endY)) {
        this->sol[this->startX][this->startY] = 7;
        if (mazeHelper (this->startX, this->startY) == false) {
            cout << "El laberinto no tiene solucion, Habil te crees -_- :v" << endl;
        }
    } else {
        cout << "El destino es invalido." << endl;
    }
}

void Maze::printSolution() {
    for (int i = 0; i < this->rows ; ++i) {
        for (int j = 0; j < this->cols ; ++j) {
            cout << this->sol[i][j]<< " ";
        }
        cout << endl;
    }
}

vector<vector<int>> Maze::loadMaze(string _lab) {
    std::vector<std::vector<int>> v;
    std::ifstream ifs(_lab);
    std::string tempstr;
    int tempint;

    while (std::getline(ifs, tempstr)) {
        std::istringstream iss(tempstr);
        std::vector<int> tempv;
        while (iss >> tempint) {
            tempv.push_back(tempint);
        }
        v.push_back(tempv);
    }

    return v;
}

void Maze::getPoints(vector <vector<int>> &_maze) {
    for (int i = 0; i < _maze.size() ; ++i) {
        for (int j = 0; j < _maze[0].size() ; ++j) {
            if (_maze[i][j] == 2){
                this->startX = i;
                this->startY = j;
                _maze[i][j] = 0;
            } else if (_maze[i][j] == 3){
                this->endX = i;
                this->endY = j;
                _maze[i][j] = 0;
            }
        }
    }
}

int main (){
    Maze A("laberinto.txt");

    auto start = std::chrono::system_clock::now();
    A.mazeSolve();
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    cout << "tiempo " << elapsed_seconds.count() << endl;

    A.printSolution();

//    int filas, columnas;
//    vector<vector<int>> laberinto;
//
//
//
//    cout << "Dimensiones del laberinto filas x columnas:" << endl;
//    cin >> filas >> columnas;

//    laberinto[filas][columnas];
//
//    laberinto.assign(filas, vector<int>(columnas, 0));
//
//
//    cout << "Copia la matriz de 0 y 1:" << endl;
//    for (int i = 0; i < filas; i++) {
//        for (int j = 0; j < columnas; j++) {
//            cin >> laberinto[i][j];
//        }
//    }
    //Maze test(laberinto);
    //test.printSolution();
    return 0;
}
