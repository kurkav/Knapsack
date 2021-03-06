#include "knapsackxeon.h"
//--------------------------------------------------------------------------------------------------------------------------------
KnapsackDynamic::KnapsackDynamic()
{
    FItemWeight = NULL;
    FItemCost = NULL;
    FLength = 0;
    FLengthFixed = 0;
    FWeight = 0;
    FCost = 0;
}
KnapsackDynamic::~KnapsackDynamic(){}
//--------------------------------------------------------------------------------------------------------------------------------
int KnapsackDynamic::PrepareVariables(unsigned int Length, unsigned int LengthFixed,int Weight){
    FLength = Length;
    FLengthFixed = LengthFixed;
    FWeight = Weight;
    return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------
void KnapsackDynamic::SetupProblem(unsigned int Length, unsigned int LengthFixed,int Weight, unsigned int * Weights, unsigned int * Costs){
    FItemWeight = Weights;
    FItemCost = Costs;

    PrepareVariables(Length, LengthFixed, Weight);
}
//--------------------------------------------------------------------------------------------------------------------------------
int KnapsackDynamic::Dynamic(bool * Inserted){
    FCost = 0;
    //int * N, int * Weights, int* Costs, int WeightLimit, int Count
    bool *N = Inserted;
    unsigned int *Weights = FItemWeight;
    unsigned int *Costs = FItemCost;
    unsigned int WeightLimit = FWeight;
    int Count = FLength-FLengthFixed;
    unsigned int **table = new unsigned int*[Count+1];
    bool **used = new bool*[Count+1];
    for(int i = 0; i <= Count; i++){
        table[i] = new unsigned int[WeightLimit+1];
        table[i][0] = 0;
        memset(table[i], 0, sizeof(unsigned int)*WeightLimit+1);

        used[i] = new bool[WeightLimit+1];
        used[i][0] = 0;
        memset(used[i], 0, sizeof(bool)*WeightLimit+1);
    }
    for(int i = 1; i <= Count; i++){
        for(unsigned int w = 0; w <= WeightLimit; w++){
            if(Weights[i-1] <= w){
                int a = table[i-1][w];
                int b = table[i-1][w-Weights[i-1]]+Costs[i-1];
                if(a >= b){
                    table[i][w] = a;
                    used[i][w] = 0;
                }else{
                    table[i][w] = b;
                    used[i][w] = 1;
                }
            }else{
                table[i][w] = table[i-1][w];
                used[i][w] = 0;
            }

        }
    }

#if 0
    for(int l = 0; l <= Count; l++){
         for(unsigned int j = 0; j <= WeightLimit; j++){
             printf("%d\t", table[l][j]);
         }
         printf("\n");
     }

    printf("------------\n");
    for(int l = 0; l <= Count; l++){
        for(unsigned int j = 0; j <= WeightLimit; j++){
             printf("%d",used[l][j]);
        }
        printf("\n");
    }
#endif

    unsigned int w = WeightLimit;
    unsigned int i = Count;
    while(w > 0 && i > 0){
        if(used[i][w] == 1){
            N[i-1] = true;
            w = w-Weights[i-1];
        }else{
            N[i-1] = false;
       }
        i--;

    }

    for(int i = 0; i <= Count; i++){
        delete[] table[i];
        delete[] used[i];
    }
    delete [] table;
    delete[] used;
}

int KnapsackDynamic::Solve(bool * Inserted){
    Dynamic(&Inserted[FLengthFixed]);
    unsigned int value = 0;
    for(unsigned int i = 0; i < FLength; i++){
        //std::cout << (Inserted[i])?"1":"0";

        if(Inserted[i]){
            value+=FItemCost[i];
        }
    }
    //std::cout <<std::endl;
    return value;
}
