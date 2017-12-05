// Include Libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

// Definitions
#define fit 1
#define unfit 0
#define uint unsigned int

// Constants
// The higher, the more exploitatory
const float DENOM_POWER = 2;

const float MIN_WEIGHT = 0.005;

// Define Structures
struct Genes
{
    uint x;
    uint y;
    uint z;
    uint t;
};

struct Individual
{
    int id;
    struct Genes genes;
    double image;
    double score;
    bool chosen;
};

struct RouletteCompartments
{
    float delimiter;
    struct Individual *individual;
};

double phi(uint x, uint y, uint z, uint t, float a, float b,
                      float c, float d)
{
    double result;
    result = (pow(2, 43) - pow(x - a, 2) - pow(y - b, 2) - pow(z - c, 2)
              - pow(t - d, 2));
    //printf("phi: %f\n", result);
    return result;
}

int s_power(uint x, uint y, uint z, uint t)
{
    double result;
    result = (int) ((x + t)/(pow(2, 31) + y + z) + 0.86525597943226508722);
    //printf("s: %f\n", result);
    //printf("s: %d\n", (int) result);
    return result;
}

double function(uint x, uint y, uint z, uint t)
{
    double result;
    result = (pow(-1, s_power(x, y, z, t)) * sin(x + y + z + t) *
              phi(x, y, z, t, 1237566.4, 54783217.5, 1237896431.1, 325123467.37) *
              phi(x, y, z, t, 5674235.4, 4067231567.2, 13245678.3, 3748967543.2) *
              phi(x, y, z, t, 3867435523.2, 7134893.75, 3565897564.1, 15675987.34) *
              phi(x, y, z, t, 4000223567.09, 3734098765.4, 3367981234.4, 4067231567.25));
    return result;
}

double get_max(uint x_range, uint y_range, uint z_range, uint t_range)
{
    int x, y, z, t;
    double max, result;
    max = 0;
    for (x = 0; x < x_range; x++)
        for (y = 0; y < y_range; y++)
            for (z = 0; z < z_range; z++)
                for (t = 0; t < t_range; t++)
                {
                    result = function(x, y, z, t);
                    if (result > max) max = result;
                }
    return max;
}

double get_min(uint x_range, uint y_range, uint z_range, uint t_range)
{
    int x, y, z, t;
    double min, result;
    min = function(0, 0, 0, 0);
    for (x = 0; x < x_range; x++)
        for (y = 0; y < y_range; y++)
            for (z = 0; z < z_range; z++)
                for (t = 0; t < t_range; t++)
                {
                    result = function(x, y, z, t);
                    if (result < min) min = result;
                }
    return min;
}

struct Genes _random_genes()
{
    uint random[4];
    arc4random_buf(&random, sizeof random);
    struct Genes genes = {random[0], random[1], random[2], random[3]};
    return genes;
}

void check_random_uniformity()
{
    float num;
    int N = 100000000;
    int n1, n2, n3, n4, n5, n6, n7, n8, n9, n10;
    uint highest, lowest;
    uint max = 0xFFFFFFFFU;
    highest = 0;
    lowest = max;
    n1 = n2 = n3 = n4 = n5 = n6 = n7 = n8 = n9 = n10 = 0;
    double div = max / 10;
    double sum = 0;
    struct Genes genes;
    int i, j;
    for(i=0; i<N; i++){
        genes = _random_genes();
        for (j=0; j<4; j++)
        {
            switch(j){
                case 0:
                    num = genes.x;
                case 1:
                    num = genes.y;
                case 2:
                    num = genes.z;
                case 3:
                    num = genes.t;
            }
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
        }
        if(num > highest) highest = num;
        if(num < lowest) lowest = num;
    }
    float result = sum / ((double) N * 4);
    printf("%f\n", result);
    printf("n1=%f, ", n1 / ((float)N * 4));
    printf("n2=%f, ", n2 / ((float)N * 4));
    printf("n3=%f, ", n3 / ((float)N * 4));
    printf("n4=%f, ", n4 / ((float)N * 4));
    printf("n5=%f, ", n5 / ((float)N * 4));
    printf("n6=%f, ", n6 / ((float)N * 4));
    printf("n7=%f, ", n7 / ((float)N * 4));
    printf("n8=%f, ", n8 / ((float)N * 4));
    printf("n9=%f, ", n9 / ((float)N * 4));
    printf("n10=%f\n", n10 / ((float)N * 4));
    printf("max=%u, min=%u\n", highest, lowest);
}

int initiate(struct Individual *population, int id, int n_pop)
{
    int i;
    for (i = 0; i < n_pop; i++)
    {
        struct Genes genes = _random_genes();
        struct Individual individual = {id, genes, 0, false};
        population[i] = individual;
        ++id;
    }
    return id;
}

void calculate(struct Individual *population, int n_pop)
{
    int i;
    uint x, y, z, t;
    for (i = 0; i < n_pop; i++)
    {
        x = population[i].genes.x;
        y = population[i].genes.y;
        z = population[i].genes.z;
        t = population[i].genes.t;
        population[i].image = function(x, y, z, t);
    }
}

double absolute(double num)
{
    if (num >= 0) return num;
    else return -num;
}

void evaluate(struct Individual *population, int n_pop)
{
    int i;
    double min = 0, max = 0, sum = 0;
    for (i = 0; i < n_pop; i++)
    {
        if (population[i].image < min) min = population[i].image;
        else if (population[i].image > max) max = population[i].image;
    }
    printf("min: %e\n", min);
    /*
    for (i = 0; i < n_pop; i++)
    {
        if (population[i].image < 0) population[i].score = 0.0001;
        else population[i].score = population[i].image/max;
        printf("sum %e\n", sum);
        sum += population[i].score;
    }
    for (i = 0; i < n_pop; i++)
        population[i].score = population[i].score / sum;

    */
    for (i=0; i<n_pop; i++)
    {
        population[i].score = population[i].image / max - min / max + 0.0001;
        printf("%e\t%f\t%f\n", population[i].image, population[i].image / max, (population[i].image - 2 * min )/ max);
    }

}

void reset_selection(struct Individual *population, int n_pop)
{
    int i;
    for(i = 0; i < n_pop; ++i)
        population[i].chosen = false;
}

float initiate_roulette(struct Individual *population, struct RouletteCompartments *genetic_roulette, int n_pop, bool fitness)
{
    int i;
    float sum = 0;
    struct Individual *competitor;
    if(fitness == fit)
    {
        for(i = 0; i < n_pop; i++)
        {
            competitor = &population[i];
            if(!competitor->chosen)
                sum += pow(competitor->score, DENOM_POWER);
            genetic_roulette[i].delimiter = sum;
            genetic_roulette[i].individual = competitor;
        }
    }
    if(fitness == unfit)
    {
        for(i = 0; i < n_pop; i++)
        {
            competitor = &population[i];
            if(competitor->chosen)
                continue;
            sum += 1 / pow(competitor->score, DENOM_POWER);
            genetic_roulette[i].delimiter = sum;
            genetic_roulette[i].individual = competitor;
        }
    }
    return sum;
}

float random_number(float max)
{
    float random;
    random = (arc4random_uniform(UINT16_MAX))/ ((float)(UINT16_MAX)) * max;
    return random;
}

struct Individual select(struct Individual *Population, struct RouletteCompartments *genetic_roulette, int n_pop, bool fitness)
{
    float max_delimiter, random;

    max_delimiter = initiate_roulette(Population, genetic_roulette, n_pop, fitness);
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

    return *genetic_roulette[selection].individual;
}

void express_genes(struct Individual individual)
{
    printf("f(x=%u, ", individual.genes.x);
    printf("y=%u, ", individual.genes.y);
    printf("z=%u, ", individual.genes.z);
    printf("t=%u) ", individual.genes.t);
    printf("= %f\n", individual.score);
}

void view_population(struct Individual *population, int n_pop, int n_gen)
{
    int i, j;
    printf("\n----------------------------------------------------------------\n");
    printf("                        Generation %5d                        ", n_gen);
    printf("\n----------------------------------------------------------------\n");
    printf(" Individual id |      Genes      |    Score   |      Image     ");
    printf("\n---------------+-----------------+------------+-----------------\n");
    for(i = 0; i < n_pop; ++i)
    {
        printf("\t       |  X: %10u  |\t      |", population[i].genes.x);
        printf("\n%10d", population[i].id);
        printf("     |  Y: %10u  |  ", population[i].genes.y);
        printf("%.6f  |  ", population[i].score);
        printf("%1.6e", population[i].image);
        printf("\n\t       |  Z: %10u  |\t      |", population[i].genes.z);
        printf("\n\t       |  T: %10u  |\t      |", population[i].genes.t);
        if (i < n_pop - 1) printf("\n---------------+-----------------+------------+-----------------\n");
        else printf("\n----------------------------------------------------------------\n");
    }
}
