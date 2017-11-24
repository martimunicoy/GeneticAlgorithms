// Include Libraries
#include "8queens.h"

// Definitions
#define fit 1
#define unfit 0
#define Individual struct Individual
#define Genes struct Genes
#define RouletteCompartments struct RouletteCompartments

// Constants
// Number of queens (DON'T CHANGE! (YET))
const int N_QUEENS = 8;
// Population size
const int N_POPULATION = 100;
// Number of generations
const int N_GENERATIONS = 100;
// Number of deaths per generation
const int N_DEATHS = N_POPULATION * 0.5;
// Probability of mutation
const float P_MUTATION = 0.4;

int main(){
    // Initialize variables
    int id = 1;
    int n_gen = 1;
    int i, j;
    Individual best, parent1, parent2, child, survivor, *Population, *NextPopulation;

    // Save memory space for Population and genetic roulette
    Individual *P = (Individual *) malloc(sizeof(Individual) * N_POPULATION);
    Individual *Q = (Individual *) malloc(sizeof(Individual) * N_POPULATION);
    RouletteCompartments *genetic_roulette = malloc_roulette(N_POPULATION);

    // Set Population pointers
    Population = P;
    NextPopulation = Q;
    Individual *T;

    // Initialize best individual
    best.scorer = sum_down(N_QUEENS);

    // Initialize population and genetic roulette
    id = initiate(Population, id, N_POPULATION, N_QUEENS);
    view_population(Population, N_POPULATION, N_QUEENS, n_gen);

    // Initiate Genetic Algorithm
    while(n_gen <= N_GENERATIONS)
    {
        evaluate(Population, N_POPULATION, N_QUEENS);

        reset_selection(Population, N_POPULATION);
        for(j = 0; j < N_DEATHS; ++j)
        {
            parent1 = select(Population, genetic_roulette, N_POPULATION, N_QUEENS, fit);
            parent2 = select(Population, genetic_roulette, N_POPULATION, N_QUEENS, fit);
            child = mutation(crossover(parent1, parent2, ++id, N_QUEENS), N_QUEENS, P_MUTATION);
            NextPopulation[j] = child;
        }

        reset_selection(Population, N_POPULATION);
        for(j=N_DEATHS; j < N_POPULATION; ++j)
        {
            survivor = select(Population, genetic_roulette, N_POPULATION, N_QUEENS, fit);
            NextPopulation[j] = survivor;
        }

        T = Population;
        Population = NextPopulation;
        NextPopulation = T;

        //view_population(Population, N_POPULATION, N_QUEENS, n_gen);

        ++n_gen;
    }
    view_population(NextPopulation, N_POPULATION, N_QUEENS, n_gen);
    printf("Found individual %d, scorer: %d\n", best.id, best.scorer);
}
