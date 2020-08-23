# CS50 Final Project - Create
## Alex Hamel, James Verschleiser, Jordan Sanz

### create
`create` is a library in the Sudoku final project that creates a randomized, solveable sudoku puzzle that has only one solution. 

It does this by first generating a fully-completed sudoku board, with every number filled in to where the board is a validly completed puzzle. It then removes tiles one by one, checking to make sure that the resulting puzzle always has only one solution. It then returns the puzzle with blanks in it, returning a random, solveable puzzle. 
### Usage
`create` is a part of the Sudoku final project, and implements a random creating algorithm. It utilizes the following functions:

```c
puzzle_t* create(int num_tiles);
int fillInSquare(puzzle_t* puzzle, int startX, int startY);
int inputSquareTile(puzzle_t* puzzle, int x, int y, list_t* list);
void puzzleRemoveTiles(puzzle_t* puzzle, int num_tiles);
puzzle_t* makePuzzleCopy(puzzle_t* puzzle);
```

### Implementation

A full implementation spec is found in the IMPLEMENTATION.md file. 

### Assumptions

There are no assumptions in this library beyond those that are clear in the specs.

### Files

A full list of files used is found in the IMPLEMENTATION.md spec.

### Compilation

To compile, simply `make create.o`. 

### Testing

Testing for `create` can be found in `TESTING.md` in the `create` section. 
