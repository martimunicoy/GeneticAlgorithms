//#include "genetics.h"

Individual * strategy1(Individual * population, Individual * nextpopulation,
                       Individual * best,
                       RouletteCompartments * genetic_roulette,
                       Individual parent1, Individual parent2,
                       Individual child, Individual survivor, int id,
                       int n_deaths, struct Args args, FILE * file,
                       char * file_fitness)
{
    int i;
    int n_gen = 1;
    Individual * T;

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

        T = population;
        population = nextpopulation;
        nextpopulation = T;
        evaluate(population, args.n_population, args.n_queens);

        for (i = 0; i < args.n_population; i++)
            if (population[i].scorer < best->scorer)
                best = &population[i];

        if (args.summarize_freq != 0)
            if ((n_gen-1) % args.summarize_freq == 0)
                summarize(population, best, n_gen-1, args.n_population);

        n_gen++;

        if (best->scorer == 0 && !args.force_to_continue)
            return best;

        if (args.write_fitness && n_gen <= args.max_fitness_points)
            write_fitness(&file, file_fitness, population, args.n_population, n_gen);
    }

    return best;
}

Individual * strategy2(Individual * population, Individual * nextpopulation,
                       Individual * best,
                       RouletteCompartments * genetic_roulette,
                       Individual parent1, Individual parent2,
                       Individual child, Individual survivor, int id,
                       int n_deaths, struct Args args, FILE * file,
                       char * file_fitness)
{
    int i;
    int n_gen = 1;
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
                summarize(population, best, n_gen-1, args.n_population);

        n_gen++;

        if (best->scorer == 0 && !args.force_to_continue)
            return best;

        if (args.write_fitness && n_gen <= args.max_fitness_points)
            write_fitness(&file, file_fitness, population, args.n_population, n_gen);
    }

    return best;
}

Individual * strategy3(Individual * population, Individual * nextpopulation,
                       Individual * best,
                       RouletteCompartments * genetic_roulette,
                       Individual parent1, Individual parent2,
                       Individual child, Individual survivor, int id,
                       int n_deaths, struct Args args, FILE * file,
                       char * file_fitness)
{
    int i;
    int n_gen = 1;
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
                summarize(population, best, n_gen-1, args.n_population);

        n_gen++;

        if (best->scorer == 0 && !args.force_to_continue)
            return best;

        if (args.write_fitness && n_gen <= args.max_fitness_points)
            write_fitness(&file, file_fitness, population, args.n_population, n_gen);
    }

    return best;
}

Individual * genetic_algorithm(int strategy, Individual * population,
                               Individual * nextpopulation, Individual * best,
                               RouletteCompartments * genetic_roulette,
                               Individual parent1, Individual parent2,
                               Individual child, Individual survivor, int id,
                               int n_deaths, struct Args args, FILE * file,
                               char * file_fitness)
{
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
            return strategy2(population, nextpopulation, best, genetic_roulette,
                             parent1, parent2, child, survivor, id, n_deaths,
                             args, file, file_fitness);
        default:
            printf("Strategy %d does not exist.\n", strategy);
            exit(EXIT_FAILURE);
    }
}
