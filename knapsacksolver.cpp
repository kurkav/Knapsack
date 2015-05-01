#include "knapsacksolver.h"

KnapsackSolver::KnapsackSolver()
{
    FLengthFixed = 0;
    FLength = 0;
    FInserted = NULL;
    FItemWeight = NULL;
    FItemCost = NULL;
    FInsertedBest = NULL;
    FBestCost = 0;
    FSolverCount = 4;
}

void KnapsackSolver::PrepareVariables(unsigned int Length,unsigned int LengthFixed){
    if(FLength == Length && FLengthFixed == LengthFixed)return;
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
        int I = i;
        for(int j = FLengthFixed-1; j >=0;j--){
            FInserted[i][j] =  (I&1);
            I = I>>1;
        }
       /*
        for(int j = 0; j < FLengthFixed; j++){
            std::cout << FInserted[i][j];
        }
        std::cout<<std::endl;
        */
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
        Problem = (Problem > -Problem)? Problem: -Problem;
        Problem = (Problem < PROBLEM_LIMIT)? Problem:PROBLEM_LIMIT;
        Problem = (Problem > 10)? Problem:10;
        PrepareVariables(Problem,3);
        FWeightLimit = 0;
        FExpectedCost = 0;
        for(unsigned int i = 0; i < FLength; i++){
            FItemCost[i] = rand() % 10;
            FItemWeight[i] = rand()% 10;

            FExpectedCost += FItemCost[i];
            FWeightLimit += FItemWeight[i];
        }
        FExpectedCost = FExpectedCost*0.6666;
        FWeightLimit = FWeightLimit*0.6666;
        }
    }
}

void KnapsackSolver::Solve(SolverType Type){
    FBestCost = 0;
    Knapsack **knapsack = new Knapsack*[FSolverCount];
    bool omp = false;
    int steps = pow(2,FLengthFixed);
    for(unsigned int i = 0; i < FSolverCount; i++){
    switch(Type){
        case DYNAMIC:            
            knapsack[i] = new KnapsackXeon();
            break;
        case OMPRECURSIVE:
            omp = true;
        case RECURSIVE:
            knapsack[i] = new KnapsackRecursive();
            break;
        }
        knapsack[i]->SetupProblem(FLength,FLengthFixed,FWeightLimit,FItemWeight,FItemCost);
        knapsack[i]->ID = i;
    }

    int SolutionCost;

    if(omp){

        #pragma omp parallel num_threads(4)
        {
        #pragma omp for
            for(int i = 0; i < steps;i++){
                Knapsack * sack = NULL;
                #pragma omp critical
                {
                    while(sack == NULL)
                    for(int s = 0; s < FSolverCount; s++){
                        if(knapsack[s]->Available){
                            knapsack[s]->Available = false;
                            sack = knapsack[s];
                            break;
                        }
                    }
                }
                SolutionCost = sack->Solve(FInserted[i]);
                #pragma omp critical
                {
                    //we want only one updating of best solution at a time
                    if(SolutionCost > FBestCost){
                        std::cout << "omp, new solution: "<< SolutionCost << std::endl;
                        FBestCost = SolutionCost;
                        memcpy(FInsertedBest, FInserted[i], FLength*sizeof(bool));
                    }
                    sack->Available = true;
                }
            }
        }
    }else{
        for(int i = 0; i < steps;i++){
            SolutionCost = knapsack[0]->Solve(FInserted[i]);
            if(SolutionCost > FBestCost){
                std::cout << "new solution: "<< SolutionCost << std::endl;
                FBestCost = SolutionCost;
                memcpy(FInsertedBest, FInserted[i], FLength*sizeof(bool));
            }
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
FBestCost = price;
    printf("FoundPrice %d \t expected %d\n",FBestCost ,FExpectedCost);
    printf("FoundWeight %d\t maximaly %d\n",weight,FWeightLimit);
    if(FBestCost == FExpectedCost && weight < FWeightLimit){
        printf("Correct Solution\n");
    }else{
        printf("Incorrect Solution\n");
    }
}
