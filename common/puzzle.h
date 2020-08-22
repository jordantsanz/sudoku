/*
 * puzzle.c - data structure for CS50 final project
 * 
 * contains the data structure puzzle which houses the sudoku puzzle struct and functions to operate on it
 * 
 * Author: Alexandre Hamel
 * Date: 08/17/2020
 * Class: CS50
 * Professor: Xia Zhou
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "../libcs50/file.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct puzzle puzzle_t;

/**************** global types ****************/

/**************** global functions ****************/
/* that is, visible outside this file */

/**************** local functions ****************/
/* not visible outside this file */

/**************** puzzleNew() ****************/
/*
 * creates a new sudoku puzzle struct
 * user is responsible for calling puzzleDelete on the given structure
 * 
 * input:
 * 
 * output: completed puzzle_t struct
 */
puzzle_t* puzzleNew();

/**************** puzzleLoad() ****************/
/*
 * loads in a sudoku puzzle from a file to a given puzzle_t* struct
 * 
 * input: puzzle_t* struct, file pointer to sudoku
 * 
 * output: the puzzle loaded into the puzzle_t* struct
 */
void
puzzleLoad(puzzle_t* puzzle, FILE* fp);

/**************** puzzleGetTile() ****************/
/*
 * sets a value in tile within the puzzle
 * row and colums go 0-8
 * 
 * input: puzzle_t struct, int row, int column
 * 
 * output: int of the value of the given tile, 0 if empty, -1 if puzzle or row/column out of bounds is NULL
 */
int puzzleGetTile(puzzle_t* puzzle, int row, int column);

/**************** puzzleSetTile() ****************/
/*
 * gets a value in a tile within the puzzle
 * row and colums go 0-8
 * 
 * input: puzzle_t struct, int row, int column, int value
 * 
 * output: the value changed in the puzzle_t struct
 */
void puzzleSetTile(puzzle_t* puzzle, int row, int column, int value);

/**************** puzzleValid() ****************/
/*
 * checks to see if whole sudoku is valid
 * 
 * input: puzzle_t struct
 * 
 * output: true if valid, false otherwise
 */
bool puzzleValid(puzzle_t* puzzle);

/**************** puzzleValidTile() ****************/
/*
 * checks to see if a single tile in the sudoku is valid
 * row and colums go 0-8
 * 
 * input: puzzle_t struct, int row of tile, int column of tile
 * 
 * output: true if valid, false otherwise
 */
bool puzzleValidTile(puzzle_t* puzzle, int row, int column);

/**************** puzzleValidRow() ****************/
/*
 * checks to see if a given row in the sudoku is valid
 * 
 * input: puzzle_t struct, int row
 * 
 * output: true if row is valid, false otherwise
 */
bool puzzleValidRow(puzzle_t* puzzle, int row);

/**************** puzzleValidColumn() ****************/
/*
 * checks to see if a given column in the sudoku is valid
 * 
 * input: puzzle_t struct, int column
 * 
 * output: true if column is valid, false otherwise
 */
bool puzzleValidColumn(puzzle_t* puzzle, int column);

/**************** puzzleValidSquare() ****************/
/*
 * checks to see if a given square (coordinates 0-2 in the 3x3 subgrid) in the sudoku is valid
 * 
 * input: puzzle_t struct, int row of 3x3 subgrid, int column of 3x3 subgrid
 * 
 * output: true if square is valid, false otherwise
 */
bool puzzleValidSquare(puzzle_t* puzzle, int row, int column);

/**************** puzzleDelete() ****************/
/*
 * checks to see if a number works
 * 
 * input: puzzle_t struct, row number, column number, the guess
 * 
 * output: true or false
 */
bool checkPossible(puzzle_t* puzzle, int row, int column, int n);

/**************** puzzleSolved() ****************/
/*
 * checks to see if whole sudoku is solved 
 * 
 * input: puzzle_t struct
 * 
 * output: true if valid, false otherwise
 */
bool puzzleSolved(puzzle_t* puzzle);

/**************** puzzlePrint() ****************/
/*
 * prints the sudoku puzzle to given file
 * 
 * input: puzzle_t struct, fp for output file
 * 
 * output: puzzle printed to output file
 */
void puzzlePrint(puzzle_t* puzzle, FILE* fp);

/**************** puzzleDelete() ****************/
/*
 * frees memory for a sudoku puzzle struct
 * 
 * input: puzzle_t struct
 * 
 * output: memory used by puzzle_t struct returned to memory
 */
void puzzleDelete(puzzle_t* puzzle);
