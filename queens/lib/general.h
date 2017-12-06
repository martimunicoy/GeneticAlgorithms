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
