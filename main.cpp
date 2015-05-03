#include <iostream>
#include <stdio.h>
#include <string.h>
#include "knapsacksolver.h"
#include <ctime>
#include <sys/time.h>
using namespace std;

timeval startTime,endTime;


void Start(){
    gettimeofday(&startTime,NULL);
}
void End(string s){
    gettimeofday(&endTime,NULL);

    long t = (endTime.tv_sec-startTime.tv_sec)*1000+((endTime.tv_usec-startTime.tv_usec)/1000.0);
    cout <<"---------"<<endl;
    cout << "Timer: " << t << " ms " << endl;
    cout << s << endl;
    cout <<"---------"<<endl;
}

int main(){
    KnapsackSolver *solver = new KnapsackSolver();
    solver->PrepareTestProblem(1000);
    solver->SetFixedLength(5);
    solver->SetSolverCount(24);


    Start();
    solver->Solve(DYNAMIC);
    End("Dynamic solver");

    Start();
    cout << endl<< endl;
    solver->Solve(OMPDYNAMIC);
    End("OMP dynamic solver");

    return 0;
}

