#ifndef KNAPSACKXEON_H
#define KNAPSACKXEON_H
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "solvers/knapsack.h"

class KnapsackDynamic : public Knapsack{
private:
    unsigned int *FItemWeight;
    unsigned int *FItemCost;
    unsigned int FLength;
    unsigned int FLengthFixed;
    unsigned int FWeight;
    unsigned int FCost;
    int **FTableCost;
    int **FTableUsed;

    int Dynamic(bool * Inserted);
    int PrepareVariables(unsigned int Length, unsigned int LengthFixed,int Weight);
public:
    KnapsackDynamic();
~KnapsackDynamic();
    /*
     * Weights, Costs will be only read
     */
    void SetupProblem(unsigned int Length, unsigned int LengthFixed,int Weight, unsigned int * Weights, unsigned int * Costs);

    /*returns
     * Cost of knapsack on success
     */
    int Solve(bool * Inserted);
};

#endif // KNAPSACKXEON_H
