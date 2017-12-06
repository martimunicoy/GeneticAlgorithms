# Genetic Algorithms

## Assignment
Solve the 8 queens problem by means of a genetic algorithm which has to be developed "ad-hoc".

## Problem description

*The eight queens problem or puzzle is the problem of placing eight chess queens on an 8×8 chessboard so that no two queens threaten each other. Thus, a solution requires that no two queens share the same row, column, or diagonal. The eight queens puzzle is an example of the more general n queens problem of placing n non-attacking queens on an n×n chessboard, for which solutions exist for all natural numbers n with the exception of n=2 and n=3*, [1].

*The problem can be quite computationally expensive, as there are 4,426,165,368 (i.e., 64C8) possible arrangements of eight queens on an 8×8 board, but only 92 solutions. It is possible to use shortcuts that reduce computational requirements or rules of thumb that avoids brute-force computational techniques. For example, by applying a simple rule that constrains each queen to a single column (or row), though still considered brute force, it is possible to reduce the number of possibilities to 16,777,216 (that is, 88) possible combinations. Generating permutations further reduces the possibilities to just 40,320 (that is, 8!), which are then checked for diagonal attacks.
Martin Richards published a program to count solutions to the n-queens problem using bitwise operations. However, this solution has already been published by Zongyan Qiu*, [1].

The approach we follow is based on genetic algorithms.

## References
[1] 8 queens problem, general information. https://en.wikipedia.org/wiki/Eight_queens_puzzle .

## License