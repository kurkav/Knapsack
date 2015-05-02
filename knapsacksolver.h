#ifndef KNAPSACKSOLVER_H
#define KNAPSACKSOLVER_H
#include "solvers/knapsack.h"
#include "solvers/knapsackxeon.h"
#include "solvers/knapsackrecursive.h"
#include <math.h>
#include <stdlib.h> /* srand, rand */
#include <omp.h>

#define PROBLEM_LIMIT 100000
enum SolverType {RECURSIVE, DYNAMIC, OMPDYNAMIC, OMPRECURSIVE};

class KnapsackSolver{
private:
    unsigned int *FItemWeight;
    unsigned int *FItemCost;

    unsigned int FLength;
    unsigned int FLengthFixed;

    unsigned int FWeightLimit;
    unsigned int FCost;
    unsigned int FBestCost;
    unsigned int FWorkerCount;
    unsigned int FSolverCount;
    unsigned int FExpectedCost;
    unsigned int FThreadCount;
    bool **FInserted;
    bool *FInsertedBest;

    void PrepareVariables(unsigned int Length,unsigned int LengthFixed);

public:
    KnapsackSolver();
    void PrepareTestProblem(int i);
    void Solve(SolverType Type);
    void PrintProblem();
    void PrintResult();
    void SetFixedLength(unsigned int fl);
    void SetSolverCount(unsigned int sc);
};

#endif // KNAPSACKSOLVER_H
