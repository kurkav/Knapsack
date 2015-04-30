#ifndef KNAPSACKSOLVER_H
#define KNAPSACKSOLVER_H
#include "knapsack.h"
#include "knapsackxeon.h"
#include "knapsackrecursive.h"
#include <math.h>
enum SolverType {RECURSIVE, DYNAMIC};

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

    unsigned int FExpectedCost;

    bool **FInserted;
    bool *FInsertedBest;

    void PrepareVariables(unsigned int Length,unsigned int LengthFixed);
public:
    KnapsackSolver();
    void PrepareTestProblem(int i);
    void Solve(SolverType Type);
    void PrintResult();
};

#endif // KNAPSACKSOLVER_H
