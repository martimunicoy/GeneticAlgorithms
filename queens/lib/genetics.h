// Define Structures
typedef struct
{   /* Given a column j of a NxN chessboard, rows[j] is the row
       where we have a queen, i.e., we have a queen at each point
       (column, row) = (j, rows[j]), j = 0,...,N-1
    */
    unsigned int * rows;
} Genes;

typedef struct
{
    int id; /* Id of the individual, it is thought to be unique among any other individual.
               The idea is to consider unique id's during a whole run of the GA algorithm.
            */
    Genes genes; /* Genes of the individual */
    unsigned int scorer; /* The fitness of the individual */
    bool chosen; /* Boolean to check if the individual has been chosen in some selection procedure*/
} Individual;

typedef struct
{
    float delimiter; /*@TODO  */
    Individual *individual;
} RouletteCompartments;

//Functions
Genes initiate_genes(int n_queens)
{
     /*
     Returns a Genes struct variable after reserving memory for it.
    */

    Genes genes;
    genes.rows = (unsigned int *) malloc(sizeof(unsigned int) * n_queens);
    return genes;
}

Genes random_genes(int n_queens)
{
    /*
     Initialises a Genes variable with rows (1,..., n_queens),
     shuffles it to obrain a random permutation of it and returns
     the obtained permutation. This assures there is one unique
     queen for each column (and each row).
    */

    Genes genes = initiate_genes(n_queens);
    unsigned int i;
    for (i = 1; i <= n_queens; i++){
        genes.rows[i - 1] = i;
    }
    shuffle(&genes.rows[0], n_queens);
    return genes;
}

void initiate(Individual *population, int id, int n_pop, int n_queens)
{
    /*
      Initialises a population of individuals.

      population: array of individuals (pointer to the first individual)
      id: the last id number available (id = id_lastused + 1)
      n_pop: number of individuals of the population
      n_queens: number of queens (dimension of the chessboard)
    */

    int sumdown = sum_down(n_queens);

    for (int i = 0; i < n_pop; i++)
    {   //Choosing random genes for the i-th individual
        Genes genes = random_genes(n_queens);
        //Initialisation of the i-th individual
        Individual individual = {id, genes, sumdown, false};
        population[i] = individual;
        ++id;
    }
}

void express_genes(Individual individual, int n_queens)
{
    /*
    Prints the fenotype of the individual, which is a particular
    chessboard (n_queens x n_queens) configuration of n_queens queens.
    */

    int row, col, index;
    for (row = n_queens; row > 0; row--)
    {
        printf("%3d ", row);
        for(col = 0; col < n_queens; col++)
        {
            if (row == individual.genes.rows[col]) printf("X ");
            else printf(". ");
        }
        printf("\n");
    }
    printf("   ");
    for (col = 0; col < n_queens; col++)
    {
        index = col;
        while(index > 25) index -= 26;
        printf(" %c", ALPHABET[index]);
    }
    printf("\n");
    if (n_queens > 26)
    {
        printf("   ");
        for (col = 0; col < n_queens; col++)
            printf(" %d", (int) col/26+1);
        printf("\n");
    }
    printf("\n");
}

bool diagonal(unsigned int column1, unsigned int row1, unsigned int column2, unsigned int row2)
{
    /*
    Given the position (col, row) of two queens, returns whether they meet in a diagonal or not.
    It works since we work with a squared chessboard and the diagonals have slope = 1. Thus,
    Two queens meet if and only if they form the hipotenuse of a rectangle triangle with equal catetus:
    */

    unsigned int diff1, diff2;
    diff1 = absolute(column1 - column2);
    diff2 = absolute(row1 - row2);
    if(diff1 == diff2)
        return true;
    return false;
}

void evaluate(Individual *population, int n_pop, int n_queens)
{
    /*
     Given a input population of size n_pop initialises the scorer (fitness)
     of each individual. The default scorer is 1+...+n_queens = sum_down(n_queens)
     since it is the case where all queens are situated in a main diagonal and each
     one meets with all the others.

     If the individual scorer is equal to the default scorer, then it is counted the
     number of (unique) pairs of queens that meet and uptdate the scorer of that individual.

     The smallest the scorer of an individual it gets, the better it is.
    */

    /*
     @Improvements:

     - I would do an additional function to perform the loop in j and k
     that, given a the an individual, returns the number of pairs of queens that meet in a diagonal.
     Use the notation like diagonal_meets(Individual individual){ col1,row1,col2,row2; }
     then do scorer += diagonal_meets(Population[i]);

     - Not allow that an individual has repeated columns in different rows, so that
     in this function the scorer+= sum_down() is not needed
    */

    int i, j, k, row;
    unsigned int scorer;
    unsigned int initial_scorer = sum_down(n_queens);
    for(i = 0; i < n_pop; ++i)
    {
        if(population[i].scorer != initial_scorer)
            continue;
        else
        {
            scorer = 0;
            for(j = 0; j < n_queens; j++)
            {
                row = population[i].genes.rows[j];
                //start from j+1 to not compare to itself and not to repeat a pair of individuals
                for(k = j + 1; k < n_queens; k++)
                    if(diagonal(row, j+1, population[i].genes.rows[k], k+1))
                        ++scorer;
            }
            population[i].scorer = scorer;
        }
    }
}

RouletteCompartments *malloc_roulette(int n_pop)
{
    /*
     Reserves memory for a RouletteCompartments struct (a wheel roulette) and returns it
    */
    RouletteCompartments *genetic_roulette = (RouletteCompartments *) malloc(sizeof(RouletteCompartments) * n_pop);
    return genetic_roulette;
}

float initiate_roulette(Individual *population, RouletteCompartments *genetic_roulette, int n_pop, int n_queens, float weight, float power, bool fitness)
{
    /*
     @TODO
    */

    int i;
    float sum = 0;
    Individual *competitor;

    if(fitness == fit)
    {
        for(i = 0; i < n_pop; ++i)
        {
            competitor = &population[i];
            if(!competitor->chosen)
                sum += 1 / pow((competitor->scorer + weight), power);
            genetic_roulette[i].delimiter = sum;
            genetic_roulette[i].individual = competitor;
        }
    }

    if(fitness == unfit)
    {
        for(i = 0; i < n_pop; ++i)
        {
            competitor = &population[i];
            if(competitor->chosen)
                continue;
            sum += 1 / pow(sum_down(n_queens) - competitor->scorer + weight, power);
            genetic_roulette[i].delimiter = sum;
            genetic_roulette[i].individual = competitor;
        }
    }
    return sum;
}

Individual * find_best(Individual *population, int n_pop)
{
    /*
     Given a population of n_pop individuals, finds the FIRST with
     the best scorer and returns it.

     @IMPROVE: choose a random individual among all 'best' individuals
    */

    int i;
    Individual * best = &population[0];

    for (i = 1; i < n_pop; i++)
        if (population[i].scorer < best->scorer) best = &population[i];

    return best;
}

Individual roulette_selection(Individual *population, RouletteCompartments *genetic_roulette, int n_pop, int n_queens, float weight, float power, bool fitness)
{
    /*
     Given a population of n_pop individuals, initiates a roulette and returns the selected individual

     genetic_roulette: an empty RouletteCompartments object, with memory already reserved.
     @weight:
     @power:
     @fitness:
    */

    float max_delimiter, random;

    max_delimiter = initiate_roulette(population, genetic_roulette, n_pop, n_queens, weight, power, fitness);
    random = random_number(max_delimiter);

    int choice = 0;

    if(max_delimiter == 0)
    {
        printf("Error!\n");
        exit(0);
    }

    while(genetic_roulette[choice].delimiter < random)
        ++choice;

    genetic_roulette[choice].individual->chosen = true;

    //view_selection(genetic_roulette, n_pop, random, choice);

    return * genetic_roulette[choice].individual;
}

Individual tournament_selection(Individual *population, int n_pop, int k_selections, bool replacement)
{
    /*
      Selects k_selections individuals at random from a population and returns the fittest one

      @IMPROVE: add the possibility do choose if the selections are with replacement or not
      (i.e., if we mark an individual as chosen or not?)
    */

    int k;
    int random_position;
    Individual * selected_individuals = (Individual *) malloc(sizeof(Individual) * k_selections);
    Individual * best_selected_individual;

    for (k = 0;  k < k_selections;){
        random_position = (int) random_number(n_pop);
        if (replacement)
        {
            if (!population[random_position].chosen){
                population[random_position].chosen = true;
                selected_individuals[k] = population[random_position];
                k++;
            }
        }
        else
        {
            selected_individuals[k] = population[random_position];
            k++;
        }
    }

    best_selected_individual = find_best(selected_individuals, k_selections);

    return * best_selected_individual;
}

void reset_selection(Individual *population, int n_pop)
{
    /*
     Resets the variable 'chosen' of each individual of the input population
     to false.
    */

    int i;
    /*@tocheck: is the input array population modified outside the function?*/
    for(i = 0; i < n_pop; ++i)
        population[i].chosen = false;
}

Individual ordered_crossover(Individual parent1, Individual parent2, int id, int n_queens)
{
    /*
     Givne two parents, parent1 and parent2, this function performs the classical OX corssover
     algorithm to obtain only ONE child by means of the genes of both parents.

     Procedure: OX
        1. Select a substring from the genes.rows of a parent at random.
        2. Produce a proto-child by copying the substring into the
        corresponding position of it, now in the genes.rows of the proto-child.
        3. Delete the rows which are already in the substring from the 2nd
        parent. The resulted sequence of gene.rows after the deletion,
        contains the rows that the proto-child needs.
        4. Place the rows that the proto-child needs into the unfixed positions
        of the proto-child.genes.rows from left to right according to the order of the sequence
        to produce an offspring.
    */

    int i, j = 0, k, tmp;
    Genes genes = initiate_genes(n_queens);
    unsigned int row;
    bool missing;

    int random1 = arc4random_uniform(n_queens);
    int random2 = arc4random_uniform(n_queens);

    if (random2 < random1){
        tmp = random1;
        random1 = random2;
        random2 = tmp;
    }
    //printf("Parent1: %d    Parent2: %d    Subset: (%d-%d)\n", parent1.id, parent2.id, random1, random2);

    // Copy rows from parent1 to child. Set rest of rows equal to 0.
    for (i = 0; i < n_queens; i++)
    {
        if (i >= random1 && i <= random2) genes.rows[i] = parent1.genes.rows[i];
        else genes.rows[i] = 0;
    }

    // Ordered copy of the rows from parent2 to child.
    for (i = 0; i < n_queens; i++)
    {
        if (i < random1 || i > random2){
            for (; j < n_queens; j++){
                row = parent2.genes.rows[j];
                missing = true;
                for (k = 0; k < n_queens; k++){
                    if (genes.rows[k] == row)
                        {
                            missing = false;
                            break;
                        }
                }
                if (missing){
                    genes.rows[i] = row;
                    break;
                }
            }
        }
    }

    Individual child = {id, genes, sum_down(n_queens), false};
    return child;
}

Individual heuristic_mutation(Individual mutant, int n_queens, int lambda, float p_mut)
{
    /*
     Given an input individual 'mutant', a probability p_mut of mutation
     and an integer lambda, if a generated random number between 0 and 1
     is smaller than p_mut, then the mutant individual will mutate as follows:

     Procedure: Heuristic Mutation.
        1. Pick up lambda genes (from mutant.genes.rows) at random.
        2. Generate neighbors according to all possible permutations of the
        selected gens.
        3. Evaluate all neighbors and select the best one as offspring.
     The best selected is returned.
    */

    float random = random_number(1);
    int i, j, k, n_perms, cols_to_mutate[lambda], rows_to_mutate[lambda];

    if(random < p_mut)
    {
        for (i = 0; i < lambda; i++)
        {
            cols_to_mutate[i] = (int) (random_number(n_queens));
            rows_to_mutate[i] = mutant.genes.rows[cols_to_mutate[i]];
            for (j = 0; j < i; j++)
                if (rows_to_mutate[i] == rows_to_mutate[j]) i--;
        }

        n_perms = factorial(lambda);
        int ** permutations = (int **) malloc(n_perms * sizeof(int *));
        for(j = 0; j < n_perms; j++)
            permutations[j] = (int *) malloc(lambda * sizeof(int));

        int counter = 0;
        permute(permutations, rows_to_mutate, 0,lambda, &counter);

        Individual * childs = (Individual *) malloc(sizeof(Individual) * n_perms);
        bool mutation;
        int m;
        for (i = 0; i < n_perms; i++)
        {
            childs[i] = mutant;
            m = 0;
            for (j = 0; j < n_queens; j++)
            {
                mutation = false;
                for (k = 0; k < lambda; k++)
                    if (j == cols_to_mutate[k]) mutation = true;
                if (mutation) {
                    childs[i].genes.rows[j] = permutations[i][m];
                    m++;
                }
            }
        }
        evaluate(childs, n_perms, n_queens);
        mutant = *find_best(childs, n_perms);
    }
    return mutant;
}

void view_population(Individual *population, int n_pop, int n_queens, int n_gen)
{
    /*
     Given a population of n_pop individuals and its generation,
     prints out onto the screen the genes and the scorer (fitness) of
     each of its individuals, line by line.
    */

    int i, j;
    printf("\nGeneration %d\n\nIndividual id\tGenes\t\t\tScorer\n", n_gen);
    for (i = 0; i < n_pop; ++i)
    {
        printf("\t%d\t(%d", population[i].id, population[i].genes.rows[0]);
        for (j = 1; j < n_queens; ++j)
            printf(",%d", population[i].genes.rows[j]);
        printf(")\t%d\n", population[i].scorer);
    }
}

void summarize(Individual *population, Individual *best, int n_gen, int n_pop)
{
    /*
     @TODO
    */

    int i;
    float mean, st_deviation, sum = 0, sum_of_squares = 0;

    for (i = 0; i < n_pop; i++)
        sum += population[i].scorer;

    mean = sum / n_pop;

    for (i = 0; i < n_pop; i++)
        sum_of_squares += pow(population[i].scorer - mean, 2);

    st_deviation = sqrt(sum_of_squares/(n_pop-1));

    print_summary(n_gen, mean, st_deviation, best->scorer);
}

void write_fitness(FILE ** file, char * filename, Individual * population, int n_pop, int generation)
{
    /*
     Given a pointer to file and a file name, appends into a file the scorer
     of each individual of the input population, one by one and separated by commas.
     In the first position it is printed the generation of the input population.

     By calling this function after sucessive generations of individuals are created,
     we can obtain a file whose rows are the fitnesses of the corresponding individuals
     for each generation.
    */

    *file = fopen(filename, "a");

    if (*file == NULL)
    {
        printf("Error changing to append 'a' file!\n");
        exit(1);
    }

    fprintf(*file, "%d,", generation);

    for (int i = 0; i < n_pop; i++)
    {
        if (i < n_pop-1)
            fprintf(*file, "%u,", population[i].scorer);
        else
            fprintf(*file, "%u\n", population[i].scorer);
    }

    fclose(*file);
}
