#include "knapsacksolver.h"

KnapsackSolver::KnapsackSolver()
{
    FLengthFixed = 0;
    FInserted = NULL;
    FItemWeight = NULL;
    FItemCost = NULL;
    FInsertedBest = NULL;
}

void KnapsackSolver::PrepareVariables(unsigned int Length,unsigned int LengthFixed){
    if(FLength != Length && FLengthFixed != LengthFixed)return;
    FLength = Length;
    FLengthFixed = LengthFixed;

    if(FItemWeight != NULL) delete [] FItemWeight;
    if(FInsertedBest != NULL) delete [] FInsertedBest;
    if(FInsertedBest != NULL) delete [] FInsertedBest;

    int Steps = pow(2,FLengthFixed);
    if(FInserted != NULL) {
        for(int i = 0; i < Steps; i++){
            if(FInserted[i] != NULL){
                delete [] FInserted[i];
            }
        }
        delete [] FInserted;
    }

    FItemCost = new unsigned int[FLength];
    FItemWeight = new unsigned int[FLength];
    FInsertedBest = new bool[FLength];
    FInserted = new bool*[Steps];
    for(int i = 0; i < Steps; i++){
        FInserted[i] = new bool[FLength];
    }
}

void KnapsackSolver::PrepareTestProblem(int Problem){
    switch(Problem){
        case 0:{
            PrepareVariables(22,0);
            //FLength= 22;
            unsigned int taskZeroC[] = {150 ,35 ,200 ,60 ,60 ,45 ,60 ,40 ,30 ,10 ,70 ,30 ,15 ,10 ,40 ,70 ,75 ,80 ,20 ,12 ,50 ,10};
            unsigned int taskZeroW[] = {9 ,13 ,153 ,50 ,15 ,68 ,27 ,39 ,23 ,52 ,11 ,32 ,24 ,48 ,73 ,42 ,43 ,22 ,7 ,18 ,4 ,30};
            for(unsigned int i = 0; i < FLength; i++){
                FItemCost[i] = taskZeroC[i];
                FItemWeight[i] = taskZeroW[i];
            }
            FExpectedCost = 930;
            FWeightLimit = 400;
            break;
        }
        case 1:{
            PrepareVariables(4,0);
            //FLength = 4;
            unsigned int taskZeroC[] = {150 ,35 ,200 ,60};
            unsigned int taskZeroW[] = {9 ,13 ,153 ,50};
            for(unsigned int i = 0; i < FLength; i++){
                FItemCost[i] = taskZeroC[i];
                FItemWeight[i] = taskZeroW[i];
            }
            FExpectedCost = 930;
            FWeightLimit = 200;
            break;
        }
        default:{
            PrepareVariables(7,0);
            //FLength = 7;
            unsigned int defaultC[] = {12,10,8,11,14,7,9};
            unsigned int defaultW[] = {4,6,5,7,3,1,6};
            for(unsigned int i = 0; i < FLength; i++){
                FItemCost[i] = defaultC[i];
                FItemWeight[i] = defaultW[i];
            }

            FExpectedCost = 44;
            FWeightLimit = 18;
        }
    }
}

void KnapsackSolver::Solve(SolverType Type){
    Knapsack *knapsack;

    int steps = pow(2,FLengthFixed);
    switch(Type){
        case DYNAMIC:
            knapsack = new KnapsackXeon();
            break;
        case RECURSIVE:
            knapsack = new KnapsackRecursive();
            break;
    }
    knapsack->SetupProblem(FLength,FLengthFixed,FWeightLimit,FItemWeight,FItemCost);
    int SolutionCost;

    for(int i = 0; i < steps;i++){
        SolutionCost = knapsack->Solve(FInserted[i]);
        if(SolutionCost > FBestCost){
            FBestCost = SolutionCost;
            memcpy(FInsertedBest, FInserted[i], FLength*sizeof(bool));
        }
    }


}

void KnapsackSolver::PrintResult(){
    //if(FInserted == NULL) return;
    if(FItemWeight == NULL) return;
    if(FItemCost == NULL) return;

    unsigned int price = 0;
    unsigned int weight = 0;
    for(unsigned int i = 0; i < FLength; i++){
        if(FInsertedBest[i]){
 //           printf("%d \n %d\n", FItemWeight[i], FItemCost[i]);
            price += FItemCost[i];
            weight+= FItemWeight[i];
        }else{
          //cout << 0 << "  ";
        }
    }
    //cout << endl;

    printf("FoundPrice %d \t expected %d\n",FBestCost ,FExpectedCost);
    printf("FoundWeight %d\t maximaly %d\n",weight,FWeightLimit);
    if(FBestCost == FExpectedCost && weight < FWeightLimit){
        printf("Correct Solution\n");
    }else{
        printf("Incorrect Solution\n");
    }
}
