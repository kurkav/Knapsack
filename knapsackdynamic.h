#ifndef KNAPSACKDYNAMIC_H
#define KNAPSACKDYNAMIC_H

class KnapsackDynamic
{
private:
    unsigned int *FWeight;
    unsigned int *FCost;
    bool *FUsed;
    unsigned int FLength;

public:
    KnapsackDynamic();
    /*
     * Weight, Cost, Used will by only read
     */
    void SetupProblem(unsigned int Length, unsigned int * Weight, unsigned int * Cost, bool * Used);

    /*returns
     * 0 on success
     */
    int Solve(Sack * sack);
};

#endif // KNAPSACKDYNAMIC_H
