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
#include "genetics.h"
#include "constants.h"
#include "arguments.h"
#include "utils.h"
#include "definitions.h"

//Function bodies
float random_number(float max)
{
    /*
    Returns a random float number between 0 and max
    */

    float random;
    random = (arc4random_uniform(UINT16_MAX)) / ((float)(UINT16_MAX)) * max;
    return random;
}

void shuffle(unsigned int * rows, int n_queens)
{
    /*
    Arrange the 'n_queens' elements of the array 'rows' in random order.
    Reference: https://stackoverflow.com/questions/6127503/shuffle-array-in-c
    size_t is a type guaranteed to hold any array index
    */

    int i, j;
    unsigned int tmp;

    for (i = n_queens-1; i >= 0; i--)
    {
        j = (unsigned int) random_number(n_queens);
        tmp = *(rows + i);
        *(rows + i) = *(rows + j);
        *(rows + j) = tmp;
    }
}

int sum_down(int n)
{
    /*
    Returns the value of the sum 1+2+3+...+n
    */
    return n*(n+1)/2;
}

unsigned int absolute(int value)
{
    /*
    Returns the absolute value of an integer
    */

    if(value < 0)
        return -value;
    return value;
}

int factorial(int m)
{
    /*
     Recursive function that return the value of m!
     (factorial of m).
    */
    if(m < 0){
        printf("\nFactorial of a negative number does not exist!\n");
        exit(0);
    }
    if(m >= 1) return m * factorial(m-1);
    else return 1;
}

void swap(unsigned int * vector, int i, int j)
{
    /*
     Given a vector and two positions of the vector, i and j,
     a swap operation between the vector components is performed:
         vector[i] <--> vector[j]
    */
    unsigned int temp;
    temp = vector[i];
    vector[i] = vector[j];
    vector[j] = temp;
}

void swap_populations(Individual **p1, Individual **p2)
{
    /*
     Swap two population pointers.
    */
    Individual *T;

    T = *p1;
    *p1 = *p2;
    *p2 = T;
}
/*
void permute(unsigned int ** permutations, unsigned int * vector, int start, int end,
             int *counter)
    int i, j;

    for (i = 0; i < lambda; i++)
    {

    }*/
void permute(unsigned int ** permutations, unsigned int * vector, int start, int end,
             int *counter)
{
    /*
     Given an input vector, start = 0, end = length of the vector, a matrix 'permutations'
     and a pointer to integer 'counter' (outside of the scope of this function), successive calls
     to this function and the swap function, recurssively fills the rows of the matrix 'permutations'
     with all the possible (end!) permutations of the input 'vector'.
    */

    int i, j;
    if (start == end)
    {
        for (j = 0; j < end; j++)
            permutations[*counter][j] = vector[j];
        ++(*counter);
        return;
    }
    else
    {
        for (i = start; i < end; i++)
        {
            swap(vector, start, i);
            permute(permutations, vector, start+1, end, counter);
            swap(vector, start, i);
        }
    }
    return;
}

bool compare(Individual *a, Individual*b, int n_queens)
{
    int i;
    for (i = 0; i < n_queens; i++)
        if (a->genes.rows[i] != b->genes.rows[i])
            return false;
    return true;
}

AnalysisResults population_analysis(Individual *population, int n_pop)
{
    /*
     @TODO
    */

    int i;
    float sum = 0, sum_of_squares = 0;
    AnalysisResults results;

    for (i = 0; i < n_pop; i++)
        sum += population[i].scorer;

    results.mean = sum / n_pop;

    for (i = 0; i < n_pop; i++)
        sum_of_squares += pow(population[i].scorer - results.mean, 2);

    results.st_deviation = sqrt(sum_of_squares/(n_pop-1));

    return results;
}

void exit_code_parser(unsigned char exit_code, char *exit_message)
{
    switch (exit_code)
    {
        case 0:
            strncpy(exit_message, "- Reached maximum generations", 30);
            break;
        case 1:
            strncpy(exit_message, "- Found at least one solution", 30);
            break;
        case 2:
            strncpy(exit_message, "- Reached maximum sieve value", 30);
            break;
    }
}

void print_summary(Individual *population, Individual *best, int n_pop,
                   int n_gen, int minutes)
{
    /*
     @TODO
    */

    AnalysisResults results = population_analysis(population, n_pop);

    printf("\n");
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("|         GENETIC SUMMARY         |\n");
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Generation:           %9d |\n", n_gen);
    printf("\t\t      ");
    printf("| Mean score:               ");
    printf("%3d.%d |\n", (int) results.mean,
                         (int) (results.mean * 10) -
                         ((int) results.mean) * 10);
    printf("\t\t      ");
    printf("| Standard deviation:       ");
    printf("%3d.%d |\n", (int) results.st_deviation,
                         (int) (results.st_deviation * 10) -
                         ((int) results.st_deviation) * 10);
    printf("\t\t      ");
    printf("| Best score:              %6d |\n", best->scorer);
    printf("\t\t      ");
    printf("| Running time (min):   %9d |\n", minutes);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\n");
}

void write_solution(GAResults ga_results, int n_queens, bool append)
{
    FILE *file;
    int i;
    char file_fitness[] = "solution.txt";

    if (append)
        file = fopen(file_fitness, "a");
    else
        file = fopen(file_fitness, "w");

    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    int row, col, index;

    for (row = n_queens; row > 0; row--)
    {
        fprintf(file, "%3d ", row);
        for(col = 0; col < n_queens; col++)
        {
            if (row == ga_results.best->genes.rows[col])
                fprintf(file, "X ");
            else
                fprintf(file, ". ");
        }
        fprintf(file, "\n");
    }
    fprintf(file, "   ");
    for (col = 0; col < n_queens; col++)
    {
        index = col;
        while(index > 25) index -= 26;
        fprintf(file, " %c", ALPHABET[index]);
    }
    fprintf(file, "\n");
    if (n_queens > 26)
    {
        fprintf(file, "   ");
        for (col = 0; col < n_queens; col++)
            fprintf(file, " %d", (int) col/26+1);
        fprintf(file, "\n");
    }
    fprintf(file, "\n");

    fprintf(file, "========================================================");
    fprintf(file, "========================\n");
    fprintf(file, "\n - Solution:\n");
    fprintf(file, "\n");
    fprintf(file, " (%4d, ", ga_results.best->genes.rows[0]);
    for (i = 1; i < n_queens-1; i++)
    {
        if (i % 13 == 0)
            fprintf(file, "\n  ");
        fprintf(file, "%4d, ", ga_results.best->genes.rows[i]);
    }
    fprintf(file, "%4d)\n", ga_results.best->genes.rows[n_queens-1]);
    fprintf(file, "\n");
    fprintf(file, "========================================================");
    fprintf(file, "========================\n");
    fprintf(file, "\n");

    fclose(file);

}

void print_results_all(GAResults ga_results, int n_queens)
{
    /*
     @TODO
    */

    AnalysisResults results = population_analysis(ga_results.population,
                                                  ga_results.n_pop);
    char *exit_message = (char *) malloc(sizeof(char) * 30);
    exit_code_parser(ga_results.exit_code, exit_message);

    printf("\n");
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("|      FINAL GENETIC SUMMARY      |\n");
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Generations:          %9d |\n", ga_results.n_gen);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Exit message:                   |\n");
    printf("\t\t      ");
    printf("|  %s  |\n", exit_message);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\n");

    free(exit_message);

    printf("\n");
    printf("+-----------------------------------------------------------");
    printf("-------------------+\n");
    printf("|                                    RESULTS                ");
    printf("                   |\n");
    printf("+-----------------------------------------------------------");
    printf("-------------------+\n");
    printf("\n");
    printf(" The solutions will be expressed in file \'solution.txt\'\n");

}

void print_results(GAResults ga_results, int n_queens)
{
    /*
     @TODO
    */

    AnalysisResults results = population_analysis(ga_results.population,
                                                  ga_results.n_pop);
    char *exit_message = (char *) malloc(sizeof(char) * 30);
    exit_code_parser(ga_results.exit_code, exit_message);

    printf("\n");
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("|      FINAL GENETIC SUMMARY      |\n");
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Generations:          %9d |\n", ga_results.n_gen);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Mean score:               ");
    printf("%3d.%d |\n", (int) results.mean,
                         (int) (results.mean * 10) -
                         ((int) results.mean) * 10);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Standard deviation:       ");
    printf("%3d.%d |\n", (int) results.st_deviation,
                         (int) (results.st_deviation * 10) -
                         ((int) results.st_deviation) * 10);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Best score:              %6d |\n", ga_results.best->scorer);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Running time (min):   %9d |\n", ga_results.minutes);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Exit message:                   |\n");
    printf("\t\t      ");
    printf("|  %s  |\n", exit_message);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\n");

    free(exit_message);

    printf("\n");
    printf("+-----------------------------------------------------------");
    printf("-------------------+\n");
    printf("|                                    RESULTS                ");
    printf("                   |\n");
    printf("+-----------------------------------------------------------");
    printf("-------------------+\n");
    printf("\n");

    if(ga_results.best->scorer != 0)
    {
        printf("\nNo optimal individual found.\n");
        printf("\n");
    }
    else
    {
        if (n_queens <= 38)
            express_genes(*ga_results.best, n_queens);
        else
        {
            printf(" Problem size is too big to be expressed in terminal. It");
            printf(" will be written in\n file \'solution.txt\'\n");
            write_solution(ga_results, n_queens, false);
        }
        int i;
        printf("\n");
        printf("========================================================");
        printf("========================\n");
        printf("\n - Solution:\n");
        printf("\n");
        printf(" (%4d, ", ga_results.best->genes.rows[0]);
        for (i = 1; i < n_queens-1; i++)
        {
            if (i % 13 == 0)
                printf("\n  ");
            printf("%4d, ", ga_results.best->genes.rows[i]);
        }
        printf("%4d)\n", ga_results.best->genes.rows[n_queens-1]);
        printf("\n");
        printf("========================================================");
        printf("========================\n");
        printf("\n");
    }
}

void print_problem_description(struct Args args)
{
    printf("+---------------------------------------------------------------");
    printf("---------------+\n");
    printf("|                             PROBLEM DESCRIPTION               ");
    printf("               |\n");
    printf("+---------------------------------------------------------------");
    printf("---------------+\n");

    printf("\n");
    printf("This algorithm will try to find a way to place %d", args.n_queens);
    printf(" chess Queens in a %dx%d\nboard by", args.n_queens, args.n_queens);
    printf(" applying a Genetic Algorithm\n");
    printf("\n");
}

void translate_bool(bool bool_to_translate, char *bool_string)
{
    if (bool_to_translate)
        strncpy(bool_string, " True", 6);
    else
        strncpy(bool_string, "False", 6);
}

void print_program_name()
{
    printf("+---------------------------------------------------------------");
    printf("---------------+\n");
    printf("|                           N QUEENS PROBLEM SOLVER             ");
    printf("               |\n");
    printf("+---------------------------------------------------------------");
    printf("---------------+\n");
}

void print_license_header()
{
    printf("\n");
    printf("                 <N Queens Problem Solver - Genetic Algorithm>\n");
    printf("               Copyright (C) <2017>   <Municoy, M., Salgado, D.>");
    printf("\n\n     Contact the authors at: mail@martimunicoy.com\n        ");
    printf("                     daniel.salgado@e-campus.uab.cat\n\n     Thi");
    printf("s program is free software: you can redistribute it and/or modif");
    printf("y\n     it under the terms of the GNU General Public License as ");
    printf("published by\n     the Free Software Foundation, either version ");
    printf("3 of the License, or\n     (at your option) any later version.\n");
    printf("\n     This program is distributed in the hope that it will be u");
    printf("seful,\n     but WITHOUT ANY WARRANTY; without even the implied ");
    printf("warranty of\n     MERCHANTABILITY or FITNESS FOR A PARTICULAR PU");
    printf("RPOSE.  See the\n     GNU General Public License for more detail");
    printf("s.\n\n");
}

void print_GA_constants_all(struct Args args)
{
    printf("\n");
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("|   GENETIC ALGORITHM CONSTANTS   |\n");
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Population size:      %9d |\n", args.n_population);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Generations:          %9d |\n", args.n_generations);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Death ratio:              %.3f |\n", args.death_ratio);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Mutation probability:     %.3f |\n", args.p_mutation);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Lambda:                      %2d |\n", args.lambda);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Tournament selections:       %2d |", args.tournament_selections);
    printf("\n");
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Fraction weight:           ");
    printf("%2d.%d |\n", (int) args.fract_weight,
                         (int) (args.fract_weight * 10) -
                         ((int) args.fract_weight) * 10);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Denominator power:         ");
    printf("%2d.%d |\n", (int) args.denom_power,
                         (int) (args.denom_power * 10) -
                         ((int) args.denom_power) * 10);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Sieve:                %9d |\n", args.sieve);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\n");

}

void print_GA_constants(struct Args args)
{
    printf("\n");
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("|   GENETIC ALGORITHM CONSTANTS   |\n");
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Population size:      %9d |\n", args.n_population);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Generations:          %9d |\n", args.n_generations);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Death ratio:              %.3f |\n", args.death_ratio);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Mutation probability:     %.3f |\n", args.p_mutation);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Lambda:                      %2d |\n", args.lambda);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Tournament selections:       %2d |", args.tournament_selections);
    printf("\n");
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Fraction weight:           ");
    printf("%2d.%d |\n", (int) args.fract_weight,
                         (int) (args.fract_weight * 10) -
                         ((int) args.fract_weight) * 10);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Denominator power:         ");
    printf("%2d.%d |\n", (int) args.denom_power,
                         (int) (args.denom_power * 10) -
                         ((int) args.denom_power) * 10);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\n");

}

void print_configuration(struct Args args)
{
    char *bool_string1 = (char *) malloc(sizeof(char) * 6);
    char *bool_string2 = (char *) malloc(sizeof(char) * 6);
    char *bool_string3 = (char *) malloc(sizeof(char) * 6);

    translate_bool(args.force_to_continue, bool_string1);
    translate_bool(args.infinite_generations, bool_string2);
    translate_bool(args.write_fitness, bool_string3);

    printf("\n");
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| GENETIC ALGORITHM CONFIGURATION |\n");
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Force to continue:        %s |\n", bool_string1);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Infinite generations:     %s |\n", bool_string2);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Write fitness:            %s |\n", bool_string1);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Summary frequency:    %9d |\n", args.summarize_freq);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Maximum fitness points:  %6d |\n", args.max_fitness_points);
    printf("\t\t      ");
    printf("+---------------------------------+\n");

    printf("\n");

    free(bool_string1);
    free(bool_string2);
    free(bool_string3);

}

void print_strategy_info(int strategy)
{
    printf("\n");
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("|      STRATEGY  INFORMATION      |\n");
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");
    printf("| Strategy number:             %2d |\n", strategy);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\t\t      ");

    switch (strategy)
    {
        case 1:
            printf("| Selection:             Roulette |\n");
            printf("\t\t      ");
            printf("+---------------------------------+\n");
            printf("\t\t      ");
            printf("| Crossover:              Ordered |\n");
            printf("\t\t      ");
            printf("+---------------------------------+\n");
            printf("\t\t      ");
            printf("| Mutation:              Swapping |\n");
            break;

        case 2:
            printf("| Selection:             Roulette |\n");
            printf("\t\t      ");
            printf("+---------------------------------+\n");
            printf("\t\t      ");
            printf("| Crossover:              Ordered |\n");
            printf("\t\t      ");
            printf("+---------------------------------+\n");
            printf("\t\t      ");
            printf("| Mutation:             Heuristic |\n");
            break;

        case 3:
            printf("| Selection:                      |\n");
            printf("\t\t      ");
            printf("|     Tournament with replacement |\n");
            printf("\t\t      ");
            printf("+---------------------------------+\n");
            printf("\t\t      ");
            printf("| Crossover:              Ordered |\n");
            printf("\t\t      ");
            printf("+---------------------------------+\n");
            printf("\t\t      ");
            printf("| Mutation:             Heuristic |\n");
            break;

        case 4:
            printf("| Selection:                      |\n");
            printf("\t\t      ");
            printf("|  Tournament without replacement |\n");
            printf("\t\t      ");
            printf("+---------------------------------+\n");
            printf("\t\t      ");
            printf("| Crossover:              Ordered |\n");
            printf("\t\t      ");
            printf("+---------------------------------+\n");
            printf("\t\t      ");
            printf("| Mutation:             Heuristic |\n");
            break;
    }
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\n");
}

void print_GA_starts()
{
    printf("\n");
    printf("+---------------------------------------------------------------");
    printf("---------------+\n");
    printf("|                            GENETIC ALGORITHM RUN              ");
    printf("               |\n");
    printf("+---------------------------------------------------------------");
    printf("---------------+\n");
}

void print_GA_completed()
{
    printf("\n");
    printf("+---------------------------------------------------------------");
    printf("---------------+\n");
    printf("|                         GENETIC ALGORITHM COMPLETED           ");
    printf("               |\n");
    printf("+---------------------------------------------------------------");
    printf("---------------+\n");
}

void print_GA_input()
{
    printf("\n");
    printf("+---------------------------------------------------------------");
    printf("---------------+\n");
    printf("|                         GENETIC ALGORITHM INPUT DATA          ");
    printf("               |\n");
    printf("+---------------------------------------------------------------");
    printf("---------------+\n");
}
