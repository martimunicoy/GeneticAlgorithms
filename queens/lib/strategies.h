/*****************************************************************************/
// Function headers
/*****************************************************************************/
GAResults strategy1(Individual * population, Individual * nextpopulation,
                    Individual * best,
                    RouletteCompartments * genetic_roulette,
                    Individual parent1, Individual parent2,
                    Individual child, Individual survivor, int id,
                    int n_deaths, struct Args args, FILE * file,
                    char * file_fitness);
/*****************************************************************************/
GAResults strategy2(Individual * population, Individual * nextpopulation,
                    Individual * best,
                    RouletteCompartments * genetic_roulette,
                    Individual parent1, Individual parent2,
                    Individual child, Individual survivor, int id,
                    int n_deaths, struct Args args, FILE * file,
                    char * file_fitness);
/*****************************************************************************/
GAResults strategy3(Individual * population, Individual * nextpopulation,
                    Individual * best,
                    RouletteCompartments * genetic_roulette,
                    Individual parent1, Individual parent2,
                    Individual child, Individual survivor, int id,
                    int n_deaths, struct Args args, FILE * file,
                    char * file_fitness);
/*****************************************************************************/
GAResults genetic_algorithm(int strategy, Individual * population,
                            Individual * nextpopulation, Individual * best,
                            RouletteCompartments * genetic_roulette,
                            Individual parent1, Individual parent2,
                            Individual child, Individual survivor, int id,
                            int n_deaths, struct Args args, FILE * file,
                            char * file_fitness);
/*****************************************************************************/
