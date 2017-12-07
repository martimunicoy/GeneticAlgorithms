#include "queens_GA.h"
#include "constants.h"
#include "definitions.h"

//const int ARGS_NUM = 16;

const char ALPHABET[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                               'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                               'U', 'V', 'W', 'X', 'Y', 'Z'};
    // Constants for default parameters
    // List of arguments
                               
const char ARGS[ARGS_NUM][3] = {"-q", "-p", "-g", "-d", "-m", "-l", "-c",
                                    "-i", "-r", "-x", "-s", "-t", "-w", "-e",
                                    "-y", "-f"};                               
    // Number of queens -q
const int N_QUEENS = 8;
    // Population size -p
const int N_POPULATION = 10;
    // Number of generations -g
const int N_GENERATIONS = 1000;
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
    // Maximum fitness points -x
const int MAX_FITNESS_POINTS = 1000;
    // Frequency to summarize -s
const int SUMMARIZE_FREQ = 100;
    // Number of selections in the tournament_selection function -t
const int TOURNAMENT_SELECTIONS = 3;
    // The higher, the more exploratory -w
const float FRACT_WEIGTH = 0.1;
    // The higher, the more exploitatory -e
const float DENOM_POWER = 2;
    // Set the strategy to apply -y
const int STRATEGY = 1;