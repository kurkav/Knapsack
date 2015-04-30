#include "knapsackrecursive.h"
//--------------------------------------------------------------------------------------------------------------------------------
KnapsackRecursive::KnapsackRecursive()
{
    FItemWeight = NULL;
    FItemCost = NULL;
    FLength = 0;
    FLengthFixed = 0;
    FWeight = 0;
    FBestCost = 0;
}
KnapsackRecursive::~KnapsackRecursive(){
    delete[] FInserted;
}
//--------------------------------------------------------------------------------------------------------------------------------
int KnapsackRecursive::PrepareVariables(unsigned int Length, unsigned int LengthFixed,int Weight){
    FLength = Length;
    FLengthFixed = LengthFixed;
    FWeight = Weight;
    FInserted= new bool[FLength];
    return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------
void KnapsackRecursive::SetupProblem(unsigned int Length, unsigned int LengthFixed,int Weight, unsigned int * Weights, unsigned int * Costs){
    FItemWeight = Weights;
    FItemCost = Costs;

    PrepareVariables(Length, LengthFixed, Weight);
}
//--------------------------------------------------------------------------------------------------------------------------------
void KnapsackRecursive::goDeeper(unsigned int pos,unsigned int weight,unsigned int cost){
    if(weight > FWeight || pos >= FLength){
        return;
    }
    if(cost > FBestCost){
        memcpy(FInsertedBest,FInserted, sizeof(bool)*FLength);
        FBestCost = cost;
    }
    FInserted[pos] = true;
    goDeeper(pos+1,weight+FItemWeight[pos], cost+FItemCost[pos]);
    FInserted[pos] = false;
    goDeeper(pos+1,weight, cost);
}
//--------------------------------------------------------------------------------------------------------------------------------
int KnapsackRecursive::Solve(bool * Inserted){
    FBestCost = 0;
    memset(FInserted, 0, sizeof(bool)*FLength);
    FInsertedBest = Inserted;
    FCost = 0;
    unsigned int weight = 0;
    unsigned int cost = 0;
/*    for(int i = 0; i < FLength; i++){
        printf("%d \t%d\n",FItemWeight[i], FItemCost[i]) ;
    }*/
    for(unsigned int i = 0; i < FLengthFixed; i++){
        if(Inserted[i]){
            weight += FItemWeight[i];
            cost += FItemCost[i];
        }
    }

    goDeeper(FLengthFixed,weight,cost);
    return FBestCost;
}
