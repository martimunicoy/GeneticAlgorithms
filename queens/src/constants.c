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

#include "constants.h"
#include "definitions.h"

const char ALPHABET[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                               'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                               'U', 'V', 'W', 'X', 'Y', 'Z'};
    // List of arguments
const char ARGS[ARGS_NUM][3] = {"-q", "-p", "-g", "-d", "-m", "-l", "-c",
                                "-i", "-r", "-x", "-s", "-t", "-w", "-e",
                                "-y", "-v", "-n", "-a", "-b", "-k", "-f"};

// Constants for default parameters

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
    // Set the sieve to apply -v
const int SIEVE = 2000;
    // Write fitness data to file -n
const bool WRITE_GENES = false;
    // Maximum fitness points -a
const int MAX_GENES_POINTS = 1000;
    // Fitness file directory
const char FITNESS_DIR[100] = "DataVisualization/Fitness.csv";
    // Genes file directory
const char GENES_DIR[100] = "DataVisualization/Genes.csv";
