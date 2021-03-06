#ifndef KNAPSACKRECURSIVE_H
#define KNAPSACKRECURSIVE_H
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "solvers/knapsack.h"

class KnapsackRecursive:public Knapsack{
private:
    unsigned int *FItemWeight;
    unsigned int *FItemCost;
    unsigned int FLength;
    unsigned int FLengthFixed;
    unsigned int FWeight;
    unsigned int FCost;
    unsigned int FBestCost;
    bool *FInserted;
    bool *FInsertedBest;
    int **FTableCost;
    int **FTableUsed;

    int KnapsackDynamic(bool * Inserted);
    int PrepareVariables(unsigned int Length, unsigned int LengthFixed,int Weight);
    void goDeeper(unsigned int pos,unsigned int weight,unsigned int cost);
public:
    KnapsackRecursive();
    ~KnapsackRecursive();
    /*
     * Weights, Costs will be only read
     */
    void SetupProblem(unsigned int Length, unsigned int LengthFixed,int Weight, unsigned int * Weights, unsigned int * Costs);

    /*returns
     * Cost of knapsack on success
     */
    int Solve(bool * Inserted);
};


#endif // KNAPSACKRECURSIVE_H
