// Function headers
float random_number(float max);
void shuffle(unsigned int * rows, int n_queens);
int sum_down(int n);
unsigned int absolute(int value);
int factorial(int m);
void swap(int * vector, int i, int j);
void permute(int ** permutations, int * vector, int start, int end, int *counter);
void print_summary(int n_gen, float mean, float st_deviation, int best_score);
bool print_results(unsigned int scorer);

//Function bodies
float random_number(float max)
{
    /*
    Returns a random float number between 0 and max
    */

    float random;
    random = (arc4random_uniform(UINT16_MAX))/ ((float)(UINT16_MAX)) * max;
    return random;
}

void shuffle(unsigned int * rows, int n_queens)
{
    /*
    Arrange the 'n_queens' elements of the array 'rows' in random order.    
    Reference: https://stackoverflow.com/questions/6127503/shuffle-array-in-c
    size_t is a type guaranteed to hold any array index
    */

    int i, j;
    unsigned int tmp;

    for (i = n_queens-1; i >= 0; i--)
    {
        j = (unsigned int) random_number(n_queens);
        tmp = *(rows + i);
        *(rows + i) = *(rows + j);
        *(rows + j) = tmp;
    }
}

int sum_down(int n)
{
    /*
    Returns the value of the sum 1+2+3+...+n
    */
    return n*(n+1)/2;
}

unsigned int absolute(int value)
{   
    /*
    Returns the absolute value of an integer
    */

    if(value < 0)
        return -value;
    return value;
}

int factorial(int m)
{
    /*
     Recursive function that return the value of m!
     (factorial of m).
    */
    if(m < 0){
        printf("\nFactorial of a negative number does not exist!\n");
        exit(0);
    }
    if(m >= 1) return m * factorial(m-1);
    else return 1;
}

void swap(int * vector, int i, int j)
{   
    /*
     Given a vector and two positions of the vector, i and j,
     a swap operation between the vector components is performed:
         vector[i] <--> vector[j]
    */
    int temp;
    temp = vector[i];
    vector[i] = vector[j];
    vector[j] = temp;
}

void permute(int ** permutations, int * vector, int start, int end, int *counter)
{    
    /*
     Given an input vector, start = 0, end = length of the vector, a matrix 'permutations'
     and a pointer to integer 'counter' (outside of the scope of this function), successive calls
     to this function and the swap function, recurssively fills the rows of the matrix 'permutations' 
     with all the possible (end!) permutations of the input 'vector'.
    */

    int i, j;
    if (start == end)
    {
        for (j = 0; j < end; j++)
        {
            permutations[*counter][j] = vector[j];
        }
        ++(*counter);
        return;
    }
    else
    {
        for (i = start; i < end; i++)
        {
            swap(vector, start, i);
            permute(permutations, vector, start+1, end, counter);
            swap(vector, start, i);
        }
    }
    return;
}

void print_summary(int n_gen, float mean, float st_deviation, int best_score)
{
    /*
     @TODO
    */

    printf("\n");
    printf("+-------------------------------+\n");
    printf("|        GENETIC SUMMARY        |\n");
    printf("+-------------------------------+\n");
    printf("| Generation:            %6d |\n", n_gen);
    printf("| Mean score:             %3d.%d |\n", (int) mean, (int) (mean*10) - ((int) mean)*10);
    printf("| Standard deviation:     %3d.%d |\n", (int) st_deviation, (int) (st_deviation*10) - ((int) st_deviation)*10);
    printf("| Best score:            %6d |\n", best_score);
    printf("+-------------------------------+\n");
    printf("\n");
}

bool print_results(unsigned int scorer)
{   
    /*
     @TODO
    */

    printf("\n");
    printf("+-------------------------------+\n");
    printf("|            RESULTS            |\n");
    printf("+-------------------------------+\n");
    printf("\n");

    if(scorer != 0)
    {
        printf("\nNo optimal individual found.\n");
        printf("\n");
        return false;
    }
    else
        return true;
}
