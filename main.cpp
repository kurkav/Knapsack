#include <iostream>
#include <stdio.h>
#include <string.h>
#include "knapsacksolver.h"
using namespace std;

int mmax(int a, int b){
    if(a < b){
        return b;
    }else {
        return a;
    }
}


int KnapsackDynamic(bool * N, unsigned int * Weights, unsigned int* Costs, int WeightLimit, int Count){
    int **table = new int*[Count+1];
    int **used = new int*[Count+1];
    for(int i = 0; i <= Count; i++){
        table[i] = new int[WeightLimit+1];
        table[i][0] = 0;
        memset(table[i], 0, sizeof(int)*WeightLimit+1);

        used[i] = new int[WeightLimit+1];
        used[i][0] = 0;
        memset(used[i], 0, sizeof(int)*WeightLimit+1);
    }
    for(int i = 1; i <= Count; i++){
        for(unsigned int w = 0; w <= WeightLimit; w++){
            if(Weights[i-1] <= w){
                int a = table[i-1][w];
                int b = table[i-1][w-Weights[i-1]]+Costs[i-1];
                if(a > b){
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

    for(int l = 0; l <= Count; l++){
         for(int j = 0; j <= WeightLimit; j++){
             cout << table[l][j] << "\t";
         }
         cout << endl;
     }
    cout<<"-----------"<<endl;
    for(int l = 0; l <= Count; l++){
        for(int j = 0; j <= WeightLimit; j++){
            cout << used[l][j] << " ";
        }
        cout << endl;
    }

    int w = WeightLimit;
    int i = Count;
    while(w > 0 && i > 0){
        if(used[i][w] == 1){
            N[i-1] = 1;
            w = w-Weights[i-1];
        }else{
            N[i-1] = 0;
       }
        i--;

    }
    return table[Count][WeightLimit];
    for(int i = 0; i < Count; i++){
        delete[] table[i];
        delete[] used[i];
    }
    delete [] table;
    delete[] used;
}

int main(){
    KnapsackSolver *solver = new KnapsackSolver();
    solver->PrepareTestProblem(0);
    solver->Solve(RECURSIVE);
    solver->PrintResult();
    return 0;
}

