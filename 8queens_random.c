// Include Libraries
#include "8queens.h"

// Definitions
#define fitness 1
#define unfitness 0
#define Individual struct Individual
#define Genes struct Genes

// Constants
// Number of queens (DON'T CHANGE! (YET))
const int N_QUEENS = 8;
// Population size
const int N_POPULATION = 1;

int main(){
    // Initialize variables
    int id = 1;

    // Initialize best individual
    Individual best;
    best.scorer = 127;

    // Initialize population
    Individual *Population = (Individual *) malloc(sizeof(Individual) * N_POPULATION);
    id = initiate(Population, id, N_POPULATION, N_QUEENS);

    // First evaluation of the population
    evaluate(Population, N_POPULATION, N_QUEENS);

    // Iterate until finding a solution
    int i;
    while(best.scorer != 0){
        for(i = 0; i < N_POPULATION; ++i){
            if(Population[i].scorer < best.scorer)
            {
                printf("%i\n", best.scorer);
                best = Population[i];
            }
        }
        if(best.scorer > 0){
            // Each new generation has got brand new individuals with random genes
            id = initiate(Population, id, N_POPULATION, N_QUEENS);
            evaluate(Population, N_POPULATION, N_QUEENS);
        }
    }
    printf("Found individual %d\n", best.id);
    express_genes(best);
}
