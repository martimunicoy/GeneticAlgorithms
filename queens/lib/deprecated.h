/*****************************************************************************/
// Old functions and implementations (DEPRECATED)
/*****************************************************************************/

// Include Libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

// Definitions
#define fit 1
#define unfit 0
#define random_bool arc4random_uniform(2)

Individual crossover2(Individual parent1, Individual parent2, int id, int n_queens)
{
    /*
     Only valid for n_queens odd
    */
    int i;
    Genes genes;
    Individual *p1 = &parent1;
    Individual *p2 = &parent2;

    if(random_bool)
    {
        p1 = &parent2;
        p2 = &parent1;
    }

    for(i = 0; i < n_queens/2; ++i)
        genes.rows[i] = p1->genes.rows[i];

    for(i = n_queens/2; i < n_queens; ++i)
        genes.rows[i] = p1->genes.rows[i]; //!!!! I think it must be p2->genes.row[i]

    Individual child = {id, genes, sum_down(n_queens), false};

    return child;
}

char * sort(char array[8]){
    /*
    Improvements:
       - Do the algorithm for a N dimensional array (general)
       - This algorithm is o(n^2), use a more efficient one.
       - I think there is no need to copy the input array,
         instead do a void type function which modifies the input array
         since it is passed by reference (vale fals, he vist per a què s'utilitzava).
    */
    int i, j, t;
    static char sorted_array[8];
    for(i = 0; i < 8; ++i)
        sorted_array[i] = array[i];
    for(i = 0; i < 7; ++i)
        for(j = 0; j < 7; ++j)
        {
            if(sorted_array[j] > sorted_array[j+1])
            {
                t = sorted_array[j+1];
                sorted_array[j+1] = sorted_array[j];
                sorted_array[j] = t;
            }
        }
    return sorted_array;
}

int count_repetitions(char array[8]){
    /*
    !!!!! Això només mira repeticions entre i, i+1.??
    THIS ASSUMES THAT THE INPUT array is sorted in ASCENDENT order!
    */
    int i, current;
    int count = 0;
    char previous = array[0];
    for(i = 1; i < 8; ++i){
        current = array[i];
        if(current == previous)
            ++count;
        else
            previous = current;
    }
    return count;
}

void old_evaluate(Individual *population, int n_pop, int n_queens)
{
    /*
     The smaller the scorer of an individual, the better (?)
    */

     /*
     Improvements:

     - I would do an additional function to perform the loop in j and k
     that, given a the an individual, returns the number of pairs of queens that meet in a diagonal.
     Use the notation like diagonal_meets(Individual individual){ col1,row1,col2,row2; }
     then do scorer += diagonal_meets(Population[i]);

     - Not allow that an individual has repeated columns in different rows, so that
     in this function the scorer+= sum_down() is not needed
      */
    int i, j, k, row;
    unsigned char scorer;
    char *sorted_cols = (char *) malloc(sizeof(char) * 8);
    short *slopes = (short *) malloc(sizeof(short) * 8); //unused
    int sumdown = sum_down(n_queens);
    for(i = 0; i < n_pop; ++i)
    {
        if(population[i].scorer != sumdown) //!!!!scorer is unsigned char [0,255], sum_down is int
            continue;
        else
        {
            scorer = 0;
            sorted_cols = sort(population[i].genes.rows);
            scorer += sum_down(count_repetitions(sorted_cols));
            for(j = 1; j < n_queens; j++)
            {
                row = population[i].genes.rows[j];
                //start from j+1 to not compare to itself and not to repeat a pair of individuals
                for(k = j + 1; k <= n_queens; k++)
                    if(diagonal(row, j, population[i].genes.rows[k], k))
                        ++scorer;
            }
            population[i].scorer = scorer;
        }
    }
}

Individual mutation(Individual mutant, int n_queens, float p_mut)
{
    float random = random_number(1);
    unsigned char alteration, row;
    /* !!! quite strange */

    if(random < p_mut)
    {
        row = (unsigned char) arc4random_uniform(n_queens);
        alteration = (unsigned char) arc4random_uniform(n_queens);
        mutant.genes.rows[row] = alteration + 1;
        //mutant.id = 0;
        mutant = mutation(mutant, n_queens, p_mut);//???????
    }
    return mutant;
}
