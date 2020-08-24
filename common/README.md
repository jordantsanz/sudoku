# CS50 Final Project - Common
## Alex Hamel, James Verschleiser, Jordan Sanz

### common
`common` is a library in the Sudoku final project that holds two modules: `puzzle`, which is a program of functions that help create, update, validate, and delete a puzzle; and `list`, which is a module implemented as a randomized stack of numbers 1-9, allowing for the popping of numbers from the end.

The `common` library is used by `create` and `solve` to create new `puzzles`, add numbers into the borad of the `puzzle`, check to make sure the numbers added do not validate the rules of Sudoku, and to delete the `puzzle`. `puzzle` implements a puzzle as a 2-D array of numbers 1-9, and the number 0 to represent a 'blank' tile. The `common` library is also used by `create` to use a `list` that randomly allows `create` to fill a `puzzle` of numbers. 

### Usage
`common` is a part of the Sudoku final project, and implements `list` and `puzzle`. It utilizies the following functions:

```c
puzzle_t* puzzleNew();
void puzzleLoad(puzzle_t* puzzle, FILE* fp);
int puzzleGetTile(puzzle_t* puzzle, int row, int column);
void puzzleSetTile(puzzle_t* puzzle, int row, int column, int value);
bool puzzleValid(puzzle_t* puzzle);
bool puzzleValidTile(puzzle_t* puzzle, int row, int column);
bool puzzleValidRow(puzzle_t* puzzle, int row);
bool puzzleValidColumn(puzzle_t* puzzle, int column);
bool puzzleValidSquare(puzzle_t* puzzle, int row, int column);
bool checkPossible(puzzle_t* puzzle, int row, int column, int n);
bool puzzleSolved(puzzle_t* puzzle);
void puzzlePrint(puzzle_t* puzzle, FILE* fp);
void puzzleDelete(puzzle_t* puzzle);
list_t* list_new();
int list_pop(list_t* list);
void list_delete(list_t* );
void swap(list_t* list, int i, int j);
void set_seed();
void reset_seed(int num);
```

### Implementation 

A full implementation spec is found in the IMPLEMENTATION.md file.

### Assumptions

There are no assumptions in this library beyond those that are clear in the spec.

### Files

* `list.c` - The implementation for the `list` module
* `list.h` - The interface for the `list` module
* `puzzle.c` - The implementation for the `puzzle` module
* `puzzle.h` - The interface for the `puzzle` module
* `Makefile` - The instructions for compiling
* `README.md` - The information about the `common` library

### Compliation

To compile, simply `make common`.

### Testing

Testing for `common` can be found in `TESTING.md` in the `common` section.