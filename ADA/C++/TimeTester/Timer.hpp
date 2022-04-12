#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <iostream>
#include <chrono>

using namespace std;

class Timer {
public:
  chrono::system_clock::time_point start;

  Timer(){
    start = chrono::system_clock::now();
  }

  ~Timer(){
    auto end = chrono::system_clock::now();
    chrono::duration<double> duration = end-start;
    cout << endl;
    cout<< duration.count() << std::endl;
  }

};

#endif // TIMER_H_INCLUDED