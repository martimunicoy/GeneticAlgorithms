struct Args{
    int n_queens;
    int n_population;
    int n_generations;
    float death_ratio;
    float p_mutation;
    int lambda;
    bool force_to_continue;
    bool infinite_generations;
    bool write_fitness;
    int max_fitness_points;
    int summarize_freq;
    int tournament_selections;
    float fract_weight;
    float denom_power;
    int strategy;
    int sieve;
    bool write_genes;
    int max_genes_points;
    char fitness_dir[100];
    char genes_dir[100];
};

//Function headers
bool starts_with(const char *string, const char *prefix);
struct Args args_initializer();
struct Args check_arguments(struct Args arguments);
bool atob(char * subline);
struct Args line_parser(char * subline1, char * subline2, struct Args arguments);
struct Args args_from_file(struct Args arguments, char file_dir[50]);
struct Args args_parser(int argc, char *argv[]);
