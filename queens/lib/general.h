// Include Libraries
#include <stdio.h>
#ifdef LINUX
    #include <bsd/stdlib.h>
#else
    #include <stdlib.h>
#endif
#include <stdbool.h>
#include <math.h>

// Definitions
#define fit 1
#define unfit 0
#define random_bool arc4random_uniform(2)

const char ALPHABET[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                           'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                           'U', 'V', 'W', 'X', 'Y', 'Z'};