// Include Libraries
#include "8queens.h"

// Definitions
/*#define fit 1
#define unfit 0
#define Individual struct Individual
#define Genes struct Genes
#define RouletteCompartments struct RouletteCompartments*/

// Constants
// Number of queens (DON'T CHANGE! (YET))
const int N_QUEENS = 8;
// Population size
const int N_POPULATION = 100;
// Number of generations
const int N_GENERATIONS = 1000;
// Probability of mutation
const float P_MUTATION = 0.7;

int main(){

    // Number of deaths per generation
    const int N_DEATHS = (int) (N_POPULATION * 0.5);
    bool Stop_IfSolutionFound = 0;

    //Create, initialise text files
    char file_fitness[] = "Fitness.csv";
    FILE *f = fopen(file_fitness, "w");
    if (f == NULL){printf("Error opening file!\n");exit(1); }

    // Initialize variables
    int id = 1;
    int n_gen = 1;
    int i, j;
    Individual best, parent1, parent2, child, survivor, *Population, *NextPopulation, *candidate;

    // Save memory space for Population and genetic roulette
    Individual *P = (Individual *) malloc(sizeof(Individual) * N_POPULATION);
    Individual *Q = (Individual *) malloc(sizeof(Individual) * N_POPULATION);
    RouletteCompartments *genetic_roulette = malloc_roulette(N_POPULATION);

    // Set Population pointers
    Population = P;
    NextPopulation = Q;
    Individual *T;

    // Initialize best individual
    best.scorer = sum_down(N_QUEENS);//???????????

    // Initialize population and genetic roulette
    id = initiate_different(Population, id, N_POPULATION, N_QUEENS);
    view_population(Population, N_POPULATION, N_QUEENS, n_gen);
    WriteFitnessesToFile(&f, file_fitness, Population, N_POPULATION, n_gen);
    // Initiate Genetic Algorithm
    while(n_gen <= N_GENERATIONS)
    {   

        
        evaluate(Population, N_POPULATION, N_QUEENS);

        reset_selection(Population, N_POPULATION);
        for(j = 0; j < N_DEATHS; ++j)
        {
            parent1 = _select(Population, genetic_roulette, N_POPULATION, N_QUEENS, fit);
            parent2 = _select(Population, genetic_roulette, N_POPULATION, N_QUEENS, fit);
            //ìmprovement: likelyhood of crossver between 0.6 and 1. Now is 1
            child = heuristic_mutation(crossover(parent1, parent2, ++id, N_QUEENS), N_QUEENS, P_MUTATION);
            NextPopulation[j] = child;
        }

        reset_selection(Population, N_POPULATION);
        for(j=N_DEATHS; j < N_POPULATION; ++j)
        {
            survivor = _select(Population, genetic_roulette, N_POPULATION, N_QUEENS, fit);
            NextPopulation[j] = survivor;
        }

        T = Population;
        Population = NextPopulation;
        NextPopulation = T;

        //view_population(Population, N_POPULATION, N_QUEENS, n_gen);

        ++n_gen;

        //Check if in the actual (new) Population is there an optimal (best) individual
        if(Stop_IfSolutionFound){
            if( (  candidate = find_best(Population, N_POPULATION)  ) != NULL){
                best = *candidate;
                break;
            }
        }


     if(N_GENERATIONS <= 1000){
            WriteFitnessesToFile(&f, file_fitness, Population, N_POPULATION, n_gen);
        }   
    }
    view_population(NextPopulation, N_POPULATION, N_QUEENS, n_gen); //crec que seria Population i no pas next population?
    if(best.scorer != 0){
        printf("\n No optimal individual found... \n");
    }
    else{ printf("Found at least one optimal individual id %d, scorer: %d\n ", best.id, best.scorer);
          view_population(&best, 1, N_QUEENS, n_gen);
          express_genes(best);
    }
}
