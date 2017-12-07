//Function headers
Individual * strategy1(Individual * population, Individual * nextpopulation,
                       Individual * best,
                       RouletteCompartments * genetic_roulette,
                       Individual parent1, Individual parent2,
                       Individual child, Individual survivor, int id,
                       int n_deaths, struct Args args, FILE * file,
                       char * file_fitness);
Individual * strategy2(Individual * population, Individual * nextpopulation,
                       Individual * best,
                       RouletteCompartments * genetic_roulette,
                       Individual parent1, Individual parent2,
                       Individual child, Individual survivor, int id,
                       int n_deaths, struct Args args, FILE * file,
                       char * file_fitness);
Individual * strategy3(Individual * population, Individual * nextpopulation,
                       Individual * best,
                       RouletteCompartments * genetic_roulette,
                       Individual parent1, Individual parent2,
                       Individual child, Individual survivor, int id,
                       int n_deaths, struct Args args, FILE * file,
                       char * file_fitness);
Individual * genetic_algorithm(int strategy, Individual * population,
                               Individual * nextpopulation, Individual * best,
                               RouletteCompartments * genetic_roulette,
                               Individual parent1, Individual parent2,
                               Individual child, Individual survivor, int id,
                               int n_deaths, struct Args args, FILE * file,
                               char * file_fitness);
