/*****************************************************************************
 *                                                                           *
 *               <N Queens Problem Solver - Genetic Algorithm>               *
 *             Copyright (C) <2017>   <Municoy, M., Salgado, D.>             *
 *                                                                           *
 *   Contact the authors at: mail@martimunicoy.com                           *
 *                           daniel.salgado@e-campus.uab.cat                 *
 *                                                                           *
 *   This program is free software: you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation, either version 3 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *****************************************************************************/

// Include Libraries
#include "definitions.h"
#include "queens_GA.h"
#include "constants.h"
#include "genetics.h"
#include "arguments.h"
#include "utils.h"
#include "strategies.h"

int main(int argc, char* argv[]){
    // Print welcome
    print_program_name();
    print_license_header();

    // Parse arguments
    struct Args args = args_parser(argc, argv);

    // Print problem description
    print_problem_description(args);

    // Create, initialize text files
    FILE * fitness_file, *genes_file;
    if (args.write_fitness)
    {
        fitness_file = fopen(args.fitness_dir, "w");
        if (fitness_file == NULL)
        {
            printf("Error opening file!\n");
            exit(1);
        }
    }
    if (args.write_genes)
    {
        genes_file = fopen(args.genes_dir, "w");
        if (genes_file == NULL)
        {
            printf("Error opening file!\n");
            exit(1);
        }
    }

    // Initialize variables
    int id = 1;
    Individual * best, * population, * nextpopulation;
    Individual *parent1, *parent2, *survivor, child;
    GAResults results;

    // Save memory space for population and genetic roulette
    Individual *P = (Individual *) malloc(sizeof(Individual) * args.n_population);
    Individual *Q = (Individual *) malloc(sizeof(Individual) * args.n_population);
    RouletteCompartments *genetic_roulette = malloc_roulette(args.n_population);

    // Set population pointers
    population = P;
    nextpopulation = Q;

    // Initialize randomly best individual
    best = &population[0];

    // Initialize population and genetic roulette
    initiate(population, id, args.n_population, args.n_queens);
    id = args.n_population;
    evaluate(population, args.n_population, args.n_queens);

    // In case we want to write down fitness data
    if (args.write_fitness)
        write_fitness(&fitness_file, args.fitness_dir, population,
                      args.n_population, 1);

    // In case we want to write down genes data
    if (args.write_genes)
        write_population_genes(&genes_file, args.genes_dir, population,
                               args.n_population, args.n_queens);

    // Get number of deaths per generation
    int n_deaths = (int) (args.n_population * args.death_ratio);

    // Print out useful information
    print_GA_input();
    print_GA_constants(args);
    print_configuration(args);

    // Initiate Genetic Algorithm
    results = genetic_algorithm(population, nextpopulation, best,
                                genetic_roulette, parent1, parent2, child,
                                survivor, id, n_deaths, args, fitness_file,
                                genes_file);

    // Print results
    //results.best = &population[0];
    print_GA_completed();
    print_results(results, args.n_queens);

    // Free memory
    free(P);
    free(Q);
    free(genetic_roulette);
}
