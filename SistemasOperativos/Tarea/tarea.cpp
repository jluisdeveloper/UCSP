#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <math.h>
using namespace std;

class Process{
private:
    int PID;
    int CPUTime;
    int arrivalTime;
    int priority;
    long waitTime;
    long turnaroundTime;
    int numOfContextSwitching;
    int timeOfCompletion;
public:
    Process(){PID = 0; CPUTime = 0; arrivalTime = 0; priority = 0; waitTime = 0; turnaroundTime = 0; numOfContextSwitching = 0; timeOfCompletion = 0;};
    void setPID(int _PID){PID = _PID;};
    void setCPUTime(int _CPUTime){CPUTime = _CPUTime;};
    void setArrivalTime(int _ArrivalTime){arrivalTime = _ArrivalTime;};
    void setPriority(int _Priority){priority = _Priority;};
    void addWaitTime(double time){waitTime += time;};
    void addTurnaroundTime(double time){turnaroundTime += time;};
    void incNumOfContextSwitching(){++numOfContextSwitching;};
    void setTimeOfCompletion(int _timeOfCompletion){timeOfCompletion = _timeOfCompletion;};
    int getPID() const {return PID;};
    int getCPUTime() const {return CPUTime;};
    int getArrivalTime() const {return arrivalTime;};
    int getPriority() const {return priority;};
    long getWaitTime() const {return waitTime;};
    long getTurnaroundTime() const {return turnaroundTime;};
    int getNumOfContextSwitching() const {return numOfContextSwitching;};
    int getTimeOfCompletion() const {return timeOfCompletion;};
    void operator=(Process p);
};


void Process::operator=(Process p){
    PID = p.getPID();
    CPUTime = p.getCPUTime();
    arrivalTime = p.getArrivalTime();
    priority = p.getPriority();
    waitTime = p.getWaitTime();
    turnaroundTime = p.getTurnaroundTime();
    numOfContextSwitching = p.getNumOfContextSwitching();
}

bool operator<(const Process &p1, const Process &p2){
    return p1.getCPUTime() > p2.getCPUTime();
};


void readFile(string fileName, vector<Process>&processes);
void sortProcesses(vector<Process>&processes);
void addWaitTime(deque<Process>&schedule, int count);
void addTurnaroundTime(deque<Process>&schedule, int count);
void addWaitTime(priority_queue<Process>&schedule, int count);
void addTurnaroundTime(priority_queue<Process>&schedule, int count);
void addTurnaroundTime(priority_queue<Process>&schedule, int count);
void removeProcess(priority_queue<Process>&schedule, Process p);
void FCFS(vector<Process>processes);
void SRTF(vector<Process>processes);
void RR(int quantum, vector<Process>processes);

int main(int argc, const char * argv[]){
    string randomize;
    int quantum = 1;
    stringstream ss;
    
    vector<Process>processes;
    string algorithm = argv[2];
    readFile(argv[1], processes);
    
    sortProcesses(processes);
    
    if(algorithm == "FCFS" || algorithm == "fcfs"){
        cout << "-First Come First Served Algorithm-" << endl;
    }else if(algorithm == "SRTF" || algorithm == "srtf"){
        cout << "-Shortest Remaining Time First-" << endl;
    }else if(algorithm == "RR" || algorithm == "rr"){
        cout << "-Round Robin-" << endl;
        RR(quantum, processes);
    }else{
        cout << "Invalid algorithm name." << endl;
    }
    return 0;
}

void readFile(string fileName, vector<Process>&processes){
    int PID, arrivalTime, CPUTime;
    string tempLine, word;
    ifstream infile;
    infile.open(fileName);
    if(infile){
        getline(infile, tempLine);
        while(!infile.eof()){
            Process *process = new Process();
            infile >> PID;
            process->setPID(PID);
            infile >> arrivalTime;
            process->setArrivalTime(arrivalTime);
            infile >> CPUTime;
            process->setCPUTime(CPUTime);
            processes.push_back(*process);
            delete process;
        }
    }else{
        cout << "Could not open file with file name \"" << fileName << "\"." << endl;
    }
    infile.close();
    processes.pop_back(); //The file has an empty line at the end
}

void sortProcesses(vector<Process>&processes){
    //Since we won't be be sorting large quantities bubblesort O(n^2) will be ok.
    Process temp;
    for(int i = 0 ; i < ( processes.size() - 1 ); ++i){
        for(int j = 0 ; j < processes.size() - i - 1; ++j){
            if(processes[j].getArrivalTime() > processes[j + 1].getArrivalTime()){ //smallest to largest
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void addWaitTime(deque<Process>&schedule, int count){
    for(int i = 0; i < schedule.size(); ++i){
        schedule[i].addWaitTime(count);
    }
}

void addTurnaroundTime(deque<Process>&schedule, int count){
    for(int i = 0; i < schedule.size(); ++i){
        schedule[i].addTurnaroundTime(count);
    }
}

void addWaitTime(priority_queue<Process>&schedule, int count){
    Process temp;
    for(int i = 0; i < schedule.size(); ++i){
        temp = schedule.top();
        temp.addWaitTime(count);
        schedule.pop();
        schedule.push(temp);
    }
}

void addTurnaroundTime(priority_queue<Process>&schedule, int count){
    Process temp;
    for(int i = 0; i < schedule.size(); ++i){
        temp = schedule.top();
        temp.addTurnaroundTime(count);
        schedule.pop();
        schedule.push(temp);
    }
}

void removeProcess(priority_queue<Process>&schedule, Process p){
    vector<Process>copy;
    
    for(int i = 0; i < schedule.size(); ++i){
        copy.push_back(schedule.top());
        schedule.pop();
    }
    
    for(int i = 0; i < copy.size(); ++i){
        if(copy[i].getPID() == p.getPID()){
            copy.erase(copy.begin() + i);
        }
    }
    
    for(int i = 0; i < copy.size(); ++i){
        schedule.push(copy[i]);
    }
}



void RR(int quantum, vector<Process>processes){
    int time = 0, counter = 0, runTime = 0;
    double avgWait = 0, avgTurn = 0, averageCPU = 0, totalSwitch = 0;
    string hold;
    bool next = false, change = false;
    Process *run = nullptr;
    deque<Process>schedule;
    vector<Process>copy;
    vector<Process>finished;
    cout << "Number of processes: " << processes.size() << endl;
    cout << "Press [ENTER] to begin RR quantum " << quantum << endl;
    getline(cin, hold);
    
    cout << "-- Gnatt Chart -- (PID->CPU Burst Time)" << endl << "|";
    
    for(int i = 0; i < processes.size(); ++i){
        Process *p = new Process();
        copy.push_back(*p);
        delete p;
    }
    
    for(int i = 0; i < processes.size(); ++i){
        copy[i] = processes[i];
    }
    
    while(true){
        if(copy[0].getArrivalTime() > time){
            ++time;
        }else{
            break;
        }
    }
    
    while(!copy.empty() || !schedule.empty() || counter != 0){
        while(true){
            if(copy[0].getArrivalTime() <= time && !copy.empty()){
                schedule.push_back(copy[0]);
                copy.erase(copy.begin());
            }else{
                break;
            }
        }
        
        if(counter <= 0){
            run = &schedule.front();
            schedule.pop_front();
            run->incNumOfContextSwitching();
        }else if(counter == quantum){
            if(run->getCPUTime() <= 0){
                run->setTimeOfCompletion(time);
                cout << " " << run->getPID() << "->" << runTime << " |";
                change = true;
                finished.push_back(*run);
                counter = -1;
                next = true;
                --time;
            }else{
                cout << " " << run->getPID() << "->" << runTime << " |";
                change = true;
                schedule.push_back(*run);
                counter = -1;
                next = true;
                --time;
            }
        }
        
        if(!next){
            if(run->getCPUTime() <= 0){
                cout << " " << run->getPID() << "->" << runTime << " |";
                change = true;
                run->setTimeOfCompletion(time);
                finished.push_back(*run);
                counter = -1;
                --time;
            }else{
                addTurnaroundTime(schedule, 1);
                addWaitTime(schedule, 1);
                run->addTurnaroundTime(1);
                run->setCPUTime(run->getCPUTime() - 1);
            }
        }
        
        if(next){
            next = false;
        }
        
        ++runTime;
        ++counter;
        ++time;
        
        if(change){
            change = false;
            runTime = 0;
        }
    }
    
    cout << endl << endl << "---- Process List ----" << endl;
    
    for(int i = 0; i < finished.size(); ++i){
        cout << i + 1 << ":" << endl;
        if(finished[i].getPID() / 10 < 1){
            cout << "----  PID: " << finished[i].getPID() << "   ----" << endl;
        }else if(finished[i].getPID() >= 100){
            cout << "----  PID: " << finished[i].getPID() << " ----" << endl;
        }else{
            cout << "----  PID: " << finished[i].getPID() << "  ----" << endl;
        }
        cout << "Time of completion: " << finished[i].getTimeOfCompletion() << "ms" << endl;
        cout << "Time spent waiting: " << finished[i].getWaitTime() << "ms" << endl;
        cout << "  Turn Around time: " << finished[i].getTurnaroundTime() << "ms" << endl;
        cout << "  Context Switches: " << finished[i].getNumOfContextSwitching() << endl << endl;
        
        averageCPU += processes[i].getCPUTime();
        avgWait += finished[i].getWaitTime();
        avgTurn += finished[i].getTurnaroundTime();
        totalSwitch += finished[i].getNumOfContextSwitching();
    }
    
    cout << "___________STATS___________" << endl;
    cout << "  Average CPU burst time: " << ceil(averageCPU / processes.size()) << "ms" << endl;
    cout << "       Average wait time: " << ceil(avgWait / finished.size()) << "ms" << endl;
    cout << "Average turn around time: " << ceil(avgTurn / finished.size()) << "ms" << endl;
    cout << "   Average response time: " << ceil(avgWait / finished.size()) << "ms" << endl;
    cout << "  Total context switches: " << totalSwitch << endl;
}
