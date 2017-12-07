#ifndef FIT
#define FIT
    #define fit true
#endif

#ifndef UNFIT
#define UNFIT
    #define unfit false
#endif

#ifndef REPLACE
#define REPLACE
	#define replace true
#endif

#ifndef NOT_REPLACE
#define NOT_REPLACE
	#define not_replace false
#endif

#ifndef RANDOM_BOOL
#define RANDOM_BOOL
	#define random_bool arc4random_uniform(2)
#endif

#ifndef ARGS_NUM
	#define ARGS_NUM 16
#endif
