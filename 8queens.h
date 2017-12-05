// Include Libraries
#include <stdio.h>
#include <bsd/stdlib.h>

#include <math.h>
#include <stdbool.h>
#include <limits.h>

// Definitions
#define fit 1
#define unfit 0
//#define Individual struct Individual;
//#define Genes struct Genes;
//#define RouletteCompartments struct RouletteCompartments;
#define random_bool arc4random_uniform(2)

// Constants
// Smallest probability for the worst individual to survive
// The higher, the more exploratory
const float FRACT_WEIGTH = 0.01;
// The higher, the more exploitatory
const float DENOM_POWER = 1;

// Define Structures
typedef struct
{   //maybe it could be unsigned char
    char column[8]; 
} Genes;

typedef struct
{
    int id;
    Genes genes;
    unsigned char scorer;
    bool chosen;
} Individual;

typedef struct //it would be RouletteCompartment (in singular?) since individual is here the adres of memory
//of only one individual
{
    float delimiter;
    Individual *individual;
} RouletteCompartments;

//Functions
Genes _random_genes(int n_queens)
{   
    //Improvement: modify the function so that there are not repeated columns?
    Genes genes;
    unsigned char random;
    int i;
    for (i = 0; i < 8; ++i){
        arc4random_buf(&random, sizeof random);
        genes.column[i] = random / 256. * n_queens; //we can change 256 by sizeof(random) ?
    }
    return genes;
}

/* Arrange the N elements of ARRAY in random order.
   Only effective if N is much smaller than RAND_MAX;
   if this may not be the case, use a better random
   number generator. 
   Source: https://stackoverflow.com/questions/6127503/shuffle-array-in-c
   size_t is a type guaranteed to hold any array index
   */

void PrintVector(int * v, int n){
  printf("\n( ");
  for(int i = 0; i <n;i++){
    printf("%d, ", v[i]);
  }
  printf(")\n");
}
   
void shuffle(char * array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          char t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}


Genes _random_genes_different(int n_queens)
{   
    Genes genes;
    char genes_col[] = {0,1,2,3,4,5,6,7};
    shuffle(genes_col, n_queens);
    /*unsigned char random;
    int i;
    for (i = 0; i < 8; ++i){
        arc4random_buf(&random, sizeof random);
        genes.column[i] = random / 256. * n_queens; //we can change 256 by sizeof(random) ?
    }*/
    for(int i = 0; i< n_queens;i++){
        genes.column[i] = genes_col[i];
    }

    return genes;
}


int sum_down(int n)
{    
    /*
    Returns the value of the sum 1+2+3+...+n
    */
    return n*(n+1)/2;
}

float random_number(float max)
{   
    /*
    Returns a random float number between 0 and max
    */
    float random;
    random = (arc4random_uniform(UINT16_MAX))/ ((float)(UINT16_MAX)) * max;
    return random;
}

//char random_int()

int initiate(Individual *Population, int id, int n_pop, int n_queens)
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
        Genes genes = _random_genes(n_queens);
        //Initialisation of the i-th individual
        Individual individual = {id, genes, sumdown, false};
        Population[i] = individual;
        ++id;
    }
    return id;
}

int initiate_different(Individual *Population, int id, int n_pop, int n_queens)
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
        Genes genes = _random_genes_different(n_queens);
        //Initialisation of the i-th individual
        Individual individual = {id, genes, sumdown, false};
        Population[i] = individual;
        ++id;
    }
    return id;
}

void check_random_uniformity(float max)
{
    float num;
    int N = 10000000;
    int n1, n2, n3, n4, n5, n6, n7, n8, n9, n10;
    float highest, lowest;
    highest = 0;
    lowest = max;
    n1 = n2 = n3 = n4 = n5 = n6 = n7 = n8 = n9 = n10 = 0;
    int div = max / 10;
    double sum = 0;
    int i;
    for(i=0; i<N; i++){
        num = random_number(max);
        sum += num;
        if(num < div) ++n1;
            else if(num < 2 * div) ++n2;
                else if(num < 3 * div) ++n3;
                    else if(num < 4 * div) ++n4;
                        else if(num < 5 * div) ++n5;
                            else if(num < 6 * div) ++n6;
                                else if(num < 7 * div) ++n7;
                                    else if(num < 8 * div) ++n8;
                                        else if(num < 9 * div) ++n9;
                                            else if(num < 10 * div) ++n10;
        if(num > highest) highest = num;
        if(num < lowest) lowest = num;
    }
    float result = sum / ((double) N);
    printf("%f\n", result);
    printf("n1=%f,n2=%f,n3=%f,n4=%f,n5=%f,n6=%f,n7=%f,n8=%f,n9=%f,n10=%f\n",n1/(float)N,n2/(float)N,n3/(float)N,n4/(float)N,n5/(float)N,n6/(float)N,n7/(float)N,n8/(float)N,n9/(float)N,n10/(float)N);
    printf("max=%f, min=%f\n", highest, lowest);
}

void check_random_uniformity2()
{
    unsigned char random_number;
    unsigned int num;
    int N = 10000000;
    long sum = 0;
    int i;
    for(i=0; i<N; i++){
        arc4random_buf(&random_number, sizeof(random_number));
        num = random_number / 256. * 8;
        sum += num;
    }
    float result = sum / ((float) N);
    printf("%f\n", result);
}

void express_genes(Individual individual)
{   /*
    Print the fenotype of the individual, which is a particular
    chessboard (8x8) configuration of 8 queens.
    */
    int i, j, column;
    for(i = 7; i >= 0; --i){
        printf("%d ", i + 1);
        column = individual.genes.column[i];
        for(j = 0; j < column; ++j)
            printf(". ");
        printf("X ");
        for(j = column + 1; j < 8; ++j)
            printf(". ");
        printf("\n");
    }
    printf("  A B C D E F G H\n");
}

char * sort(char array[8]){
    /*
    Improvements:
       - Do the algorithm for a N dimensional array (general)
       - This algorithm is o(n^2), use a more efficient one.
       - I think there is no need to copy the input array,
         instead do a void type function which modifies the input array
         since it is passed by reference (vale fals, he vist per a què s'utilitzava).
    */
    int i, j, t;
    static char sorted_array[8];
    for(i = 0; i < 8; ++i)
        sorted_array[i] = array[i];
    for(i = 0; i < 7; ++i)
        for(j = 0; j < 7; ++j)
        {
            if(sorted_array[j] > sorted_array[j+1])
            {
                t = sorted_array[j+1];
                sorted_array[j+1] = sorted_array[j];
                sorted_array[j] = t;
            }
        }
    return sorted_array;
}

int count_repetitions(char array[8]){
    /*
    !!!!! Això només mira repeticions entre i, i+1.??
    THIS ASSUMES THAT THE INPUT array is sorted in ASCENDENT order!
    */
    int i, current;
    int count = 0;
    char previous = array[0];
    for(i = 1; i < 8; ++i){
        current = array[i];
        if(current == previous)
            ++count;
        else
            previous = current;
    }
    return count;
}

unsigned char absolute(char value)
{   /*
    Returns the absolute value of a char
    */
    if(value < 0)
        return -value;
    return value;
}

bool diagonal(unsigned char column1, unsigned char row1, unsigned char column2, unsigned char row2)
{   
    /*
    Given the position (col, row) of two queens, returns wheter they meet in a diagonal or not.
    It works due to pitagoras theorem, and since we work with a squared chessboard.
    */
    unsigned char diff1, diff2;
    diff1 = absolute(column1 - column2);
    diff2 = absolute(row1 - row2);
    if(diff1==diff2)
        return true;
    return false;
}

void evaluate(Individual *Population, int n_pop, int n_queens)
{    
    /*
     The smaller the scorer of an individual, the better (?)     
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
    int i, j, k, column;
    unsigned char scorer;
    char *sorted_cols = (char *) malloc(sizeof(char) * 8);
    short *slopes = (short *) malloc(sizeof(short) * 8); //unused
    int sumdown = sum_down(n_queens);
    for(i = 0; i < n_pop; ++i)
    {
        if(Population[i].scorer != sumdown) //!!!!scorer is unsigned char [0,255], sum_down is int
            continue;
        else
        {
            scorer = 0;
            sorted_cols = sort(Population[i].genes.column);
            /*!!!!Dont understand yet, whi sum_down( of the repetitions)*/
            scorer += sum_down(count_repetitions(sorted_cols));
            /*j is the row of the i-th individual*/
            for(j = 0; j < 7; ++j)
            {
                column = Population[i].genes.column[j];
                //start from j+1 to not compare to itself and not to repeat a pair of individuals
                for(k = j + 1; k < 8; ++k)
                    if(diagonal(column, j, Population[i].genes.column[k], k))
                        ++scorer;
            }
            Population[i].scorer = scorer;
        }
    }
}

RouletteCompartments *malloc_roulette(int n_pop)
{
    RouletteCompartments *genetic_roulette = (RouletteCompartments *) malloc(sizeof(RouletteCompartments) * n_pop);
    return genetic_roulette;
}

float initiate_roulette(Individual *Population, RouletteCompartments *genetic_roulette, int n_pop, int n_queens, bool fitness)
{
    int i;
    float sum = 0;
    Individual *competitor;
    if(fitness == fit)
    {
        for(i = 0; i < n_pop; ++i)
        {
            competitor = &Population[i];
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
            competitor = &Population[i];
            if(competitor->chosen)
                continue;
            sum += 1 / pow(sum_down(n_queens) - competitor->scorer + FRACT_WEIGTH, DENOM_POWER);
            genetic_roulette[i].delimiter = sum;
            genetic_roulette[i].individual = competitor;
        }
    }
    return sum;
}

void view_selection(RouletteCompartments *genetic_roulette, int n_pop, float random, int selection)
{
    int i;

    if(selection == 0)
        printf("-->\t0: (0.000000-%f)\tChosen: %i\n", genetic_roulette[0].delimiter, genetic_roulette[0].individual->chosen);
    else
        printf("\t0: (0.000000-%f)\tChosen: %i\n", genetic_roulette[0].delimiter, genetic_roulette[0].individual->chosen);

    for(i=1;i<n_pop;++i){
        if(i==selection)
            printf("-->\t%d: (%f-%f)\tChosen: %i\n", i, genetic_roulette[i-1].delimiter, genetic_roulette[i].delimiter, genetic_roulette[i].individual->chosen);
        else
            printf("\t%d: (%f-%f)\tChosen: %i\n", i, genetic_roulette[i-1].delimiter, genetic_roulette[i].delimiter, genetic_roulette[i].individual->chosen);
    }

    printf("Random: %f\tSelected: %d (Scorer %d)\n", random, selection, genetic_roulette[selection].individual->scorer);
}

Individual _select(Individual *Population, RouletteCompartments *genetic_roulette, int n_pop, int n_queens, bool fitness)
{   
    /*
     Given a Population of individuals, initiates a roulette and returns the selected individual
    */
    float max_delimiter, random;

    max_delimiter = initiate_roulette(Population, genetic_roulette, n_pop, n_queens, fitness);
    random = random_number(max_delimiter);

    int selection = 0;

    if(max_delimiter == 0)
    {
        printf("Error!\n");
        exit(0);
    }

    while(genetic_roulette[selection].delimiter < random)
        ++selection;

    genetic_roulette[selection].individual->chosen = true;

    //view_selection(genetic_roulette, n_pop, random, selection);

    return *genetic_roulette[selection].individual;
}

void reset_selection(Individual *Population, int n_pop)
{
    int i;
    /*!!! To check: is the input array Population modified outside the function?*/
    for(i = 0; i < n_pop; ++i)
        Population[i].chosen = false;
}

Individual crossover(Individual parent1, Individual parent2, int id, int n_queens)
{   
    /*
     random_bool chooses randomly a 0 (parent1) or a 1 (parent 2)
    */
    int i;
    Genes genes;

    for(i = 0; i < n_queens; ++i)
    {
        if(random_bool)
            genes.column[i] = parent1.genes.column[i];
        else
            genes.column[i] = parent2.genes.column[i];
    }

    Individual child = {id, genes, sum_down(n_queens), false};

    return child;
}

Individual crossover2(Individual parent1, Individual parent2, int id, int n_queens)
{   
    /*
     Only valid for n_queens odd 
    */
    int i;
    Genes genes;
    Individual *p1 = &parent1;
    Individual *p2 = &parent2;

    if(random_bool)
    {
        p1 = &parent2;
        p2 = &parent1;
    }

    for(i = 0; i < n_queens/2; ++i)
        genes.column[i] = p1->genes.column[i];

    for(i = n_queens/2; i < n_queens; ++i)
        genes.column[i] = p1->genes.column[i]; //!!!! I think it must be p2->genes.column[i]

    Individual child = {id, genes, sum_down(n_queens), false};

    return child;
}

Individual mutation(Individual mutant, int n_queens, float p_mut)
{
    float random = random_number(1);
    unsigned char alteration, column;
    /* !!! quite strange */

    if(random < p_mut)
    {
        column = (unsigned char) arc4random_uniform(n_queens);
        alteration = (unsigned char) arc4random_uniform(n_queens);
        mutant.genes.column[column] = alteration;
        //mutant.id = 0;
        mutant = mutation(mutant, n_queens, p_mut);//???????
    }
    return mutant;
}

int Factorial(int m){
    if(m < 0){ printf("\nFactorial of a negative number does not exist!!\n");exit(0);}

    if(m>=1) return m*Factorial(m-1);
    else return 1;
}

void Swap(int * vector, int i, int j){
    int temp;
    temp = vector[i];
    vector[i] = vector[j];
    vector[j] = temp;
}


typedef struct {
    int ** array;
    int first_empty;

} Dinamic_Matrix;


void Add_VectorToMatrix(int * vector, int n, Dinamic_Matrix matrix, int row){
     //int row = matrix.first_empty;
     for(int i = 0; i<n;i++){
        matrix.array[row][i] = vector[i];
     }
     //matrix.first_empty =matrix.first_empty+1;
}

void Copy_Vector1ToVector2(int * vector1, int * vector2, int n){
     for(int i = 0; i<n;i++){
        vector2[i] = vector1[i];
     }
}

void Copy_Vector1ToVector2char(char * vector1, char * vector2, int n){
     for(int i = 0; i<n;i++){
        vector2[i] = vector1[i];
     }
}

void PrintMatrix(int ** matrix, int nrows, int ncols){
    for(int i = 0; i< nrows;i++){
        PrintVector(matrix[i],ncols);
    }

}

int COUNTER = 0;

void Permute(int *vector, int i,int n, Dinamic_Matrix matrix, int n_perms) { 
  if (n == i){
     matrix.first_empty = COUNTER;
     Add_VectorToMatrix(vector,n,matrix, matrix.first_empty);
     COUNTER++;
     //matrix.first_empty++;
     /*PrintVector(vector ,n );
     printf("first_empty = %d\n", matrix.first_empty);
     printf("first_empty = %d\n", counter);*/
     return;
  }
  int j;
  for (j = i; j < n; j++) { 
     Swap(vector,i,j);
     Permute(vector,i+1,n, matrix, n_perms);
     Swap(vector,i,j);
  }

  return;
}

/*
int ** Permutations(int * vector, int n){
       int n_perms
       int permutations[][]

}*/
Individual * find_best(Individual *Population, int n_pop){
    Individual *best = NULL;    
    for(int i=0; i<n_pop;i++){
        if(Population[i].scorer == 0) {
            best = &Population[i];
            break; }       
    }
    return best;
}


Individual heuristic_mutation(Individual mutant, int n_queens, float p_mut)
{
    //GLOBAL VARIABLE
    COUNTER = 0;

    float random = random_number(1);
    unsigned char alteration, column;
    /* !!! quite strange */
    int lambda = 3;
    int genes_to_mutate[lambda], positions_to_mutate[lambda]; 
    int n_perms;
    if(random < p_mut)
    {   
        printf("MUTACIO HEURISTICA \n\n");

        Individual * neighbors = (Individual *) malloc(lambda*sizeof(Individual));
        for(int i = 0; i< lambda;i++){
            positions_to_mutate[i] = (int) (random_number(n_queens));
            genes_to_mutate[i] = mutant.genes.column[positions_to_mutate[i]];
        }
        
        Dinamic_Matrix permutations;
        n_perms = Factorial(lambda);
        permutations.array = (int **) malloc(n_perms*sizeof(int *));
        for(int j = 0; j < n_perms; j++){
            permutations.array[j] = (int *) malloc(lambda*sizeof(int));
                                         }
        printf("Abans del permute \n\n");


        permutations.first_empty = 0;
        Permute(genes_to_mutate, 0,lambda, permutations, n_perms);
        printf("Despres del permute \n\n");
        
        for(int ind = 0; ind < n_perms;ind++){
            Copy_Vector1ToVector2char(mutant.genes.column, neighbors[ind].genes.column,n_queens);
            for(int k = 0; k <lambda; k++){
                neighbors[ind].genes.column[positions_to_mutate[k]] = permutations.array[ind][k];
            }
            //Copy_Vector1ToVector2(neighbors[k].genes  permutations[k]);
        }
        
        printf("Despres del for \n\n");

        Individual * best_neighbor;
        best_neighbor = find_best(neighbors, n_perms);
        //Copy_Vector1ToVector2(best_neighbor->genes.column ,mutant.genes.column, n_queens);
        //d
        
        //mutant.id = 0;
        //mutant = mutation(mutant, n_queens, p_mut);
    

        //free(neighbors);
        /*for(int j = 0; j < n_perms; j++) free(permutations.array[j]);
        free(permutations.array);*/
        //free(permutations);
    }

    return mutant;
}



void view_population(Individual *Population, int n_pop, int n_queens, int n_gen)
{
    int i, j;
    printf("\nGeneration %d\n\nIndividual id\tGenes\t\t\tScorer\n", n_gen);
    for(i = 0; i < n_pop; ++i)
    {
        printf("\t%d\t(%d", Population[i].id, Population[i].genes.column[0]);
        for(j = 1; j < n_queens; ++j)
            printf(",%d", Population[i].genes.column[j]);
        printf(")\t%d\n", Population[i].scorer);
    }
}

