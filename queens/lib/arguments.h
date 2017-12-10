/*****************************************************************************/
// Define Structures
/*****************************************************************************/
struct Args{
    // Flag -q
    int n_queens;              /*Number of queens*/

    // Flag -p
    int n_population;          /*Population size*/

    // Flag -g
    int n_generations;         /*Number of generations*/

    // Flag -d
    float death_ratio;         /*Death ratio per generation*/

    // Flag -m
    float p_mutation;          /*Probability of mutation*/

    // Flag -l
    int lambda;                /*Heuristic Mutation only: genes to mutate*/

    // Flag -c
    bool force_to_continue;    /*Continue after finding a solution*/

    // Flag -i
    bool infinite_generations; /*Infinite generations until finding solution*/

    // Flag -r
    bool write_fitness;        /*Write fitness data to a file*/

    // Flag -x
    int max_fitness_points;    /*Maximum points to write in fitness data file*/

    // Flag -s
    int summarize_freq;        /*Frequency to summarize*/

    // Flag -t
    int tournament_selections; /*Tournament Selection only: selection number*/

    // Flag -w
    float fract_weight;        /*Roulette Selection only: the higher, the
                                 higher, the more exploratory*/
    // Flag -e
    float denom_power;         /*Roulette Selection only: the higher, the most
                                 exploitatory*/
    // Flag -y
    int strategy;              /*Set the Genetic Algorithm strategy to apply*/

    // Flag -v
    int sieve;                 /*allqueens_GA only: set the sieve to apply*/

    // Flag -n
    bool write_genes;          /*Maximum points to write in genes output file*/

    // Flag -a
    int max_genes_points;      /*Maximum points to write in genes output file*/

    // Flag -b
    char fitness_dir[100];     /*Directory for the fitness data output*/

    // Flag -k
    char genes_dir[100];       /*Directory for the genes data  output*/
};
/*****************************************************************************/


/*****************************************************************************/
//Function headers
/*****************************************************************************/
bool starts_with             (const char *string, const char *prefix);
/*****************************************************************************/
struct Args args_initializer ();
/*****************************************************************************/
struct Args check_arguments  (struct Args arguments);
/*****************************************************************************/
bool atob                    (char * subline);
/*****************************************************************************/
struct Args line_parser      (char * subline1, char * subline2,
                              struct Args arguments);
/*****************************************************************************/
struct Args args_from_file   (struct Args arguments, char file_dir[50]);
/*****************************************************************************/
struct Args args_parser      (int argc, char *argv[]);
/*****************************************************************************/
