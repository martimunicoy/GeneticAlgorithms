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
#include "queens_GA.h"
#include "constants.h"
#include "genetics.h"
#include "arguments.h"
#include "utils.h"
#include "strategies.h"
#include "definitions.h"

// Function bodies
GAResults genetic_algorithm(Individual *population, Individual *nextpopulation,
                            Individual *best,
                            RouletteCompartments *genetic_roulette,
                            Individual *parent1, Individual *parent2,
                            Individual child, Individual *survivor, int id,
                            int n_deaths, struct Args args, FILE *fitness_file,
                            FILE *genes_file)
{
    // Print GA information
    print_strategy_info(args.strategy);
    print_GA_starts();

    // Initiate variables
    int i, seconds;
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

    // Start counter
    gettimeofday(&start, NULL);

    // Start GA loop
    while(n_gen <= args.n_generations || args.infinite_generations)
    {
        switch (args.strategy)
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
                    nextpopulation[i] = *survivor;
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
                                              args.n_queens);

                    heuristic_mutation(&child, permutations,
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
                    nextpopulation[i] = *survivor;
                }
                break;

            case 3:
                // Mutation and crossover
                for (i = 0; i < n_deaths; i++)
                {
                    parent1 = tournament_selection(population,
                                                   args.n_population,
                                                   args.tournament_selections,
                                                   replace);
                    parent2 = tournament_selection(population,
                                                   args.n_population,
                                                   args.tournament_selections,
                                                   replace);
                    child = ordered_crossover(parent1, parent2, ++id,
                                              args.n_queens);

                    heuristic_mutation(&child, permutations,
                                       args.n_queens, args.lambda,
                                       n_perms, args.p_mutation);

                    nextpopulation[i] = child;
                }

                // Selection
                reset_selection(population, args.n_population);
                for (i = n_deaths; i < args.n_population; i++)
                {
                    survivor = tournament_selection(population,
                                                   args.n_population,
                                                   args.tournament_selections,
                                                   replace);
                    nextpopulation[i] = *survivor;
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
                                              args.n_queens);

                    heuristic_mutation(&child, permutations,
                                       args.n_queens, args.lambda,
                                       n_perms, args.p_mutation);

                    nextpopulation[i] = child;
                }

                // Selection
                for (i = n_deaths; i < args.n_population; i++)
                {
                    survivor = tournament_selection(population,
                                                   args.n_population,
                                                   args.tournament_selections,
                                                   not_replace);
                    nextpopulation[i] = *survivor;
                }
                break;

            case 5:
                // Mutation and crossover
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
                                              args.n_queens);

                    heuristic_mutation(&child, permutations,
                                       args.n_queens, args.lambda,
                                       n_perms, args.p_mutation);

                    nextpopulation[i] = child;

                // Selection
                for (i = n_deaths; i < args.n_population; i++)
                {
                    survivor = tournament_selection(population,
                                                   args.n_population,
                                                   args.tournament_selections,
                                                   not_replace);
                    nextpopulation[i] = *survivor;
                }
                break;

                }

            case 6:
                // Mutation and crossover
                for (i = 0; i < n_deaths; i++)
                {
                    parent1 = tournament_selection(population,
                                                   args.n_population,
                                                   args.tournament_selections,
                                                   replace);
                    parent2 = tournament_selection(population,
                                                   args.n_population,
                                                   args.tournament_selections,
                                                   replace);
                    child = ordered_crossover(parent1, parent2, ++id,
                                              args.n_queens);

                    swapping_mutation(&child, args.n_queens, args.p_mutation);

                    nextpopulation[i] = child;
                }

                // Selection
                reset_selection(population, args.n_population);
                for (i = n_deaths; i < args.n_population; i++)
                {
                    survivor = tournament_selection(population,
                                                   args.n_population,
                                                   args.tournament_selections,
                                                   replace);
                    nextpopulation[i] = *survivor;
                }
                break;

            default:
                printf("Strategy %d does not exist.\n", args.strategy);
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
                seconds = (int) (end.tv_sec  - start.tv_sec);
                print_summary(population, best, args.n_population, n_gen-1,
                              seconds);
            }

        // Sum up 1 generation
        n_gen++;

        // Write fitness
        if (args.write_fitness && n_gen <= args.max_fitness_points)
            write_fitness(&fitness_file, args.fitness_dir, population,
                          args.n_population, n_gen);

        // Write genes
        if (args.write_genes && n_gen <= args.max_genes_points)
            write_population_genes(&genes_file, args.genes_dir, population,
                                   args.n_population, args.n_queens);

        // Look out for a solution
        if (best->scorer == 0 && !args.force_to_continue)
        {
            exit_code = 1;
            break;
        }

    // End of While loop
    }

    // Stop counter
    gettimeofday(&end, NULL);

    // Calculate GA running time in seconds
    seconds = (int) (end.tv_sec  - start.tv_sec);

    // Wrap the results and return them
    GAResults results = {best, population, args.n_population, n_gen-1,
                         exit_code, seconds};

    // Free memory
    free(permutations);

    return results;
}
