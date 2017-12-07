/*#ifndef CONSTANTS
#define CONSTANTS*/
    #include <stdbool.h>
    #include "definitions.h"

    //extern const int ARGS_NUM;

    extern const char ALPHABET[26];
        // Constants for default parameters
        // List of arguments
                      
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

//#endif

/*
    extern const char ALPHABET[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                                   'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                                   'U', 'V', 'W', 'X', 'Y', 'Z'};
        // Constants for default parameters
        // List of arguments
                                   
    extern const char ARGS[ARGS_NUM][3] = {"-q", "-p", "-g", "-d", "-m", "-l", "-c",
                                        "-i", "-r", "-x", "-s", "-t", "-w", "-e",
                                        "-y", "-f"};                               
        // Number of queens -q
    extern  const int N_QUEENS = 8;
        // Population size -p
    extern  const int N_POPULATION = 10;
        // Number of generations -g
    extern  const int N_GENERATIONS = 1000;
        // Death ratio per generation -d
    extern  const float DEATH_RATIO = 0.3;
        // Probability of mutation -m
    extern  const float P_MUTATION = 0.2;
        // Number of genes to mutate -l
    extern  const int LAMBDA = 3;
        // Force the algorithm to continue after finding a solution -c
    extern  const bool FORCE_TO_CONTINUE = false;
        // Infinite number of generations -i
    extern  const bool INFINITE_GENERATIONS = false;
        // Write fitness data to file -r
    extern  const bool WRITE_FITNESS = false;
        // Maximum fitness points -x
    extern  const int MAX_FITNESS_POINTS = 1000;
        // Frequency to summarize -s
    extern  const int SUMMARIZE_FREQ = 100;
        // Number of selections in the tournament_selection function -t
    extern  const int TOURNAMENT_SELECTIONS = 3;
        // The higher, the more exploratory -w
    extern  const float FRACT_WEIGTH = 0.1;
        // The higher, the more exploitatory -e
    extern  const float DENOM_POWER = 2;
        // Set the strategy to apply -y
    extern  const int STRATEGY = 1;
    */