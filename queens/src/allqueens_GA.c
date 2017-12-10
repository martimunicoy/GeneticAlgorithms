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

// Function bodies
int main(int argc, char* argv[]){
    // Print welcome
    print_program_name();
    print_license_header();

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
    int minutes;
    int id = 1;
    Individual *best, *population, *nextpopulation;
    Individual *parent1, *parent2, child, *survivor;
    struct timeval start, end;

    // Save memory space for population and genetic roulette
    Individual *P = (Individual *) malloc(sizeof(Individual) *
                                          args.n_population);
    Individual *Q = (Individual *) malloc(sizeof(Individual) *
                                          args.n_population);
    RouletteCompartments *genetic_roulette = malloc_roulette(
                                                 args.n_population);

    // Save dynamic memory space for a list of all solutions
    bool repeated;
    int solutions_num = 0;
    int solutions_length = 10;
    int solutions_increment = 10;
    Individual *solutions = (Individual *) malloc(sizeof(Individual) *
                             solutions_length);
    initiate(solutions, 0, solutions_length, args.n_queens);

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
    print_GA_input();
    print_GA_constants_all(args);
    print_configuration(args);

    // Initiate Genetic Algorithm
    print_strategy_info(args.strategy);
    print_GA_starts();

    int i, j, k;
    int n_gen = 1;
    int sieve = 0;
    unsigned char exit_code = 0;
    Individual *T;

    int n_perms = factorial(args.lambda);
    unsigned int **permutations = (unsigned int **) malloc(n_perms *
                                   sizeof(unsigned int *));
    for(i = 0; i < n_perms; i++)
        permutations[i] = (unsigned int *) malloc(args.lambda *
                           sizeof(unsigned int));
    Individual *childs = (Individual *) malloc(sizeof(Individual)
                                               * n_perms);
    initiate(childs, 0, n_perms, args.n_queens);

    // Start counter
    gettimeofday(&start, NULL);

    while (n_gen <= args.n_generations || args.infinite_generations)
    {
        reset_selection(population, args.n_population);
        for (i = 0; i < n_deaths; i++)
        {
            parent1 = roulette_selection(population,
                                         genetic_roulette,
                                         args.n_population,
                                         args.n_queens,
                                         args.fract_weight,
                                         args.denom_power,
                                         fit);
            parent2 = roulette_selection(population,
                                         genetic_roulette,
                                         args.n_population,
                                         args.n_queens,
                                         args.fract_weight,
                                         args.denom_power,
                                         fit);
            child = ordered_crossover(parent1, parent2, ++id,
                                      args.n_queens),
            swapping_mutation(&child, args.n_queens, args.p_mutation);
            nextpopulation[i] = child;
        }

        // Selection
        reset_selection(population, args.n_population);
        for (i = n_deaths; i < args.n_population; i++)
        {
            survivor = roulette_selection(population,
                                          genetic_roulette,
                                          args.n_population,
                                          args.n_queens,
                                          args.fract_weight,
                                          args.denom_power, fit);
            nextpopulation[i] = *survivor;
        }
        // Swap populations
        swap_populations(&population, &nextpopulation);

        // Look out for a solution and assure that it has not been found before
        evaluate(population, args.n_population, args.n_queens);
        for (i = 0; i < args.n_population; i++)
        {
            if (population[i].scorer == 0)
            {
                repeated = false;
                for (j = 0; j < solutions_num; j++)
                {
                    repeated = compare(&population[i], &solutions[j],
                                       args.n_queens);
                    if (repeated)
                        break;
                }
                if (!repeated)
                {
                    if (solutions_num < solutions_length)
                        copy_individual(&population[i],
                                        &solutions[solutions_num],
                                        args.n_queens);
                    else
                    {
                        solutions_length += solutions_increment;
                        solutions = (Individual *) realloc(solutions,
                                                       sizeof(Individual) *
                                                       solutions_length);
                        for (j = solutions_length - solutions_increment;
                             j < solutions_length; j++)
                            initiate(&solutions[j], 0, 1, args.n_queens);
                        copy_individual(&population[i],
                                        &solutions[solutions_num],
                                        args.n_queens);
                        solutions[solutions_num] = population[i];
                    }
                    solutions_num++;
                    sieve = 0;
                }
                else
                {
                    population[i].scorer = sum_down(args.n_queens);
                    sieve++;
                }
            }
        }

        // Find best individual
        for (i = 0; i < args.n_population; i++)
                if (population[i].scorer < best->scorer)
                    best = &population[i];

        // Print summary
        if (args.summarize_freq != 0)
            if ((n_gen-1) % args.summarize_freq == 0)
            {
                gettimeofday(&end, NULL);
                minutes = (int) (end.tv_sec  - start.tv_sec) / 60;
                print_summary(population, best, args.n_population, n_gen-1,
                              minutes);
            }

        // Sum up 1 generation
        n_gen++;

        // Look out for the sieve
        if (sieve > args.sieve)
        {
            exit_code = 2;
            break;
        }

        // Write fitness
        if (args.write_fitness && n_gen <= args.max_fitness_points)
            write_fitness(&file, file_fitness, population, args.n_population,
                          n_gen);

    // End of While loop
    }

    // Stop counter
    gettimeofday(&end, NULL);

    // Calculate GA running time in minutes
    minutes = (int) (end.tv_sec  - start.tv_sec) / 60;

    // Wrap the results and return them
    GAResults results = {best, population, args.n_population, n_gen-1,
                         exit_code};

    // Print results
    print_GA_completed();
    printf(" Number of different solutions: %d\n\n", solutions_num);
    print_results_all(results, args.n_queens);
    printf("\n");
    printf("========================================================");
    printf("========================\n");
    for (i = 0; i < solutions_num; i++)
    {
        printf("\n - Solution %d:\n", i + 1);
        printf("\n");
        printf(" (%4d, ", solutions[i].genes.rows[0]);
        for (j = 1; j < args.n_queens - 1; j++)
        {
            if (j % 13 == 0)
                printf("\n  ");
            printf("%4d, ", solutions[i].genes.rows[j]);
        }
        printf("%4d)\n", solutions[i].genes.rows[args.n_queens-1]);
        printf("\n");
        results.best = &solutions[i];
        if (i == 0)
            write_solution(results, args.n_queens, false);
        else
            write_solution(results, args.n_queens, true);

    }
    printf("========================================================");
    printf("========================\n");
    printf("\n");


    // Free memory
    for (i = 0; i < n_perms; i++)
        free(childs[i].genes.rows);
    free(childs);
    free(permutations);
    for (i = 0; i < args.n_population; i++)
        free(P[i].genes.rows);
    free(P);
    free(Q);
    free(genetic_roulette);
}
