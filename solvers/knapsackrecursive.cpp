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
    if(weight > FWeight || pos > FLength){
        return;
    }
    if(cost >= FBestCost){
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
    for(unsigned int i = 0; i < FLengthFixed;i++){
        FInserted[i] = Inserted[i];
    }
    for(unsigned int i = FLengthFixed; i<FLength;i++){
        Inserted[i]= false;
        FInserted[i] = false;
    }
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

 #if 0
    int sol = 0,w = 0;
    for(unsigned int i = 0; i < FLength;i++){
        if(FLengthFixed == i){
            std::cout << "-";
        }
        std::cout << (Inserted[i])?"1":"0";

        if(Inserted[i]){
            sol += FItemCost[i];
            w += FItemWeight[i];
        }
    }
    std::cout << std::endl<< ID<<":_rec sol/weight: " << sol << "/" << w <<std::endl<<std::endl;
#endif
    return FBestCost;
}
