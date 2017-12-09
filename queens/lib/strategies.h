/*****************************************************************************/
// Function headers
/*****************************************************************************/
GAResults genetic_algorithm(Individual *population, Individual *nextpopulation,
                            Individual *best,
                            RouletteCompartments *genetic_roulette,
                            Individual *parent1, Individual *parent2,
                            Individual child, Individual *survivor, int id,
                            int n_deaths, struct Args args, FILE *fitness_file,
                            FILE *genes_file);
/*****************************************************************************/
