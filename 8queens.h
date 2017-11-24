// Include Libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

// Definitions
#define fit 1
#define unfit 0
#define Individual struct Individual
#define Genes struct Genes
#define RouletteCompartments struct RouletteCompartments
#define random_bool arc4random_uniform(2)

// Constants
// Smallest probability for the worst individual to survive
// The higher, the more exploratory
const float FRACT_WEIGTH = 0.01;
// The higher, the more exploitatory
const float DENOM_POWER = 1;

// Define Structures
Genes
{
    char column[8];
};

Individual
{
    int id;
    Genes genes;
    unsigned char scorer;
    bool chosen;
};

RouletteCompartments
{
    float delimiter;
    Individual *individual;
};

//Functions
Genes _random_genes(int n_queens)
{
    Genes genes;
    unsigned char random;
    int i;
    for (i = 0; i < 8; ++i){
        arc4random_buf(&random, sizeof random);
        genes.column[i] = random / 256. * n_queens;
    }
    return genes;
}

int sum_down(int n)
{
    return n*(n+1)/2;
}

float random_number(float max)
{
    float random;
    random = (arc4random_uniform(UINT16_MAX))/ ((float)(UINT16_MAX)) * max;
    return random;
}

//char random_int()

int initiate(Individual *Population, int id, int n_pop, int n_queens)
{
    int i;
    for (i = 0; i < n_pop; i++)
    {
        Genes genes = _random_genes(n_queens);
        Individual individual = {id, genes, sum_down(n_queens), false};
        Population[i] = individual;
        ++id;
    }
    return id;
}

void check_random_uniformity(float max)
{
    float num;
    int N = 10000000;
    int n1, n2, n3, n4, n5, n6, n7, n8, n9, n10;
    float highest, lowest;
    highest = 0;
    lowest = max;
    n1 = n2 = n3 = n4 = n5 = n6 = n7 = n8 = n9 = n10 = 0;
    int div = max / 10;
    double sum = 0;
    int i;
    for(i=0; i<N; i++){
        num = random_number(max);
        sum += num;
        if(num < div) ++n1;
            else if(num < 2 * div) ++n2;
                else if(num < 3 * div) ++n3;
                    else if(num < 4 * div) ++n4;
                        else if(num < 5 * div) ++n5;
                            else if(num < 6 * div) ++n6;
                                else if(num < 7 * div) ++n7;
                                    else if(num < 8 * div) ++n8;
                                        else if(num < 9 * div) ++n9;
                                            else if(num < 10 * div) ++n10;
        if(num > highest) highest = num;
        if(num < lowest) lowest = num;
    }
    float result = sum / ((double) N);
    printf("%f\n", result);
    printf("n1=%f,n2=%f,n3=%f,n4=%f,n5=%f,n6=%f,n7=%f,n8=%f,n9=%f,n10=%f\n",n1/(float)N,n2/(float)N,n3/(float)N,n4/(float)N,n5/(float)N,n6/(float)N,n7/(float)N,n8/(float)N,n9/(float)N,n10/(float)N);
    printf("max=%f, min=%f\n", highest, lowest);
}

void check_random_uniformity2()
{
    unsigned char random_number;
    unsigned int num;
    int N = 10000000;
    long sum = 0;
    int i;
    for(i=0; i<N; i++){
        arc4random_buf(&random_number, sizeof(random_number));
        num = random_number / 256. * 8;
        sum += num;
    }
    float result = sum / ((float) N);
    printf("%f\n", result);
}

void express_genes(Individual individual)
{
    int i, j, column;
    for(i = 7; i >= 0; --i){
        printf("%d ", i + 1);
        column = individual.genes.column[i];
        for(j = 0; j < column; ++j)
            printf(". ");
        printf("X ");
        for(j = column + 1; j < 8; ++j)
            printf(". ");
        printf("\n");
    }
    printf("  A B C D E F G H\n");
}

char * sort(char array[8]){
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

unsigned char absolute(char value)
{
    if(value < 0)
        return -value;
    return value;
}

bool diagonal(unsigned char column1, unsigned char row1, unsigned char column2, unsigned char row2)
{
    unsigned char diff1, diff2;
    diff1 = absolute(column1 - column2);
    diff2 = absolute(row1 - row2);
    if(diff1==diff2)
        return true;
    return false;
}

void evaluate(Individual *Population, int n_pop, int n_queens)
{
    int i, j, k, column;
    unsigned char scorer;
    char *sorted_cols = (char *) malloc(sizeof(char) * 8);
    short *slopes = (short *) malloc(sizeof(short) * 8);
    for(i = 0; i < n_pop; ++i)
    {
        if(Population[i].scorer != sum_down(n_queens))
            continue;
        else
        {
            scorer = 0;
            sorted_cols = sort(Population[i].genes.column);
            scorer += sum_down(count_repetitions(sorted_cols));
            for(j = 0; j < 7; ++j)
            {
                column = Population[i].genes.column[j];
                for(k = j + 1; k < 8; ++k)
                    if(diagonal(column, j, Population[i].genes.column[k], k))
                        ++scorer;
            }
            Population[i].scorer = scorer;
        }
    }
}

RouletteCompartments *malloc_roulette(int n_pop)
{
    RouletteCompartments *genetic_roulette = (RouletteCompartments *) malloc(sizeof(RouletteCompartments) * n_pop);
    return genetic_roulette;
}

float initiate_roulette(Individual *Population, RouletteCompartments *genetic_roulette, int n_pop, int n_queens, bool fitness)
{
    int i;
    float sum = 0;
    Individual *competitor;
    if(fitness == fit)
    {
        for(i = 0; i < n_pop; ++i)
        {
            competitor = &Population[i];
            if(!competitor->chosen)
                sum += 1 / pow((competitor->scorer + FRACT_WEIGTH), DENOM_POWER);
            genetic_roulette[i].delimiter = sum;
            genetic_roulette[i].individual = competitor;
        }
    }
    if(fitness == unfit)
    {
        for(i = 0; i < n_pop; ++i)
        {
            competitor = &Population[i];
            if(competitor->chosen)
                continue;
            sum += 1 / pow(sum_down(n_queens) - competitor->scorer + FRACT_WEIGTH, DENOM_POWER);
            genetic_roulette[i].delimiter = sum;
            genetic_roulette[i].individual = competitor;
        }
    }
    return sum;
}

void view_selection(RouletteCompartments *genetic_roulette, int n_pop, float random, int selection)
{
    int i;

    if(selection == 0)
        printf("-->\t0: (0.000000-%f)\tChosen: %i\n", genetic_roulette[0].delimiter, genetic_roulette[0].individual->chosen);
    else
        printf("\t0: (0.000000-%f)\tChosen: %i\n", genetic_roulette[0].delimiter, genetic_roulette[0].individual->chosen);

    for(i=1;i<n_pop;++i){
        if(i==selection)
            printf("-->\t%d: (%f-%f)\tChosen: %i\n", i, genetic_roulette[i-1].delimiter, genetic_roulette[i].delimiter, genetic_roulette[i].individual->chosen);
        else
            printf("\t%d: (%f-%f)\tChosen: %i\n", i, genetic_roulette[i-1].delimiter, genetic_roulette[i].delimiter, genetic_roulette[i].individual->chosen);
    }

    printf("Random: %f\tSelected: %d (Scorer %d)\n", random, selection, genetic_roulette[selection].individual->scorer);
}

Individual select(Individual *Population, RouletteCompartments *genetic_roulette, int n_pop, int n_queens, bool fitness)
{
    float max_delimiter, random;

    max_delimiter = initiate_roulette(Population, genetic_roulette, n_pop, n_queens, fitness);
    random = random_number(max_delimiter);

    int selection = 0;

    if(max_delimiter == 0)
    {
        printf("Error!\n");
        exit(0);
    }

    while(genetic_roulette[selection].delimiter < random)
        ++selection;

    genetic_roulette[selection].individual->chosen = true;

    //view_selection(genetic_roulette, n_pop, random, selection);

    return *genetic_roulette[selection].individual;
}

void reset_selection(Individual *Population, int n_pop)
{
    int i;
    for(i = 0; i < n_pop; ++i)
        Population[i].chosen = false;
}

Individual crossover(Individual parent1, Individual parent2, int id, int n_queens)
{
    int i;
    Genes genes;

    for(i = 0; i < n_queens; ++i)
    {
        if(random_bool)
            genes.column[i] = parent1.genes.column[i];
        else
            genes.column[i] = parent2.genes.column[i];
    }

    Individual child = {id, genes, sum_down(n_queens), false};

    return child;
}

Individual crossover2(Individual parent1, Individual parent2, int id, int n_queens)
{
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
        genes.column[i] = p1->genes.column[i];

    for(i = n_queens/2; i < n_queens; ++i)
        genes.column[i] = p1->genes.column[i];

    Individual child = {id, genes, sum_down(n_queens), false};

    return child;
}

Individual mutation(Individual mutant, int n_queens, float p_mut)
{
    float random = random_number(1);
    unsigned char alteration, column;

    if(random < p_mut)
    {
        column = (unsigned char) arc4random_uniform(n_queens);
        alteration = (unsigned char) arc4random_uniform(n_queens);
        mutant.genes.column[column] = alteration;
        //mutant.id = 0;
        mutant = mutation(mutant, n_queens, p_mut);
    }
    return mutant;
}

void view_population(Individual *Population, int n_pop, int n_queens, int n_gen)
{
    int i, j;
    printf("\nGeneration %d\n\nIndividual id\tGenes\t\t\tScorer\n", n_gen);
    for(i = 0; i < n_pop; ++i)
    {
        printf("\t%d\t(%d", Population[i].id, Population[i].genes.column[0]);
        for(j = 1; j < n_queens; ++j)
            printf(",%d", Population[i].genes.column[j]);
        printf(")\t%d\n", Population[i].scorer);
    }
}

