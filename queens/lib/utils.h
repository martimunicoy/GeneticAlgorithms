/*****************************************************************************/
// Define Structures
/*****************************************************************************/
typedef struct
{
    Individual *best;        /*Best individual, the one with the lowest score*/
    Individual *population;  /*Final population state*/
    int n_pop;               /*Population size*/
    int n_gen;               /*The number of generations that were performed*/
    unsigned char exit_code; /*Exit code to know the reason why GA finished*/
    int minutes;             /*GA running time in minuts*/
} GAResults;
/*****************************************************************************/
typedef struct
{
    float mean;         /*Mean of population scores*/
    float st_deviation; /*Standard deviation of population scores*/
} AnalysisResults;
/*****************************************************************************/


/*****************************************************************************/
// Function headers
/*****************************************************************************/
float random_number                 (float max);
/*****************************************************************************/
void shuffle                        (unsigned int * rows, int n_queens);
/*****************************************************************************/
int sum_down                        (int n);
/*****************************************************************************/
unsigned int absolute               (int value);
/*****************************************************************************/
int factorial                       (int m);
/*****************************************************************************/
void swap                           (unsigned int * vector, int i, int j);
/*****************************************************************************/
void swap_populations               (Individual **p1, Individual **p2);
/*****************************************************************************/
void permute                        (unsigned int ** permutations,
                                     unsigned int * vector, int start, int end,
                                     int *counter);
/*****************************************************************************/
bool compare                        (Individual *a, Individual*b,
                                     int n_queens);
/*****************************************************************************/
AnalysisResults population_analysis (Individual *population, int n_pop);
/*****************************************************************************/
void exit_code_parser               (unsigned char exit_code,
                                     char *exit_message);
/*****************************************************************************/
void print_summary                  (Individual *population, Individual *best,
                                     int n_pop, int n_gen, int minutes);
/*****************************************************************************/
void write_solution                  (GAResults ga_results, int n_queens,
                                     bool append);
/*****************************************************************************/
void print_results_all              (GAResults ga_results, int n_queens);
/*****************************************************************************/
void print_results                  (GAResults ga_results, int n_queens);
/*****************************************************************************/
void print_problem_description      (struct Args args);
/*****************************************************************************/
void translate_bool                 (bool bool_to_translate,
                                     char *bool_string);
/*****************************************************************************/
void print_program_name             ();
/*****************************************************************************/
void print_license_header           ();
/*****************************************************************************/
void print_configuration            (struct Args args);
/*****************************************************************************/
void print_GA_constants             (struct Args args);
/*****************************************************************************/
void print_GA_constants_all         (struct Args args);
/*****************************************************************************/
void print_strategy_info            (int strategy);
/*****************************************************************************/
void print_GA_starts                ();
/*****************************************************************************/
void print_GA_completed             ();
/*****************************************************************************/
void print_GA_input                 ();
/*****************************************************************************/
