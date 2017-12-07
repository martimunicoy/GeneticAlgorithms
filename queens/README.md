# N Queens Problem Solver - Genetic Algorithm

The following program attempts to solve the so-called 8 Queens Problem in the general case of having N Queens by means of a genetic algorithm which is developed "ad-hoc".

## Problem description

*The eight queens problem or puzzle is the problem of placing eight chess queens on an 8×8 chessboard so that no two queens threaten each other. Thus, a solution requires that no two queens share the same row, column, or diagonal. The eight queens puzzle is an example of the more general n queens problem of placing n non-attacking queens on an n×n chessboard, for which solutions exist for all natural numbers n with the exception of n=2 and n=3*, [1].

*The problem can be quite computationally expensive, as there are 4,426,165,368 (i.e., 64C8) possible arrangements of eight queens on an 8×8 board, but only 92 solutions. It is possible to use shortcuts that reduce computational requirements or rules of thumb that avoids brute-force computational techniques. For example, by applying a simple rule that constrains each queen to a single column (or row), though still considered brute force, it is possible to reduce the number of possibilities to 16,777,216 (that is, 88) possible combinations. Generating permutations further reduces the possibilities to just 40,320 (that is, 8!), which are then checked for diagonal attacks.
Martin Richards published a program to count solutions to the n-queens problem using bitwise operations. However, this solution has already been published by Zongyan Qiu*, [1].

The approach we follow is based on genetic algorithms.

## Getting started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites
Depending on the native OS some external libraries will need to be included to run this program. See install section below.

This project supports the following C compiler versions:
* Apple gcc v4.2.1
* Ubuntu gcc v5.4.0

Other regular C compilers should work as well but have not been tested yet.

### Installing on OSX
On the main folder of the project call the compiler to create the executable.

```
gcc src/queens_GA.c src/constants.c src/genetics.c src/utils.c src/arguments.c src/strategies.c -lm -o queens_GA.out
```

It will compile the source files and it will build the executable _queens_GA.out_.

### Installing on Linux
On the main folder of the project call the compiler to create the executable.

```
gcc src/queens_GA.c src/constants.c src/genetics.c src/utils.c src/arguments.c src/strategies.c -lm -o queens_GA.out
```

For non-GNU Linux systems the previous command will complain about a missing library (_stdlib.h_). Then, this library needs to be manually installed by means of the following command:
```
sudo apt-get update
sudo apt-get install libbsd-dev
```

After its installation, the compiler should work fine by looking for it at _bsd/stdlib.h_. Run again the gcc command. Be aware of the gcc flag _-D LINUX_ that looks for this new _bsd/stdlib.h_ library.

```
gcc -D LINUX src/queens_GA.c src/constants.c src/genetics.c src/utils.c src/arguments.c src/strategies.c -lm -lbsd -o queens_GA.out
```

### Installing with Make
It is also possible to compile the C Program by using _make_. Just go to the main folder of the project and enter the following command:

```
make
```

In case that your OS does not come with _stdlib.h_ you will get the following error while compiling:

```
./lib/queens_GA.h:3:15: fatal error: 'bsd/stdlib.h' file not found
```

Then, you will need to install this missing library and execute _make_ again. You can find more information about how to install this missing library in the Installing on Linux section.

## Test running
To see if the executable was properly built, a quick test can be run. On the same main folder of the project run the executable _queens_GA.out_ by using the next command:

```
./queens_GA.out
```

A solution for the 8 Queens Problem should be displayed in the terminal.

Feel free to play with it by tunning the Genetic Algorithm with the command-line arguments that are described in the flags section from below. You can also solve a more general problem made up of N Queens.

Have fun!

## Flags
A list of all the available flags is found below with a brief description of their use.

## Authors
* **Martí Municoy**, martimunicoy@gmail.com
* **Dani Salgado**, danysalgado14@gmail.com

## References
[1] 8 queens problem, general information. https://en.wikipedia.org/wiki/Eight_queens_puzzle .

## License
This project is licensed under the GNU License - see the [LICENSE.txt](LICENSE.txt) file for details
