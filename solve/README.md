# CS50 Final Project - Create
## Alex Hamel, James Verschleiser, Jordan Sanz

### solve
`solve` is a function in the Sudoku final project that attempts to solve a sudoku puzzle. It also determines whether there is no solution, a unique solution, or multiple solutions for the given puzzle. 

It does this by going through tiles one by one. For each tile that isn't already filled in, it tries a number until one is valid and then recursively calls the function with this new more-filled in board. It does so until either the board is full or no number works in a given square. In the case of the latter, the program backtracks until it tries every possible combination or a valid solution is found. 

### Usage
`solve` is a part of the Sudoku final project, and implements a recursive back-tracking algorithm. It utilizes the following function:

```c
int solve(puzzle_t* puzzle, puzzle_t* solvedHolder, int solved_count, FILE* fp);
```

### Implementation

A full implementation spec is found in the IMPLEMENTATION.md file. 

### Assumptions

There are no assumptions in this library beyond those that are clear in the specs.

### Files

```
Solve.h: header function that contains information about the functions.
Solve.c: actual c code
Makefile: compiles the given code
```

### Compilation

To compile, simply `make solve.o`. 

### Testing

Testing for `solve` can be found in `TESTING.md` in the `solve` section. 
