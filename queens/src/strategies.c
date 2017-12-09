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

/*****************************************************************************/
// Includes
/*****************************************************************************/
#include "queens_GA.h"
#include "constants.h"
#include "genetics.h"
#include "arguments.h"
#include "utils.h"
#include "strategies.h"
#include "definitions.h"

/*****************************************************************************/
// Functions
/*****************************************************************************/
GAResults genetic_algorithm(int strategy, Individual * population,
                            Individual * nextpopulation, Individual * best,
                            RouletteCompartments * genetic_roulette,
                            Individual parent1, Individual parent2,
                            Individual child, Individual survivor, int id,
                            int n_deaths, struct Args args, FILE * file,
                            char * file_fitness)
{
    // Print GA information
    print_strategy_info(strategy);
    print_GA_starts();

    // Initiate variables
    int i, minutes;
    int n_gen = 1;
    unsigned char exit_code = 0;
    Individual *T;
    struct timeval start, end;

    // Load Heuristic Mutation tools
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

    // Start GA loop
    while(n_gen <= args.n_generations || args.infinite_generations)
    {
        switch (strategy)
        {
            case 1:
                // Mutation and crossover
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
                    nextpopulation[i] = survivor;
                }
                break;

            case 2:
                // Mutation and crossover
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
                    heuristic_mutation(&child, permutations, childs,
                                       args.n_queens, args.lambda,
                                       n_perms, args.p_mutation);
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
                    nextpopulation[i] = survivor;
                }
                break;

            case 3:
                // Mutation and crossover
                for (i = 0; i < n_deaths; i++)
                {
                    reset_selection(population, args.n_population);
                    parent1 = tournament_selection(population,
                                                   args.n_population,
                                                   args.tournament_selections,
                                                   replace);
                    parent2 = tournament_selection(population,
                                                   args.n_population,
                                                   args.tournament_selections,
                                                   replace);
                    child = ordered_crossover(parent1, parent2, ++id,
                                              args.n_queens),
                    heuristic_mutation(&child, permutations, childs,
                                       args.n_queens, args.lambda,
                                       n_perms, args.p_mutation);
                    nextpopulation[i] = child;
                }

                // Selection
                reset_selection(population, args.n_population);
                for (i = n_deaths; i < args.n_population; i++)
                {
                    reset_selection(population, args.n_population);
                    survivor = tournament_selection(population,
                                                   args.n_population,
                                                   args.tournament_selections,
                                                   replace);
                    nextpopulation[i] = survivor;
                }
                break;

            case 4:
                // Mutation and crossover
                for (i = 0; i < n_deaths; i++)
                {
                    parent1 = tournament_selection(population,
                                                   args.n_population,
                                                   args.tournament_selections,
                                                   not_replace);
                    parent2 = tournament_selection(population,
                                                   args.n_population,
                                                   args.tournament_selections,
                                                   not_replace);
                    child = ordered_crossover(parent1, parent2, ++id,
                                              args.n_queens),
                    heuristic_mutation(&child, permutations, childs,
                                       args.n_queens, args.lambda,
                                       n_perms, args.p_mutation);
                    nextpopulation[i] = child;
                }

                // Selection
                for (i = n_deaths; i < args.n_population; i++)
                {
                    reset_selection(population, args.n_population);
                    survivor = tournament_selection(population,
                                                   args.n_population,
                                                   args.tournament_selections,
                                                   not_replace);
                    nextpopulation[i] = survivor;
                }
                break;

            default:
                printf("Strategy %d does not exist.\n", strategy);
                    exit(EXIT_FAILURE);
        }

        // Swap populations
        swap_populations(&population, &nextpopulation);

        // Find best individual
        evaluate(population, args.n_population, args.n_queens);
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

        // Look out for a solution
        if (best->scorer == 0 && !args.force_to_continue)
        {
            exit_code = 1;
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
                         exit_code, minutes};

    // Free memory
    for (i = 0; i < n_perms; i++)
        free(childs[i].genes.rows);
    free(childs);
    free(permutations);

    return results;
}
