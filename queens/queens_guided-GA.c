// Include Libraries
#include "lib/general.h"
#include "lib/utils.h"
#include "lib/genetics.h"

int main(){
    // Constants
    // Number of queens
    const int N_QUEENS = 80;
    // Population size
    const int N_POPULATION = 1000;
    // Number of generations
    const int N_GENERATIONS = 10000;
    // Number of deaths per generation
    const int N_DEATHS = N_POPULATION * 0.3;
    // Probability of mutation
    const float P_MUTATION = 0.2;
    // Number of genes to mutate
    const int LAMBDA = 4;
    // Force the algorithm to continue after finding a solution
    const bool FORCE_TO_CONTINUE = false;
    // Frequency to summarize
    const int SUMMARIZE_FREQ = 500;
    // Number of selections in the tournament_selection function
    const int TOURNAMENT_SELECTIONS = 3;

    //Create, initialise text files
    char file_fitness[] = "DataVisualization/Fitness.csv";
    FILE *f = fopen(file_fitness, "w");
    if (f == NULL){printf("Error opening file!\n");exit(1); }

    // Initialize variables
    int id = 1;
    int n_gen = 1;
    int i;
    Individual * best, parent1, parent2, child, survivor, *population, *nextpopulation, *candidate;

    // Save memory space for population and genetic roulette
    Individual *P = (Individual *) malloc(sizeof(Individual) * N_POPULATION);
    Individual *Q = (Individual *) malloc(sizeof(Individual) * N_POPULATION);
    RouletteCompartments *genetic_roulette = malloc_roulette(N_POPULATION);

    // Set population pointers
    population = P;
    nextpopulation = Q;
    Individual *T;

    // Initialize best individual
    best = &population[0];

    // Initialize population and genetic roulette
    initiate(population, id, N_POPULATION, N_QUEENS);
    id = N_POPULATION;
    evaluate(population, N_POPULATION, N_QUEENS);
    //view_population(population, N_POPULATION, N_QUEENS, n_gen);

    //write_fitness(&f, file_fitness, population, N_POPULATION, n_gen);

    // Initiate Genetic Algorithm
    while(n_gen <= N_GENERATIONS)
    {
        reset_selection(population, N_POPULATION);
        for (i = 0; i < N_DEATHS; i++)
        {
            parent1 = selection(population, genetic_roulette, N_POPULATION, N_QUEENS, fit);
            parent2 = selection(population, genetic_roulette, N_POPULATION, N_QUEENS, fit);
            child = heuristic_mutation(ordered_crossover(parent1, parent2, ++id, N_QUEENS), N_QUEENS, LAMBDA, P_MUTATION);
            nextpopulation[i] = child;
        }

        reset_selection(population, N_POPULATION);
        for (i = N_DEATHS; i < N_POPULATION; i++)
        {
            survivor = selection(population, genetic_roulette, N_POPULATION, N_QUEENS, fit);
            nextpopulation[i] = survivor;
        }

        T = population;
        population = nextpopulation;
        nextpopulation = T;

        evaluate(population, N_POPULATION, N_QUEENS);

        for (i = 0; i < N_POPULATION; i++)
            if (population[i].scorer < best->scorer) best = &population[i];

        if ((n_gen-1)%SUMMARIZE_FREQ == 0)
            summarize(population, best, n_gen-1, N_QUEENS);

        n_gen++;


        if (best->scorer == 0 && !FORCE_TO_CONTINUE) break;

        if (N_GENERATIONS <= 1000){
            write_fitness(&f, file_fitness, population, N_POPULATION, n_gen);
        }
    }
    n_gen--;

    if(best->scorer != 0)
        printf("\n No optimal individual found... \n");
    else
    {
        printf("Found at least one optimal individual id %d, scorer: %d\n", best->id, best->scorer);
        express_genes(*best, N_QUEENS);
    }
}
