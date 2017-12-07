// Include Libraries
#include "lib/general.h"
#include "lib/utils.h"
#include "lib/genetics.h"
#include "lib/arguments.h"

int main(int argc, char* argv[]){
    // Parse arguments
    struct Args args = args_parser(argc, argv);

    // Create, initialize text files
    char file_fitness[] = "DataVisualization/Fitness.csv";
    FILE *f = fopen(file_fitness, "w");
    if (f == NULL){printf("Error opening file!\n");exit(1); }

    // Initialize variables
    int id = 1;
    int n_gen = 1;
    int i;
    Individual * best, parent1, parent2, child, survivor, *population, *nextpopulation, *candidate;

    // Save memory space for population and genetic roulette
    Individual *P = (Individual *) malloc(sizeof(Individual) * args.n_population);
    Individual *Q = (Individual *) malloc(sizeof(Individual) * args.n_population);
    RouletteCompartments *genetic_roulette = malloc_roulette(args.n_population);

    // Set population pointers
    population = P;
    nextpopulation = Q;
    Individual *T;

    // Initialize best individual
    best = &population[0];

    // Initialize population and genetic roulette
    initiate(population, id, args.n_population, args.n_queens);
    id = args.n_population;
    evaluate(population, args.n_population, args.n_queens);
    //view_population(population, args.n_population, args.n_queens, n_gen);

    //write_fitness(&f, file_fitness, population, args.n_population, n_gen);

    // Initiate Genetic Algorithm
    while(n_gen <= args.n_generations || INFINITE_GENERATIONS)
    {
        reset_selection(population, args.n_population);
        for (i = 0; i < N_DEATHS; i++)
        {
            parent1 = roulette_selection(population, genetic_roulette, args.n_population, args.n_queens, args.fract_weight, args.denom_power, fit);
            parent2 = roulette_selection(population, genetic_roulette, args.n_population, args.n_queens, args.fract_weight, args.denom_power, fit);
            child = heuristic_mutation(ordered_crossover(parent1, parent2, ++id, args.n_queens), args.n_queens, args.lambda, args.p_mutation);
            nextpopulation[i] = child;
        }

        reset_selection(population, args.n_population);
        for (i = N_DEATHS; i < args.n_population; i++)
        {
            survivor = roulette_selection(population, genetic_roulette, args.n_population, args.n_queens, args.fract_weight, args.denom_power, fit);
            nextpopulation[i] = survivor;
        }

        T = population;
        population = nextpopulation;
        nextpopulation = T;

        evaluate(population, args.n_population, args.n_queens);

        for (i = 0; i < args.n_population; i++)
            if (population[i].scorer < best->scorer) best = &population[i];

        if (args.summarize_freq != 0)
            if ((n_gen-1) % args.summarize_freq == 0)
                summarize(population, best, n_gen-1, args.n_queens);

        n_gen++;


        if (best->scorer == 0 && !FORCE_TO_CONTINUE) break;

        if (args.n_generations <= 1000){
            write_fitness(&f, file_fitness, population, args.n_population, n_gen);
        }
    }
    n_gen--;

    printf("\n");
    printf("+-------------------------------+\n");
    printf("|            RESULTS            |\n");
    printf("+-------------------------------+\n");
    printf("\n");

    if(best->scorer != 0)
        printf("\nNo optimal individual found.\n");
    else
        express_genes(*best, args.n_queens);
    printf("\n");
}
