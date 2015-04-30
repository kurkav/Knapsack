#include <iostream>
#include <stdio.h>
#include <string.h>
#include "knapsacksolver.h"
using namespace std;

int main(){
    KnapsackSolver *solver = new KnapsackSolver();
    solver->PrepareTestProblem(0);
    solver->Solve(RECURSIVE);
    solver->PrintResult();
    return 0;
}

