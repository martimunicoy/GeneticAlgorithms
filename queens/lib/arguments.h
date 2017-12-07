#include <string.h>

#define ARGS_NUM 14

// Constants for default parameters
// List of arguments
const char ARGS[ARGS_NUM][3] = {"-q", "-p", "-g", "-d", "-m", "-l", "-c",
                                "-i", "-r", "-s", "-t", "-w", "-e", "-f"};
// Number of queens -q
const int N_QUEENS = 8;
// Population size -p
const int N_POPULATION = 10;
// Number of generations -g
const int N_GENERATIONS = 500;
// Death ratio per generation -d
const float DEATH_RATIO = 0.3;
// Probability of mutation -m
const float P_MUTATION = 0.2;
// Number of genes to mutate -l
const int LAMBDA = 3;
// Force the algorithm to continue after finding a solution -c
const bool FORCE_TO_CONTINUE = false;
// Infinite number of generations -i
const bool INFINITE_GENERATIONS = false;
// Write fitness data to file -r
const bool WRITE_FITNESS = false;
// Frequency to summarize -s
const int SUMMARIZE_FREQ = 50;
// Number of selections in the tournament_selection function -t
const int TOURNAMENT_SELECTIONS = 3;
// The higher, the more exploratory -w
const float FRACT_WEIGTH = 0.1;
// The higher, the more exploitatory -e
const float DENOM_POWER = 2;


struct Args{
    int n_queens;
    int n_population;
    int n_generations;
    float death_ratio;
    float p_mutation;
    int lambda;
    bool force_to_continue;
    bool infinite_generations;
    bool write_fitness;
    int summarize_freq;
    int tournament_selections;
    float fract_weight;
    float denom_power;
};

bool starts_with(const char *string, const char *prefix){
    return strncmp(string, prefix, strlen(prefix)) == 0;
}

struct Args args_initializer()
{
    struct Args arguments = {N_QUEENS, N_POPULATION, N_GENERATIONS, DEATH_RATIO,
                             P_MUTATION, LAMBDA, FORCE_TO_CONTINUE,
                             INFINITE_GENERATIONS, SUMMARIZE_FREQ,
                             TOURNAMENT_SELECTIONS, FRACT_WEIGTH, DENOM_POWER};

    return arguments;
}

struct Args check_arguments(struct Args arguments)
{
    if (arguments.n_queens < 4 | arguments.n_queens > 1000)
    {
        printf("\'n_queens\' out of range, using default value (%d)\n", N_QUEENS);
        arguments.n_queens = N_QUEENS;
    }
    if (arguments.n_population < 10 | arguments.n_population > 999999999)
    {
        printf("\'n_population\' out of range, using default value (%d)\n", N_POPULATION);
        arguments.n_population = N_POPULATION;
    }
    if (arguments.n_generations < 1 | arguments.n_generations > 999999999)
    {
        printf("\'n_generations\' out of range, using default value (%d)\n", N_GENERATIONS);
        arguments.n_generations = N_GENERATIONS;
    }
    if (arguments.death_ratio < 0 | arguments.death_ratio > 0.5)
    {
        printf("\'n_deaths\' out of range, using default value (%f)\n", DEATH_RATIO);
        arguments.death_ratio = DEATH_RATIO;
    }
    if (arguments.p_mutation < 0 | arguments.p_mutation > 1)
    {
        printf("\'p_mutation\' out of range, using default value (%f)\n", P_MUTATION);
        arguments.p_mutation = P_MUTATION;
    }
    if (arguments.lambda < 0 | arguments.lambda > 5)
    {
        printf("\'lambda\' out of range, using default value (%d)\n", LAMBDA);
        arguments.lambda = LAMBDA;
    }
    if (arguments.summarize_freq < 0 | arguments.summarize_freq > 999999999)
    {
        printf("\'p_mutation\' out of range, using default value (%d)\n", SUMMARIZE_FREQ);
        arguments.summarize_freq = SUMMARIZE_FREQ;
    }
    if (arguments.tournament_selections < 1 | arguments.tournament_selections > arguments.n_population)
    {
        printf("\'tournament_selections\' out of range, using default value (%d)\n", TOURNAMENT_SELECTIONS);
        arguments.tournament_selections = TOURNAMENT_SELECTIONS;
    }
    if (arguments.fract_weight < 0 | arguments.fract_weight > 1000)
    {
        printf("\'fract_weight\' out of range, using default value (%f)\n", FRACT_WEIGTH);
        arguments.fract_weight = FRACT_WEIGTH;
    }
    if (arguments.denom_power < 0 | arguments.denom_power > 10)
    {
        printf("\'denom_power\' out of range, using default value (%f)\n", DENOM_POWER);
        arguments.denom_power = DENOM_POWER;
    }

    return arguments;
}

bool atob(char * subline)
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
        printf("Error while parsing %s from the input file.\n", subline);
        exit(EXIT_FAILURE);
    }
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
    else if (starts_with(subline1, "TOURNAMENT_SELECTIONS"))
        arguments.tournament_selections = atoi(subline2);
    else if (starts_with(subline1, "FRACT_WEIGTH"))
        arguments.fract_weight = atof(subline2);
    else if (starts_with(subline1, "DENOM_POWER"))
        arguments.denom_power = atof(subline2);

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
        printf("Error while openening arguments input file %s\n", file_dir);
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, f)) != -1)
    {
        subline1 = strtok(line, " ");
        subline2 = strtok(NULL, " ");
        if (subline2 != NULL)
            arguments = line_parser(subline1, subline2, arguments);
        else
        {
            printf("Wrong input line: %s\n", line);
            exit(EXIT_FAILURE);
        }
    }

    fclose(f);
    if (line)
        free(line);

    return arguments;
}

struct Args args_parser(int argc, char *argv[])
{
    int i, j;
    char file_dir[50];
    struct Args arguments = args_initializer();

    for (i = 1; i < argc; i++)
    {
        if (starts_with(*(argv + i), "-f"))
            if (i + 2 <= argc){
                strcpy(file_dir, *(argv + i + 1));
                arguments = args_from_file(arguments, file_dir);
            }
    }

    for (i = 1; i < argc; i++){
        for (j = 0; j < ARGS_NUM; j++)
        {
            if (starts_with(*(argv + i), ARGS[j]))
            {
                if (j == 6) arguments.force_to_continue = true;
                else if (j == 7) arguments.infinite_generations = true;
                else if (j == 8) arguments.write_fitness = true;
                else if (i + 2 <= argc)
                {
                    if (j == 0) arguments.n_queens = atoi(*(argv + i + 1));
                    else if (j == 1) arguments.n_population = atoi(*(argv + i + 1));
                    else if (j == 2) arguments.n_generations = atoi(*(argv + i + 1));
                    else if (j == 3) arguments.death_ratio = atof(*(argv + i + 1));
                    else if (j == 4) arguments.p_mutation = atof(*(argv + i + 1));
                    else if (j == 5) arguments.lambda = atoi(*(argv + i + 1));
                    else if (j == 9) arguments.summarize_freq = atoi(*(argv + i + 1));
                    else if (j == 10) arguments.tournament_selections = atoi(*(argv + i + 1));
                    else if (j == 11) arguments.fract_weight = atof(*(argv + i + 1));
                    else if (j == 12) arguments.denom_power = atof(*(argv + i + 1));
                }
                else
                    printf("Wrong command (%s), using default values.\n", *(argv + i));
                break;
            }
        }
    }

    arguments = check_arguments(arguments);

    return arguments;
}
