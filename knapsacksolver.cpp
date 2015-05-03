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
    FSolverCount = 1;
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
        for(int i = 0; i < FSolverCount; i++){
            if(FInserted[i] != NULL){
                delete [] FInserted[i];
            }
        }
        delete [] FInserted;
    }

    FItemCost = new unsigned int[FLength];
    FItemWeight = new unsigned int[FLength];
    FInsertedBest = new bool[FLength];
    FInserted = new bool*[FSolverCount];
    for(int i = 0; i < FSolverCount; i++){
        FInserted[i] = new bool[FLength];
    }
}

void KnapsackSolver::SetFixedLength(unsigned int fl){
    if(fl > FLength-3 || fl == FLengthFixed) return;
    FLengthFixed = fl;
}

void KnapsackSolver::SetSolverCount(unsigned int sc){
    if(FSolverCount == sc) return;
    //delete old
    if(FInserted != NULL) {
        for(int i = 0; i < FSolverCount; i++){
            if(FInserted[i] != NULL){
                delete [] FInserted[i];
            }
        }
        delete [] FInserted;
    }

    //create new
    FSolverCount = sc;
    FInserted = new bool*[FSolverCount];
    for(int i = 0; i < FSolverCount; i++){
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
        Problem = (Problem > -Problem)? Problem: -Problem;
        Problem = (Problem < PROBLEM_LIMIT)? Problem:PROBLEM_LIMIT;
        Problem = (Problem > 10)? Problem:10;
        PrepareVariables(Problem,FLengthFixed);
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
    if(FBestCost != 0){
        //compare with previous solution
        FExpectedCost = FBestCost;
    }
    FBestCost = 0;
    Knapsack **knapsack = new Knapsack*[FSolverCount];
    bool omp = false;
    int steps = pow(2,FLengthFixed);
    for(unsigned int i = 0; i < FSolverCount; i++){
    switch(Type){
        case OMPDYNAMIC:
            omp = true;
        case DYNAMIC:
            knapsack[i] = new KnapsackDynamic();
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
        omp_set_dynamic(0);     // Explicitly disable dynamic teams
        omp_set_num_threads(FSolverCount);
        #pragma omp parallel
        {
        #pragma omp for
            for(int i = 0; i < steps;i++){
                Knapsack * sack = NULL;
                bool * inserted = NULL;
                #pragma omp critical
                {   //find usable solver
                    while(sack == NULL)
                    for(unsigned int s = 0; s < FSolverCount; s++){
                        if(knapsack[s]->Available){
                            knapsack[s]->Available = false;
                            sack = knapsack[s];
                            inserted = FInserted[s];
                            break;
                        }
                    }
                }
                //prepare fixed part
                int I = i;
                for(int j = FLengthFixed-1; j >=0;j--){
                    inserted[j] =  (I&1);
                    I = I>>1;
                }
                SolutionCost = sack->Solve(inserted);
                #pragma omp critical
                {
                    //we want only one updating of best solution at a time
                    if(SolutionCost > FBestCost){
                        FBestCost = SolutionCost;
                        memcpy(FInsertedBest, inserted, FLength*sizeof(bool));
#if DEBUG
                        std::cout << "omp, new solution: "<< SolutionCost << std::endl;
                        for(unsigned int k = 0; k < FLength; k++){
                            if(FLengthFixed == k){
                                std::cout << "-";
                            }
                            std::cout << (FInsertedBest[k])?"1":"0";
                        }
                        std::cout<<std::endl;
#endif
                    }
                }
                sack->Available = true;
            }
        }
    }else{
        for(int i = 0; i < steps;i++){
            bool * inserted = FInserted[0];

            //prepare fixed part
            int I = i;
            for(int j = FLengthFixed-1; j >=0;j--){
                inserted[j] =  (I&1);
                I = I>>1;
            }

            SolutionCost = knapsack[0]->Solve(inserted);
            if(SolutionCost > FBestCost){
                FBestCost = SolutionCost;
#if DEBUG
                std::cout << "new solution: "<< SolutionCost << std::endl;
                for(unsigned int i = 0; i < FLength; i++){
                    if(FLengthFixed == i){
                        std::cout << "-";
                    }
                    std::cout << (inserted[i])?"1":"0";
                }
                std::cout<<std::endl;
#endif

                memcpy(FInsertedBest, inserted, FLength*sizeof(bool));
            }
        }
     }
    if(knapsack != NULL){
        for(int i = 0; i < FSolverCount; i++){
            if(knapsack[i] != NULL)delete knapsack[i];
        }
        delete [] knapsack;
    }

}

void KnapsackSolver::PrintResult(){
    if(FInserted == NULL) return;
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
    printf("FoundPrice %d \t expected %d\n",price ,FExpectedCost);
    printf("FoundWeight %d\t maximaly %d\n",weight,FWeightLimit);
    if(FBestCost == FExpectedCost && weight <= FWeightLimit){
        printf("Correct Solution\n");
    }else{
        printf("Incorrect Solution\n");
    }
}


void KnapsackSolver::PrintProblem(){
    for(int i = 0; i < FLength; i++){
        std::cout << FItemCost[i] << " ";
    }
    std::cout<<std::endl;
    for(int i = 0; i < FLength; i++){
        std::cout << FItemWeight[i] << " ";
    }
    std::cout<<std::endl;
}
