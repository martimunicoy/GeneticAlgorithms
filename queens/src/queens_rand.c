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
#include "definitions.h"
#include "queens_GA.h"
#include "constants.h"
#include "genetics.h"
#include "arguments.h"
#include "utils.h"

// Function bodies
int main(int argc, char* argv[]){
    // Print welcome
    print_program_name();
    print_license_header();

    // Parse arguments
    struct Args args = args_parser(argc, argv);

    // Print problem description
    print_problem_description_rand(args);

    // Initialize variables
    int id = 1;

    // Initialize population
    Individual queens_combination;
    initiate(&queens_combination, id, 1, args.n_queens);

    // First evaluation of the population
    evaluate(&queens_combination, 1, args.n_queens);

    // Iterate until finding a solution
    int i;
    while(queens_combination.scorer != 0){
        // Each new generation has got brand new individuals with random genes
        initiate(&queens_combination, ++id, 1, args.n_queens);
        evaluate(&queens_combination, 1, args.n_queens);
    }
    printf("Found solution after %d random iterations:\n", queens_combination.id);
    printf("\n");
    express_genes(queens_combination, args.n_queens);
}
