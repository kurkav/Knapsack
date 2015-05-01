#include <iostream>
#include <stdio.h>
#include <string.h>
#include "knapsacksolver.h"
#include <ctime>
using namespace std;

time_t startTime,endTime;


void Start(){
    time(&startTime);
}
void End(string s){
    time(&endTime);

    cout <<"---------"<<endl;
    cout << "Timer: " << endTime - startTime << " s " << endl;
    cout << s << endl;
    cout <<"---------"<<endl;
}

int main(){
    KnapsackSolver *solver = new KnapsackSolver();
    solver->PrepareTestProblem(30);
    Start();
    solver->Solve(RECURSIVE);
    End("Recursive solver");
    solver->PrintResult();
    Start();
    cout << endl<< endl;
    solver->Solve(OMPRECURSIVE);
    End("OMP Recursive solver");

    solver->PrintResult();
    return 0;
}

