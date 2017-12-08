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
#include "genetics.h"
#include "arguments.h"
#include "utils.h"
#include "constants.h"

int main(){
    // Constants
    // Number of queens (DON'T CHANGE! (YET))
    const int N_QUEENS = 8;
    // Initialize variables
    int id = 1;

    // Initialize population
    Individual queens_combination;
    initiate(&queens_combination, id, 1, N_QUEENS);

    // First evaluation of the population
    evaluate(&queens_combination, 1, N_QUEENS);

    // Iterate until finding a solution
    int i;
    while(queens_combination.scorer != 0){
        // Each new generation has got brand new individuals with random genes
        initiate(&queens_combination, ++id, 1, N_QUEENS);
        evaluate(&queens_combination, 1, N_QUEENS);
    }
    printf("Found individual %d\n", queens_combination.id);
    express_genes(queens_combination, N_QUEENS);
}
