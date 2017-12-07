// Include Libraries
#include "lib/general.h"
#include "lib/utils.h"
#include "lib/genetics.h"

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
