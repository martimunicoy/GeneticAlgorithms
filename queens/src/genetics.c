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
#include "definitions.h"

// Function bodies
Genes initiate_genes(int n_queens)
{
     /*
     Returns a Genes struct variable after reserving memory for it.
    */

    Genes genes;
    genes.rows = (unsigned int *) malloc(sizeof(unsigned int) * n_queens);
    return genes;
}

Genes random_genes(int n_queens)
{
    /*
     Initialises a Genes variable with rows (1,..., n_queens),
     shuffles it to obrain a random permutation of it and returns
     the obtained permutation. This assures there is one unique
     queen for each column (and each row).
    */

    Genes genes = initiate_genes(n_queens);
    unsigned int i;
    for (i = 1; i <= n_queens; i++){
        genes.rows[i - 1] = i;
    }
    shuffle(&genes.rows[0], n_queens);
    return genes;
}

void initiate(Individual *population, int id, int n_pop, int n_queens)
{
    /*
      Initialises a population of individuals.

      population: array of individuals (pointer to the first individual)
      id: the last id number available (id = id_lastused + 1)
      n_pop: number of individuals of the population
      n_queens: number of queens (dimension of the chessboard)
    */

    int sumdown = sum_down(n_queens);

    for (int i = 0; i < n_pop; i++)
    {   //Choosing random genes for the i-th individual
        Genes genes = random_genes(n_queens);
        //Initialisation of the i-th individual
        Individual individual = {id, genes, sumdown, false};
        population[i] = individual;
        ++id;
    }
}

void express_genes(Individual individual, int n_queens)
{
    /*
    Prints the fenotype of the individual, which is a particular
    chessboard (n_queens x n_queens) configuration of n_queens queens.
    */
    char span[40] = {                                        };
    int row, col, index;

    for (col = 0; col < (int) ((80 - n_queens * 2 - 4) / 2); col++)
        span[col] = ' ';

    for (row = n_queens; row > 0; row--)
    {
        printf("%s%3d ", span, row);
        for(col = 0; col < n_queens; col++)
        {
            if (row == individual.genes.rows[col]) printf("X ");
            else printf(". ");
        }
        printf("\n");
    }
    printf("   ");
    printf("%s", span);
    for (col = 0; col < n_queens; col++)
    {
        index = col;
        while(index > 25) index -= 26;
        printf(" %c", ALPHABET[index]);
    }
    printf("\n");
    printf("%s", span);
    if (n_queens > 26)
    {
        printf("   ");
        for (col = 0; col < n_queens; col++)
            printf(" %d", (int) col/26+1);
        printf("\n");
    }
    printf("\n");
}

bool diagonal(unsigned int column1, unsigned int row1, unsigned int column2,
              unsigned int row2)
{
    /*
    Given the position (col, row) of two queens, returns whether they meet in a
    diagonal or not. It works since we work with a squared chessboard and the
    diagonals have slope = 1. Thus, two queens meet if and only if they form
    the hipotenuse of a rectangle triangle with equal catetus:
    */

    unsigned int diff1, diff2;
    diff1 = absolute(column1 - column2);
    diff2 = absolute(row1 - row2);
    if(diff1 == diff2)
        return true;
    return false;
}

void evaluate(Individual *population, int n_pop, int n_queens)
{
    /*
     Given a input population of size n_pop initialises the scorer (fitness)
     of each individual. The default scorer is:

                    1 + ... + n_queens = sum_down(n_queens)

     since it is the case where all queens are situated in a main diagonal and
     each one meets with all the others.

     If the individual scorer is equal to the default scorer, then it is
     counted the number of (unique) pairs of queens that meet and uptdate the
     scorer of that individual.

     The smallest the scorer of an individual it gets, the better it is.
    */

    int i, j, k, row;
    unsigned int scorer;
    for(i = 0; i < n_pop; ++i)
    {
        scorer = 0;
        for(j = 0; j < n_queens; j++)
        {
            row = population[i].genes.rows[j];
            // start from j+1 to not compare to itself and not to repeat a
            // pair of individuals
            for(k = j + 1; k < n_queens; k++)
                if(diagonal(row, j+1, population[i].genes.rows[k], k+1))
                    ++scorer;
        }
        population[i].scorer = scorer;

    }
}

RouletteCompartments *malloc_roulette(int n_pop)
{
    /*
     Reserves memory for a RouletteCompartments struct (a wheel roulette) and
     returns it.
    */
    RouletteCompartments *genetic_roulette = (RouletteCompartments *)
                                  malloc(sizeof(RouletteCompartments) * n_pop);
    return genetic_roulette;
}

float initiate_roulette(Individual *population,
                        RouletteCompartments *genetic_roulette, int n_pop,
                        int n_queens, float weight, float power, bool fitness)
{
    /*
     @TODO
    */

    int i;
    float sum = 0;
    Individual *competitor;

    if(fitness == fit)
    {
        for(i = 0; i < n_pop; ++i)
        {
            competitor = &population[i];
            if(!competitor->chosen)
                sum += 1 / pow((competitor->scorer + weight), power);
            genetic_roulette[i].delimiter = sum;
            genetic_roulette[i].individual = competitor;
        }
    }

    if(fitness == unfit)
    {
        for(i = 0; i < n_pop; ++i)
        {
            competitor = &population[i];
            if(competitor->chosen)
                continue;
            sum += 1 / pow(sum_down(n_queens) - competitor->scorer + weight,
                           power);
            genetic_roulette[i].delimiter = sum;
            genetic_roulette[i].individual = competitor;
        }
    }
    return sum;
}

void sort_by_scorer(Individual *subpopulation, int k_selections)
{
    /*
    @TODO
    */
    int i, j;
    Individual t;

    for (i = 0; i < k_selections - 1; i++)
        for (j = 0; j < k_selections - 1; j++)
        {
            if (subpopulation[j].scorer > subpopulation[j+1].scorer)
            {
                t = subpopulation[j+1];
                subpopulation[j+1] = subpopulation[j];
                subpopulation[j] = t;
            }
        }
}

Individual *find_best(Individual *subpopulation, int k_selections)
{
    /*
     Given a population of n_pop individuals, finds the FIRST with
     the best scorer and returns it.
    */

    int i, rand_index, repetitions = 0;
    Individual *best;


    sort_by_scorer(subpopulation, k_selections);

    for (i = 0;
         subpopulation[i].scorer ==
         subpopulation[i+1].scorer && i < k_selections;
         i++)
        repetitions++;

    if (repetitions > 0)
    {
        rand_index = arc4random_uniform(repetitions+1);
        best = &subpopulation[rand_index];
    }
    else
        best = &subpopulation[0];

    return best;
}

Individual *roulette_selection(Individual *population,
                               RouletteCompartments *genetic_roulette,
                               int n_pop, int n_queens, float weight,
                               float power, bool fitness)
{
    /*
     Given a population of n_pop individuals, initiates a roulette and returns
     the selected individual
     genetic_roulette: an empty RouletteCompartments object, with memory
     already reserved.
    */

    float max_delimiter, random;

    max_delimiter = initiate_roulette(population, genetic_roulette, n_pop,
                                      n_queens, weight, power, fitness);
    random = random_number(max_delimiter);

    int choice = 0;

    if(max_delimiter == 0)
    {
        printf("Error!\n");
        exit(0);
    }

    while(genetic_roulette[choice].delimiter < random)
        ++choice;

    genetic_roulette[choice].individual->chosen = true;

    return genetic_roulette[choice].individual;
}

Individual *tournament_selection(Individual *population, int n_pop,
                                 int k_selections, bool replacement)
{
    /*
      Selects k_selections individuals at random from a population and returns
      the fittest one
    */

    int i, j, k;
    int random_position;
    int selected_individuals[k_selections];
    bool repeated;

    if (k_selections > n_pop)
    {
        printf("Error: Tournament selection was unable to make ");
        printf("%d different columns to mutate.\nChoose either", k_selections);
        printf("a lower \'k_selections\' value or increase the population si");
        printf("ze.\n");
        exit(1);
    }

    k = 0;
    for (i = 0;  i < k_selections;)
    {
        random_position = arc4random_uniform(n_pop);
        if (replacement)
        {
            selected_individuals[i] = random_position;
            i++;
        }
        else
        {
            repeated = false;
            for (j = 0; j < i; j++)
            {
                if (random_position == selected_individuals[j])
                    repeated = true;
            }
            if (!repeated)
            {
                k = 0;
                selected_individuals[i] = random_position;
                i++;
            }
            else
                k++;
        }
        if (k > 1000000)
        {
            printf("Error: Tournament selection was unable to make ");
            printf("%d different columns to mutate.\nChoose ", k_selections);
            printf("either a lower \'k_selections\' value or increase the ");
            printf("population size.\n");
            exit(1);
        }
    }

    int best = selected_individuals[0];
    unsigned int scorer = population[selected_individuals[0]].scorer;

    for (i = 1;  i < k_selections; i++)
    {
        if (population[selected_individuals[i]].scorer < scorer)
        {
            best = selected_individuals[i];
            scorer = population[selected_individuals[i]].scorer;
        }
    }

    return &population[best];
}

void reset_selection(Individual *population, int n_pop)
{
    /*
     Resets the variable 'chosen' of each individual of the input population
     to false.
    */

    int i;
    /*@tocheck: is the input array population modified outside the function?*/
    for(i = 0; i < n_pop; ++i)
        population[i].chosen = false;
}

Individual ordered_crossover(Individual *parent1, Individual *parent2, int id,
                             int n_queens)
{
    /*
     Given two parents, parent1 and parent2, this function performs the
     classical OX crossover algorithm to obtain only ONE child by means of the
     genes of both parents.

     Procedure: OX
        1. Select a substring from the genes.rows of a parent at random.
        2. Produce a proto-child by copying the substring into the
        corresponding position of it, now in the genes.rows of the proto-child.
        3. Delete the rows which are already in the substring from the 2nd
        parent. The resulted sequence of gene.rows after the deletion,
        contains the rows that the proto-child needs.
        4. Place the rows that the proto-child needs into the unfixed positions
        of the proto-child.genes.rows from left to right according to the order
        of the sequence to produce an offspring.
    */

    int i, j = 0, k, tmp;
    Genes genes = initiate_genes(n_queens);
    unsigned int row;
    bool missing;

    int random1 = arc4random_uniform(n_queens);
    int random2 = arc4random_uniform(n_queens);

    if (random2 < random1){
        tmp = random1;
        random1 = random2;
        random2 = tmp;
    }

    // Copy rows from parent1 to child. Set rest of rows equal to 0.
    for (i = 0; i < n_queens; i++)
    {
        if (i >= random1 && i <= random2)
            genes.rows[i] = parent1->genes.rows[i];
        else
            genes.rows[i] = 0;
    }

    // Ordered copy of the rows from parent2 to child.
    for (i = 0; i < n_queens; i++)
    {
        if (i < random1 || i > random2){
            for (; j < n_queens; j++){
                row = parent2->genes.rows[j];
                missing = true;
                for (k = 0; k < n_queens; k++){
                    if (genes.rows[k] == row)
                        {
                            missing = false;
                            break;
                        }
                }
                if (missing){
                    genes.rows[i] = row;
                    break;
                }
            }
        }
    }

    Individual child = {id, genes, sum_down(n_queens), false};
    return child;
}

void swapping_mutation(Individual *mutant, int n_queens, float p_mut)
{
    unsigned int index1, index2, temp;

    float random = random_number(1);
    index1 = arc4random_uniform(n_queens);
    index2 = index1;

    if (random < p_mut)
    {
        while (index1 == index2)
            index2 = arc4random_uniform(n_queens);

        temp = mutant->genes.rows[index1];
        mutant->genes.rows[index1] = mutant->genes.rows[index2];
        mutant->genes.rows[index2] = temp;
    }
}

void copy_individual(Individual *original, Individual *copy, int n_queens)
{
    int i;
    copy->id = original->id;
    copy->chosen = original->chosen;
    copy->scorer = sum_down(n_queens);
    for (i = 0; i < n_queens; i++)
        copy->genes.rows[i] = original->genes.rows[i];
}

void heuristic_mutation(Individual *mutant, unsigned int **permutations,
                        int n_queens, int lambda, int n_perms, float p_mut)
{
    /*
     Given an input individual 'mutant', a probability p_mut of mutation
     and an integer lambda, if a generated random number between 0 and 1
     is smaller than p_mut, then the mutant individual will mutate as follows:

     Procedure: Heuristic Mutation.
        1. Pick up lambda genes (from mutant.genes.rows) at random.
        2. Generate neighbors according to all possible permutations of the
        selected gens.
        3. Evaluate all neighbors and select the best one as offspring.
     The best selected is returned.
    */
    float random = random_number(1);
    int i, j, k, cols_to_mutate[lambda], col;
    unsigned int rows_to_mutate[lambda];
    bool repeated;

    if(random < p_mut)
    {
        for (i = 0; i < lambda; i++)
        {
            repeated = true;
            k = 0;
            while (repeated && k < 1000)
            {
                repeated = false;
                k++;
                cols_to_mutate[i] = arc4random_uniform(n_queens);
                for (j = 0; j < i; j++)
                    if (cols_to_mutate[i] == cols_to_mutate[j])
                        repeated = true;
            }
            if (k == 1000)
            {
                printf("Error: Heuristic mutation was unable to find ");
                printf("%d different columns to mutate. Check ", lambda);
                printf("initial parameters.\n");
                exit(1);
            }
            rows_to_mutate[i] = mutant->genes.rows[cols_to_mutate[i]];
        }

        int counter = 0;
        permute(permutations, rows_to_mutate, 0,lambda, &counter);

        int cols[n_queens], best;
        unsigned int scorer, best_scorer = 0;

        for (i = 0; i < n_perms; i++)
        {
            for (j = 0; j < n_queens; j++)
                cols[j] = mutant->genes.rows[j];

            for (j = 0; j < lambda; j++)
            {
                col = cols_to_mutate[j];
                cols[col] = permutations[i][j];
            }

            scorer = 0;
            for(j = 0; j < n_queens; j++)
                for(k = j + 1; k < n_queens; k++)
                    if(diagonal(cols[j], j+1, cols[k], k+1))
                        ++scorer;

            if (i == 0 | scorer < best_scorer)
            {
                best_scorer = scorer;
                best = i;
            }
        }

        // Get best rows
        for (j = 0; j < n_queens; j++)
            cols[j] = mutant->genes.rows[j];

        for (j = 0; j < lambda; j++)
        {
            col = cols_to_mutate[j];
            cols[col] = permutations[best][j];
        }

        // Apply them to mutant
        for (j = 0; j < n_queens; j++)
            mutant->genes.rows[j] = cols[j];
    }
}

void view_population(Individual *population, int n_pop, int n_queens,
                     int n_gen)
{
    /*
     Given a population of n_pop individuals and its generation,
     prints out onto the screen the genes and the scorer (fitness) of
     each of its individuals, line by line.
    */

    int i, j;
    printf("\nGeneration %d\n\nIndividual id\tGenes\t\t\tScorer\n", n_gen);
    for (i = 0; i < n_pop; ++i)
    {
        printf("\t%d\t(%d", population[i].id, population[i].genes.rows[0]);
        for (j = 1; j < n_queens; ++j)
            printf(",%d", population[i].genes.rows[j]);
        printf(")\t%d\n", population[i].scorer);
    }
}

void write_fitness(FILE ** file, char * filename, Individual * population,
                   int n_pop, int generation)
{
    /*
     Given a pointer to file and a file name, appends into a file the scorer
     of each individual of the input population, one by one and separated by
     commas. In the first position it is printed the generation of the input
     population.

     By calling this function after sucessive generations of individuals are
     created, we can obtain a file whose rows are the fitnesses of the
     corresponding individuals for each generation.
    */

    *file = fopen(filename, "a");

    if (*file == NULL)
    {
        printf("Error changing to append 'a' file!\n");
        exit(1);
    }

    fprintf(*file, "%d,", generation);

    for (int i = 0; i < n_pop; i++)
    {
        if (i < n_pop-1)
            fprintf(*file, "%u,", population[i].scorer);
        else
            fprintf(*file, "%u\n", population[i].scorer);
    }

    fclose(*file);
}

void write_population_genes(FILE **file, char *filename,
                            Individual *population, int n_pop, int n_queens)
{
    *file = fopen(filename, "a");

    if (*file == NULL)
    {
        printf("Error changing to append 'a' file!\n");
        exit(1);
    }

    for(int i = 0;i < n_pop;i++){
        for(int j = 0; j < n_queens; j++){
            if(j < n_queens-1){
                fprintf(*file, "%u,", population[i].genes.rows[j]);
            }
            else{
                fprintf(*file, "%u\n", population[i].genes.rows[j]);
            }

        }
    }

    fclose(*file);
}
