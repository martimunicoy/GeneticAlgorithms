/*****************************************************************************/
// Define Structures
/*****************************************************************************/
typedef struct
{   /* Given a column j of a NxN chessboard, rows[j] is the row
       where we have a queen, i.e., we have a queen at each point
       (column, row) = (j, rows[j]), j = 0,...,N-1
    */
    unsigned int * rows;
} Genes;
/*****************************************************************************/
typedef struct
{
    int id; /* Id of the individual, it is thought to be unique among any other individual.
               The idea is to consider unique id's during a whole run of the GA algorithm.
            */
    Genes genes; /* Genes of the individual */
    unsigned int scorer; /* The fitness of the individual */
    bool chosen; /* Boolean to check if the individual has been chosen in some selection procedure*/
} Individual;
/*****************************************************************************/
typedef struct
{
    float delimiter; /*@TODO  */
    Individual *individual;
} RouletteCompartments;
/*****************************************************************************/


/*****************************************************************************/
//Function headers
/*****************************************************************************/
Genes initiate_genes                  (int n_queens);
/*****************************************************************************/
Genes random_genes                    (int n_queens);
/*****************************************************************************/
void initiate                         (Individual *population, int id,
                                       int n_pop, int n_queens);
/*****************************************************************************/
void express_genes                    (Individual individual, int n_queens);
/*****************************************************************************/
bool diagonal                         (unsigned int column1, unsigned int row1,
                                       unsigned int column2,
                                       unsigned int row2);
/*****************************************************************************/
void evaluate                         (Individual *population, int n_pop,
                                       int n_queens);
/*****************************************************************************/
RouletteCompartments *malloc_roulette (int n_pop);
/*****************************************************************************/
float initiate_roulette               (Individual *population,
                                       RouletteCompartments *genetic_roulette,
                                       int n_pop, int n_queens, float weight,
                                       float power, bool fitness);
/*****************************************************************************/
Individual *find_best                 (Individual *population, int n_pop);
/*****************************************************************************/
Individual *roulette_selection        (Individual *population,
                                       RouletteCompartments *genetic_roulette,
                                       int n_pop, int n_queens, float weight,
                                       float power, bool fitness);
/*****************************************************************************/
Individual *tournament_selection      (Individual *population, int n_pop,
                                       int k_selections, bool replacement);
/*****************************************************************************/
void reset_selection                  (Individual *population, int n_pop);
/*****************************************************************************/
Individual ordered_crossover         (Individual *parent1, Individual *parent2,
                                      int id, int n_queens);
/*****************************************************************************/
void swapping_mutation                (Individual *mutant, int n_queens,
                                       float p_mut);
/*****************************************************************************/
void copy_individual                  (Individual *original, Individual *copy,
                                       int n_queens);
/*****************************************************************************/
void heuristic_mutation               (Individual *mutant,
                                       unsigned int **permutations,
                                       Individual *childs, int n_queens,
                                       int lambda, int n_perms, float p_mut);
/*****************************************************************************/
void view_population                  (Individual *population, int n_pop,
                                       int n_queens, int n_gen);
/*****************************************************************************/
void write_fitness                    (FILE ** file, char * filename,
                                       Individual *population, int n_pop,
                                       int generation);
/*****************************************************************************/
