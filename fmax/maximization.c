// Include Custom maximization.h Library
#include "maximization.h"

// Definitions
#define fit 1
#define unfit 0
#define uint unsigned int

// Constants
// Population size
const int N_POPULATION = 10;
// Number of generations
const int N_GENERATIONS = 100;
// Number of deaths per generation
const int N_DEATHS = N_POPULATION * 0.2;
// Probability of mutation
const float P_MUTATION = 0.4;

int main()
{
    /*
    printf("s_power(0,0,0,0) = %f\n", s_power(0,0,0,0));
    printf("phi(0,0,0,0,1237566.4,54783217.5,1237896431.1,325123467.37) = %f\n", phi(0,0,0,0,1237566.4,54783217.5,1237896431.1,325123467.37));
    double max = get_max(100,100,100,100);
    double min = get_min(100,100,100,100);
    printf("max: %f\tmin: %f\n", max, min);

    */
    // Initialize variables
    int id = 1;
    int n_gen = 1;
    int i, j;

    struct Individual best, parent1, parent2, child, survivor;

    struct Individual * population = (struct Individual *) malloc(sizeof(struct Individual) * N_POPULATION);
    struct Individual * next_population = (struct Individual *) malloc(sizeof(struct Individual) * N_POPULATION);
    struct RouletteCompartments  *genetic_roulette = (struct RouletteCompartments *) malloc(sizeof(struct RouletteCompartments) * N_POPULATION);

    // Initialize population
    id = initiate(population, id, N_POPULATION);
    calculate(population, N_POPULATION);

    evaluate(population, N_POPULATION);
    view_population(population, N_POPULATION, n_gen);

    reset_selection(population, N_POPULATION);

    for(j = 0; j < N_DEATHS; ++j)
    {
        parent1 = select(population, genetic_roulette, N_POPULATION, fit);
        parent2 = select(population, genetic_roulette, N_POPULATION, fit);
        printf("%d and %d\n", parent1.id, parent2.id);
        //child = mutation(crossover(parent1, parent2, ++id), P_MUTATION);
        //NextPopulation[j] = child;
    }


    free(population);
    free(next_population);
    free(genetic_roulette);

    // Initiate Genetic Algorithm
    //while(n_gen <= N_GENERATIONS)
    //{

}
