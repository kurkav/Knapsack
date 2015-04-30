#ifndef KNAPSACK_H
#define KNAPSACK_H
#include <iostream>
#include <string.h>
#include <stdio.h>

class Knapsack{
public:
    Knapsack();
    ~Knapsack();
    /*
     * Weights, Costs will be only read
     */
    virtual void SetupProblem(unsigned int Length, unsigned int LengthFixed,int Weight, unsigned int * Weights, unsigned int * Costs) = 0;

    /*returns
     * Cost of knapsack on success
     */
    virtual int Solve(bool * Inserted) = 0;
};


#endif // KNAPSACKRECURSIVE_H
