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

#include "queens_GA.h"
#include "constants.h"
#include "arguments.h"
#include "definitions.h"

// Function bodies
bool starts_with(const char *string, const char *prefix){
    return strncmp(string, prefix, strlen(prefix)) == 0;
}

struct Args args_initializer()
{
    struct Args arguments = {N_QUEENS, N_POPULATION, N_GENERATIONS, DEATH_RATIO,
                             P_MUTATION, LAMBDA, FORCE_TO_CONTINUE,
                             INFINITE_GENERATIONS, WRITE_FITNESS,
                             MAX_FITNESS_POINTS, SUMMARIZE_FREQ,
                             TOURNAMENT_SELECTIONS, FRACT_WEIGTH, DENOM_POWER,
                             STRATEGY, SIEVE, WRITE_GENES, MAX_GENES_POINTS};

    strcpy(arguments.fitness_dir, FITNESS_DIR);
    strcpy(arguments.genes_dir, GENES_DIR);

    return arguments;
}

struct Args check_arguments(struct Args arguments)
{
    printf("\n  - Checking arguments...\n");
    if (arguments.n_queens < 4 | arguments.n_queens > 1000)
    {
        printf("    \'n_queens\' out of range, using default value (%d)\n", N_QUEENS);
        arguments.n_queens = N_QUEENS;
    }
    if (arguments.n_population < 10 | arguments.n_population > 999999999)
    {
        printf("    \'n_population\' out of range, using default value (%d)\n", N_POPULATION);
        arguments.n_population = N_POPULATION;
    }
    if (arguments.n_generations < 1 | arguments.n_generations > 999999999)
    {
        printf("    \'n_generations\' out of range, using default value (%d)\n", N_GENERATIONS);
        arguments.n_generations = N_GENERATIONS;
    }
    if (arguments.death_ratio < 0 | arguments.death_ratio > 0.5)
    {
        printf("    \'n_deaths\' out of range, using default value (%f)\n", DEATH_RATIO);
        arguments.death_ratio = DEATH_RATIO;
    }
    if (arguments.p_mutation < 0 | arguments.p_mutation > 1)
    {
        printf("    \'p_mutation\' out of range, using default value (%f)\n", P_MUTATION);
        arguments.p_mutation = P_MUTATION;
    }
    if (arguments.lambda < 0 | arguments.lambda > 5)
    {
        printf("    \'lambda\' out of range, using default value (%d)\n", LAMBDA);
        arguments.lambda = LAMBDA;
    }
    if (arguments.max_fitness_points < 0 | arguments.max_fitness_points > 999999)
    {
        printf("    \'max_fitness_points\' out of range, using default value (%d)\n", MAX_FITNESS_POINTS);
        arguments.max_fitness_points = MAX_FITNESS_POINTS;
    }
    if (arguments.summarize_freq < 0 | arguments.summarize_freq > 999999999)
    {
        printf("    \'summarize_freq\' out of range, using default value (%d)\n", SUMMARIZE_FREQ);
        arguments.summarize_freq = SUMMARIZE_FREQ;
    }
    if (arguments.tournament_selections < 1 | arguments.tournament_selections > arguments.n_population)
    {
        printf("    \'tournament_selections\' out of range, using default value (%d)\n", TOURNAMENT_SELECTIONS);
        arguments.tournament_selections = TOURNAMENT_SELECTIONS;
    }
    if (arguments.fract_weight < 0 | arguments.fract_weight > 1000)
    {
        printf("    \'fract_weight\' out of range, using default value (%f)\n", FRACT_WEIGTH);
        arguments.fract_weight = FRACT_WEIGTH;
    }
    if (arguments.denom_power < 0 | arguments.denom_power > 15)
    {
        printf("    \'denom_power\' out of range, using default value (%f)\n", DENOM_POWER);
        arguments.denom_power = DENOM_POWER;
    }
    if (arguments.strategy < 1 | arguments.strategy > 4)
    {
        printf("    \'strategy\' out of range, using default value (%d)\n", STRATEGY);
        arguments.strategy = STRATEGY;
    }
    if (arguments.sieve < 100 | arguments.sieve > 999999999)
    {
        printf("    \'sieve\' out of range, using default value (%d)\n", SIEVE);
        arguments.sieve = SIEVE;
    }
    if (arguments.max_genes_points < 0 | arguments.max_genes_points > 999999)
    {
        printf("    \'max_genes_points\' out of range, using default value (%d)\n", MAX_GENES_POINTS);
        arguments.max_genes_points = MAX_GENES_POINTS;
    }

    printf("    Done.\n");

    return arguments;
}

bool atob(char *subline)
{
    if (strncmp(subline, "true", 4) == 0)
        return true;
    else if (strncmp(subline, "t", 1) == 0)
        return true;
    else if (strncmp(subline, "1", 1) == 0)
        return true;
    else if (strncmp(subline, "false", 4) == 0)
        return false;
    else if (strncmp(subline, "f", 1) == 0)
        return false;
    else if (strncmp(subline, "0", 1) == 0)
        return false;
    else
    {
        printf("    Error while parsing %s from the input file.\n", subline);
        exit(EXIT_FAILURE);
    }
}

char *string_parser(char *subline)
{
    subline[strlen(subline)-1] = '\0';
    return subline;
}

struct Args line_parser(char * subline1, char * subline2, struct Args arguments)
{
    if (starts_with(subline1, "N_QUEENS"))
        arguments.n_queens = atoi(subline2);
    else if (starts_with(subline1, "N_POPULATION"))
        arguments.n_population = atoi(subline2);
    else if (starts_with(subline1, "N_GENERATIONS"))
        arguments.n_generations = atoi(subline2);
    else if (starts_with(subline1, "DEATH_RATIO"))
        arguments.death_ratio = atof(subline2);
    else if (starts_with(subline1, "P_MUTATION"))
        arguments.p_mutation = atof(subline2);
    else if (starts_with(subline1, "LAMBDA"))
        arguments.lambda = atoi(subline2);
    else if (starts_with(subline1, "FORCE_TO_CONTINUE"))
        arguments.force_to_continue = atob(subline2);
    else if (starts_with(subline1, "INFINITE_GENERATIONS"))
        arguments.infinite_generations = atob(subline2);
    else if (starts_with(subline1, "WRITE_FITNESS"))
        arguments.write_fitness = atob(subline2);
    else if (starts_with(subline1, "SUMMARIZE_FREQ"))
        arguments.summarize_freq = atoi(subline2);
    else if (starts_with(subline1, "MAX_FITNESS_POINTS"))
        arguments.max_fitness_points = atoi(subline2);
    else if (starts_with(subline1, "TOURNAMENT_SELECTIONS"))
        arguments.tournament_selections = atoi(subline2);
    else if (starts_with(subline1, "FRACT_WEIGTH"))
        arguments.fract_weight = atof(subline2);
    else if (starts_with(subline1, "DENOM_POWER"))
        arguments.denom_power = atof(subline2);
    else if (starts_with(subline1, "STRATEGY"))
        arguments.strategy = atoi(subline2);
    else if (starts_with(subline1, "SIEVE"))
        arguments.sieve = atoi(subline2);
    else if (starts_with(subline1, "WRITE_GENES"))
        arguments.write_genes = atob(subline2);
    else if (starts_with(subline1, "MAX_GENES_POINTS"))
        arguments.max_genes_points = atoi(subline2);
    else if (starts_with(subline1, "FITNESS_DIR"))
        strcpy(arguments.fitness_dir, string_parser(subline2));
    else if (starts_with(subline1, "GENES_DIR"))
        strcpy(arguments.genes_dir, string_parser(subline2));

    return arguments;
}

struct Args args_from_file(struct Args arguments, char file_dir[50])
{
    FILE * f;
    char * line = NULL;
    char * subline1, * subline2;
    size_t len = 0;
    ssize_t read;

    f = fopen(file_dir, "r");

    if (f == NULL)
    {
        printf("    Error while openening arguments input file %s\n", file_dir);
        exit(EXIT_FAILURE);
    }
    printf("\n  - Reading information from file \'%s\'...\n", file_dir);

    while ((read = getline(&line, &len, f)) != -1)
    {
        subline1 = strtok(line, " ");
        subline2 = strtok(NULL, " ");
        if (subline2 != NULL)
            arguments = line_parser(subline1, subline2, arguments);
        else
        {
            printf("    Wrong input line: %s\n", line);
            exit(EXIT_FAILURE);
        }
    }

    fclose(f);
    if (line)
        free(line);

    printf("    Done.\n");

    return arguments;
}

struct Args args_parser(int argc, char *argv[])
{
    int i, j;
    char file_dir[50];
    struct Args arguments = args_initializer();

    printf("================================================================");
    printf("================\n");
    printf("\n Collecting input information...\n");

    for (i = 1; i < argc; i++)
    {
        if (starts_with(*(argv + i), "-f"))
            if (i + 2 <= argc)
            {
                strcpy(file_dir, *(argv + i + 1));
                arguments = args_from_file(arguments, file_dir);
            }
    }

    printf("\n  - Reading command-line flags...\n");

    for (i = 1; i < argc; i++){
        for (j = 0; j < ARGS_NUM; j++)
        {
            if (starts_with(*(argv + i), ARGS[j]))
            {
                if (j == 6) arguments.force_to_continue = true;
                else if (j == 7) arguments.infinite_generations = true;
                else if (j == 8) arguments.write_fitness = true;
                else if (j == 16) arguments.write_genes = true;
                else if (i + 2 <= argc)
                {
                    if (j == 0) arguments.n_queens = atoi(*(argv + i + 1));
                    else if (j == 1)
                        arguments.n_population = atoi(*(argv + i + 1));
                    else if (j == 2)
                        arguments.n_generations = atoi(*(argv + i + 1));
                    else if (j == 3)
                        arguments.death_ratio = atof(*(argv + i + 1));
                    else if (j == 4)
                        arguments.p_mutation = atof(*(argv + i + 1));
                    else if (j == 5)
                        arguments.lambda = atoi(*(argv + i + 1));
                    else if (j == 9)
                        arguments.max_fitness_points = atoi(*(argv + i + 1));
                    else if (j == 10)
                        arguments.summarize_freq = atoi(*(argv + i + 1));
                    else if (j == 11)
                        arguments.tournament_selections =
                                                         atoi(*(argv + i + 1));
                    else if (j == 12)
                        arguments.fract_weight = atof(*(argv + i + 1));
                    else if (j == 13)
                        arguments.denom_power = atof(*(argv + i + 1));
                    else if (j == 14)
                        arguments.strategy = atoi(*(argv + i + 1));
                    else if (j == 15)
                        arguments.sieve = atoi(*(argv + i + 1));
                    else if (j == 17)
                        arguments.max_genes_points = atoi(*(argv + i + 1));
                    else if (j == 18)
                        strcpy(arguments.fitness_dir, *(argv + i + 1));
                    else if (j == 19)
                        strcpy(arguments.genes_dir, *(argv + i + 1));
                }
                else
                    printf("    Wrong command (%s), using default values.\n", *(argv + i));
                break;
            }
        }
    }

    printf("    Done.\n");

    arguments = check_arguments(arguments);

    printf("\n Input data collected.\n");
    printf("\n==============================================================");
    printf("==================\n");
    printf("\n\n");


    return arguments;
}
