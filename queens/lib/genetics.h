// Constants
// The higher, the more exploratory
const float FRACT_WEIGTH = 0.1;
// The higher, the more exploitatory
const float DENOM_POWER = 3;

// Define Structures
typedef struct
{
    unsigned int * rows;
} Genes;

typedef struct
{
    int id;
    Genes genes;
    unsigned int scorer;
    bool chosen;
} Individual;

typedef struct
{
    float delimiter;
    Individual *individual;
} RouletteCompartments;

//Functions
Genes initiate_genes(int n_queens)
{
    Genes genes;
    genes.rows = (unsigned int *) malloc(sizeof(unsigned int) * n_queens);
    return genes;
}

Genes random_genes(int n_queens)
{
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
      Population: array of individuals  (pointer to the first individual)
      ?id: last individual id not already used (id = id_lastused + 1)??
      n_pop: number of individuals of the Population
      n_queens: number of queens (dimension of the chess table)
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
{   /*
    Print the fenotype of the individual, which is a particular
    chessboard (8x8) configuration of 8 queens.
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
    printf("   ");
    if (n_queens > 26)
    {
        for (col = 0; col < n_queens; col++)
            printf(" %d", (int) col/26+1);
        printf("\n");
    }
}

bool diagonal(unsigned int column1, unsigned int row1, unsigned int column2, unsigned int row2)
{
    /*
    Given the position (col, row) of two queens, returns wheter they meet in a diagonal or not.
    It works due to pitagoras theorem, and since we work with a squared chessboard.
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
     The smallest the scorer of an individual it gets, the better it is.
    */

     /*
     Improvements:

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
    RouletteCompartments *genetic_roulette = (RouletteCompartments *) malloc(sizeof(RouletteCompartments) * n_pop);
    return genetic_roulette;
}

float initiate_roulette(Individual *population, RouletteCompartments *genetic_roulette, int n_pop, int n_queens, bool fitness)
{
    int i;
    float sum = 0;
    Individual *competitor;
    if(fitness == fit)
    {
        for(i = 0; i < n_pop; ++i)
        {
            competitor = &population[i];
            if(!competitor->chosen)
                sum += 1 / pow((competitor->scorer + FRACT_WEIGTH), DENOM_POWER);
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
            sum += 1 / pow(sum_down(n_queens) - competitor->scorer + FRACT_WEIGTH, DENOM_POWER);
            genetic_roulette[i].delimiter = sum;
            genetic_roulette[i].individual = competitor;
        }
    }
    return sum;
}

Individual selection(Individual *population, RouletteCompartments *genetic_roulette, int n_pop, int n_queens, bool fitness)
{
    /*
     Given a Population of individuals, initiates a roulette and returns the selected individual
    */
    float max_delimiter, random;

    max_delimiter = initiate_roulette(population, genetic_roulette, n_pop, n_queens, fitness);
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

    return *genetic_roulette[choice].individual;
}

void reset_selection(Individual *population, int n_pop)
{
    int i;
    /*!!! To check: is the input array population modified outside the function?*/
    for(i = 0; i < n_pop; ++i)
        population[i].chosen = false;
}

Individual ordered_crossover(Individual parent1, Individual parent2, int id, int n_queens)
{
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

Individual * find_best(Individual *population, int n_pop)
{
    int i;
    Individual * best = &population[0];

    for (i = 1; i < n_pop; i++)
        if (population[i].scorer < best->scorer) best = &population[i];

    return best;
}

Individual heuristic_mutation(Individual mutant, int n_queens, int lambda, float p_mut)
{
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
    int i, j;
    printf("\nGeneration %d\n\nIndividual id\tGenes\t\t\tScorer\n", n_gen);
    for(i = 0; i < n_pop; ++i)
    {
        printf("\t%d\t(%d", population[i].id, population[i].genes.rows[0]);
        for(j = 1; j < n_queens; ++j)
            printf(",%d", population[i].genes.rows[j]);
        printf(")\t%d\n", population[i].scorer);
    }
}

void summarize(Individual *population, Individual *best, int n_gen, int n_queens)
{
    int i;
    float mean, st_deviation, sum = 0, sum_of_squares = 0;

    for (i = 0; i < n_queens; i++)
        sum += population[i].scorer;

    mean = sum / n_queens;

    for (i = 0; i < n_queens; i++)
        sum_of_squares += pow(population[i].scorer - mean, 2);

    st_deviation = sqrt(sum_of_squares/(n_queens-1));

    print_summary(n_gen, mean, st_deviation, best->scorer);
}

void write_fitness(FILE ** file, char * filename, Individual * population, int n_pop, int generation)
{
    *file = fopen(filename, "a");

    if (*file == NULL)
    {
        printf("Error changing to append 'a' file!\n");
        exit(1);
    }

    fprintf(*file, "%d,", generation);

    for(int i = 0;i < n_pop;i++)
    {
        if(i<n_pop-1)
            fprintf(*file, "%u,", population[i].scorer);
        else
            fprintf(*file, "%u\n", population[i].scorer);
    }

    fclose(*file);
}
