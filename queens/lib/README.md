# C Libraries for the N queens problem

Currently it is important to preserve the following order when including the libraries in the 'main.c' of a program:

* #include "lib/general.h" (must be the first)
* #include "lib/utils.h" 
* #include "lib/genetics.h" (must be after utils.h)
* #include "lib/arguments.h"

This means that **general.h** includes general definitions and libraries that may be imprescindible for other libraries.
**utils.h** provides functions that are independent of the genetic algorithm, and thus independent of the functions in the **genetics.h** library.
The functions from **genetics.h** make use of some auxiliary functions coming from **utils.h**, and are functions particularized to the N-queens problem and its genetic algorithm approach; this library also includes particular structs for the problem.

## general.h

## utils.h

## genetics.h

## arguments.h

## test.h

## deprecated.h