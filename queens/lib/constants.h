#ifndef CONSTANTS
#define CONSTANTS
    #include <stdbool.h>
    #include "definitions.h"
    
    // Constants global parameters

    extern const char ALPHABET[26];
                      
    extern const char ARGS[ARGS_NUM][3];                               
        // Number of queens -q
    extern  const int N_QUEENS;
        // Population size -p
    extern  const int N_POPULATION;
        // Number of generations -g
    extern  const int N_GENERATIONS;
        // Death ratio per generation -d
    extern  const float DEATH_RATIO;
        // Probability of mutation -m
    extern  const float P_MUTATION;
        // Number of genes to mutate -l
    extern  const int LAMBDA;
        // Force the algorithm to continue after finding a solution -c
    extern  const bool FORCE_TO_CONTINUE;
        // Infinite number of generations -i
    extern  const bool INFINITE_GENERATIONS;
        // Write fitness data to file -r
    extern  const bool WRITE_FITNESS;
        // Maximum fitness points -x
    extern  const int MAX_FITNESS_POINTS;
        // Frequency to summarize -s
    extern  const int SUMMARIZE_FREQ;
        // Number of selections in the tournament_selection function -t
    extern  const int TOURNAMENT_SELECTIONS;
        // The higher, the more exploratory -w
    extern  const float FRACT_WEIGTH;
        // The higher, the more exploitatory -e
    extern  const float DENOM_POWER;
        // Set the strategy to apply -y
    extern  const int STRATEGY;

#endif
