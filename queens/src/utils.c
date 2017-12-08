/*****************************************************************************
 *               <N Queens Problem Solver - Genetic Algorithm>               *
 *             Copyright (C) <2017>   <Municoy, M., Salgado, D.>             *
 *                                                                           *
 *   Contact the authors at: martimunicoy@gmail.com                          *
 *                           danysalgado14@gmail.com                         *
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
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
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
    random = (arc4random_uniform(UINT16_MAX))/ ((float)(UINT16_MAX)) * max;
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

void swap(int * vector, int i, int j)
{
    /*
     Given a vector and two positions of the vector, i and j,
     a swap operation between the vector components is performed:
         vector[i] <--> vector[j]
    */
    int temp;
    temp = vector[i];
    vector[i] = vector[j];
    vector[j] = temp;
}

void permute(int ** permutations, int * vector, int start, int end, int *counter)
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
        {
            permutations[*counter][j] = vector[j];
        }
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
    }
}

void print_summary(Individual *population, Individual *best, int n_pop,
                   int n_gen)
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
    printf("| Generation:              %6d |\n", n_gen);
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
    printf("+---------------------------------+\n");
    printf("\n");
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
    printf("| Generations:             %6d |\n", ga_results.n_gen);
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
    printf("| Exit message:                   |\n");
    printf("\t\t      ");
    printf("|  %s  |\n", exit_message);
    printf("\t\t      ");
    printf("+---------------------------------+\n");
    printf("\n");

    free(exit_message);

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
        express_genes(*ga_results.best, n_queens);
}

void print_problem_description(struct Args args)
{
    printf("\n");
    printf("This algorithm will try to find a way to place %d", args.n_queens);
    printf(" chess Queens in a %dx%d board\nby", args.n_queens, args.n_queens);
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
    printf("\n\nThis program comes with ABSOLUTELY NO WARRANTY. This is free");
    printf(" software, and you\nare welcome to redistribute it under certain");
    printf(" conditions. See LICENSE.txt for\ndetails.");
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
            printf("| Mutation:             Heuristic |\n");
            break;

        case 2:
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

        case 3:
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
