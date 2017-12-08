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
    //view_population(population, args.n_population, args.n_queens, 0);

    if (args.write_fitness)
        write_fitness(&file, file_fitness, population, args.n_population, 1);

    // Get number of deaths per generation
    int n_deaths = (int) (args.n_population * args.death_ratio);

    // Print out useful information
    print_program_name();
    print_license_header();
    print_problem_description(args);
    print_GA_input();
    print_GA_constants(args);
    print_configuration(args);

    // Initiate Genetic Algorithm
    results = genetic_algorithm(args.strategy, population, nextpopulation,
                                best, genetic_roulette, parent1, parent2,
                                child, survivor, id, n_deaths, args, file,
                                file_fitness);

    // Print results
    //results.best = &population[0];
    print_GA_completed();
    print_results(results, args.n_queens);

    // Free memory
    free(P);
    free(Q);
    free(genetic_roulette);
    for (int i = 0; i < args.n_population; i++)
        free(population[i].genes.rows);
}
