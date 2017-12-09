/*****************************************************************************/
// Function headers
/*****************************************************************************/
GAResults genetic_algorithm(int strategy, Individual *population,
                            Individual *nextpopulation, Individual *best,
                            RouletteCompartments *genetic_roulette,
                            Individual *parent1, Individual *parent2,
                            Individual child, Individual *survivor, int id,
                            int n_deaths, struct Args args, FILE *fitness_file,
                            char *fitness_dir, FILE *genes_file,
                            char *genes_dir);
/*****************************************************************************/
