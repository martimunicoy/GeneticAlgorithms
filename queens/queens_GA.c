// Include Libraries
#include "lib/definitions.h"

#include "lib/queens_GA.h"
#include "lib/constants.h"
#include "lib/utils.h"
#include "lib/genetics.h"
#include "lib/arguments.h"
#include "lib/strategies.h"




int main(int argc, char* argv[]){
    // Parse arguments
    struct Args args = args_parser(argc, argv);

    // Create, initialize text files
    FILE * file;
    char file_fitness[] = "DataVisualization/Fitness.csv";
    if (args.write_fitness)
    {
        file = fopen(file_fitness, "w");
        if (file == NULL)
        {
            printf("Error opening file!\n");
            exit(1);
        }
    }

    // Initialize variables
    int id = 1;
    Individual * best, * population, * nextpopulation;
    Individual parent1, parent2, child, survivor;

    // Save memory space for population and genetic roulette
    Individual * P = (Individual *) malloc(sizeof(Individual) * args.n_population);
    Individual * Q = (Individual *) malloc(sizeof(Individual) * args.n_population);
    RouletteCompartments * genetic_roulette = malloc_roulette(args.n_population);

    // Set population pointers
    population = P;
    nextpopulation = Q;

    // Initialize best individual
    best = &population[0];

    // Initialize population and genetic roulette
    initiate(population, id, args.n_population, args.n_queens);
    id = args.n_population;
    evaluate(population, args.n_population, args.n_queens);
    //view_population(population, args.n_population, args.n_queens, n_gen);

    if (args.write_fitness)
        write_fitness(&file, file_fitness, population, args.n_population, 1);

    // Get number of deaths per generation
    int n_deaths = (int) (args.n_population * args.death_ratio);

    // Initiate Genetic Algorithm
    best = genetic_algorithm(args.strategy, population, nextpopulation, best,
                             genetic_roulette, parent1, parent2, child,
                             survivor, id, n_deaths, args, file, file_fitness);

    // Print results
    if (print_results(best->scorer))
        express_genes(* best, args.n_queens);

    // Free memory
    free(P);
    free(Q);
    free(genetic_roulette);
}
