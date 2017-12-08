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
GAResults strategy1(Individual *population, Individual *nextpopulation,
                    Individual *best, RouletteCompartments *genetic_roulette,
                    Individual parent1, Individual parent2,
                    Individual child, Individual survivor, int id,
                    int n_deaths, struct Args args, FILE * file,
                    char * file_fitness)
{
    int i;
    int n_gen = 1;
    unsigned char exit_code = 0;
    Individual *T;

    while(n_gen <= args.n_generations || args.infinite_generations)
    {
        reset_selection(population, args.n_population);

        for (i = 0; i < n_deaths; i++)
        {
            parent1 = roulette_selection(population, genetic_roulette, args.n_population, args.n_queens, args.fract_weight, args.denom_power, fit);
            parent2 = roulette_selection(population, genetic_roulette, args.n_population, args.n_queens, args.fract_weight, args.denom_power, fit);
            child = heuristic_mutation(ordered_crossover(parent1, parent2, ++id, args.n_queens), args.n_queens, args.lambda, args.p_mutation);
            nextpopulation[i] = child;
        }

        reset_selection(population, args.n_population);
        for (i = n_deaths; i < args.n_population; i++)
        {
            survivor = roulette_selection(population, genetic_roulette, args.n_population, args.n_queens, args.fract_weight, args.denom_power, fit);
            nextpopulation[i] = survivor;
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
                print_summary(population, best, args.n_population, n_gen-1);

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
            write_fitness(&file, file_fitness, population, args.n_population, n_gen);
    }

    // Wrap the results and return them
    GAResults results = {best, population, args.n_population, n_gen-1,
                         exit_code};
    return results;
}

GAResults strategy2(Individual * population, Individual * nextpopulation,
                    Individual * best,
                    RouletteCompartments * genetic_roulette,
                    Individual parent1, Individual parent2,
                    Individual child, Individual survivor, int id,
                    int n_deaths, struct Args args, FILE * file,
                    char * file_fitness)
{
    int i;
    int n_gen = 1;
    unsigned char exit_code = 0;
    Individual * T;

    while(n_gen <= args.n_generations || args.infinite_generations)
    {
        for (i = 0; i < n_deaths; i++)
        {
            reset_selection(population, args.n_population);
            parent1 = tournament_selection(population, args.n_population, args.tournament_selections, replace);
            parent2 = tournament_selection(population, args.n_population, args.tournament_selections, replace);
            child = heuristic_mutation(ordered_crossover(parent1, parent2, ++id, args.n_queens), args.n_queens, args.lambda, args.p_mutation);
            nextpopulation[i] = child;
        }

        for (i = n_deaths; i < args.n_population; i++)
        {
            reset_selection(population, args.n_population);
            survivor = tournament_selection(population, args.n_population, args.tournament_selections, replace);
            nextpopulation[i] = survivor;
        }

        T = population;
        population = nextpopulation;
        nextpopulation = T;
        evaluate(population, args.n_population, args.n_queens);

        for (i = 0; i < args.n_population; i++)
            if (population[i].scorer < best->scorer)
                best = &population[i];

        if (args.summarize_freq != 0)
            if ((n_gen-1) % args.summarize_freq == 0)
                print_summary(population, best, args.n_population, n_gen-1);

        n_gen++;

        if (best->scorer == 0 && !args.force_to_continue)
        {
            exit_code = 1;
            break;
        }

        if (args.write_fitness && n_gen <= args.max_fitness_points)
            write_fitness(&file, file_fitness, population, args.n_population, n_gen);
    }

    GAResults results = {best, population, args.n_population, n_gen-1,
                         exit_code};

    return results;
}

GAResults strategy3(Individual * population, Individual * nextpopulation,
                    Individual * best,
                    RouletteCompartments * genetic_roulette,
                    Individual parent1, Individual parent2,
                    Individual child, Individual survivor, int id,
                    int n_deaths, struct Args args, FILE * file,
                    char * file_fitness)
{
    int i;
    int n_gen = 1;
    unsigned char exit_code = 0;
    Individual * T;

    while(n_gen <= args.n_generations || args.infinite_generations)
    {
        for (i = 0; i < n_deaths; i++)
        {
            parent1 = tournament_selection(population, args.n_population, args.tournament_selections, not_replace);
            parent2 = tournament_selection(population, args.n_population, args.tournament_selections, not_replace);
            child = heuristic_mutation(ordered_crossover(parent1, parent2, ++id, args.n_queens), args.n_queens, args.lambda, args.p_mutation);
            nextpopulation[i] = child;
        }

        for (i = n_deaths; i < args.n_population; i++)
        {
            survivor = tournament_selection(population, args.n_population, args.tournament_selections, not_replace);
            nextpopulation[i] = survivor;
        }

        T = population;
        population = nextpopulation;
        nextpopulation = T;
        evaluate(population, args.n_population, args.n_queens);

        for (i = 0; i < args.n_population; i++)
            if (population[i].scorer < best->scorer)
                best = &population[i];

        if (args.summarize_freq != 0)
            if ((n_gen-1) % args.summarize_freq == 0)
                print_summary(population, best, args.n_population, n_gen-1);

        n_gen++;

        if (best->scorer == 0 && !args.force_to_continue)
        {
            exit_code = 1;
            break;
        }
        if (args.write_fitness && n_gen <= args.max_fitness_points)
            write_fitness(&file, file_fitness, population, args.n_population, n_gen);
    }

    GAResults results = {best, population, args.n_population, n_gen-1,
                         exit_code};

    return results;
}

GAResults genetic_algorithm(int strategy, Individual * population,
                            Individual * nextpopulation, Individual * best,
                            RouletteCompartments * genetic_roulette,
                            Individual parent1, Individual parent2,
                            Individual child, Individual survivor, int id,
                            int n_deaths, struct Args args, FILE * file,
                            char * file_fitness)
{
    print_strategy_info(strategy);
    print_GA_starts();
    switch (strategy)
    {
        case 1:
            return strategy1(population, nextpopulation, best, genetic_roulette,
                             parent1, parent2, child, survivor, id, n_deaths,
                             args, file, file_fitness);
        case 2:
            return strategy2(population, nextpopulation, best, genetic_roulette,
                             parent1, parent2, child, survivor, id, n_deaths,
                             args, file, file_fitness);
        case 3:
            return strategy3(population, nextpopulation, best, genetic_roulette,
                             parent1, parent2, child, survivor, id, n_deaths,
                             args, file, file_fitness);
        default:
            printf("Strategy %d does not exist.\n", strategy);
            exit(EXIT_FAILURE);
    }
}
