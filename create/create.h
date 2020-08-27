/*
* create.c - interface for creating random sudoku puzzles
*
* contains the function that solves sudoku puzzles
* 
* Author: Alex Hamel, James Verschleiser, Jordan Sanz
* Date: 08/22/2020
* Class: CS50
* Professor: Xia Zhou
*/

#include <stdio.h>
#include <stdlib.h>
#include "../common/puzzle.h"
#include "../common/list.h"


/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/

/**************** global types ****************/

/**************** local functions ****************/
/***************** fillInSquare *******************/
/* fills in the entire puzzle to completion
*
* input: puzzle_t* puzzle, int startX, int startY
*
* output: return value of success: 0 if successful, -1 if not
*
* Notes:
* - will fill the puzzle that the puzzle_t* puzzle points to
* - startX and startY should be 0, 0 respectively
*/
int fillInSquare(puzzle_t* puzzle, int startX, int startY);

/*********************** inputSquareTile **************************/
/* Recursively fills in every tile of the sudoku board
* 
* input: puzzle_t* puzzle, int x, int y, list_t* list
* output: return value of success: 0 if successful, -1 if not
*
*
* Notes:
* - will attempt to fill in a random value at (x, y)
* - if the board is no longer valid, will reset that value and try again with a different value
* - if all values are tried, will return -1
* - runs recursively; thus, if one tile is unsuccessful and returns -1, the previous tile will attempt to 
*   fill in with the remaining numbers from their list previously
*/
int inputSquareTile(puzzle_t* puzzle, int x, int y, list_t* list);

/************************ puzzleRemoveTiles *************************/
/* Removes tiles from a completed sudoku board to make it solveable
* Will only make a puzzle with one possible solution
*
* input: puzzle_t* puzzle, int num_tiles
* output: none
*
*
* Notes:
* - will remove num_tiles tiles from the sudoku board, replacing them with 0's
* - attempts to remove a tile from the board
* - if the tile being removed leaves a board with only one solution, the tile stays removed
* - else, the tile is put back and another random tile is attempted
*/
void puzzleRemoveTiles(puzzle_t* puzzle, int num_tiles);

/******************************** makePuzzleCopy **********************/
/* makes a copy of a puzzle
* 
* input: puzzle_t* puzzle
* output: puzzle_t* puzzleCopy of puzzle_t* puzzle
*
* Notes:
* - allocates memory for a pointer to a new puzzle, so this must be deleted (and is in puzzleRemoveTiles)
*/
puzzle_t* makePuzzleCopy(puzzle_t* puzzle);

/**************** global functions *******************************************/

/**************** create() ****************/
/*
 * creates a random sudoku puzzle
 * 
 * input: number of tiles removed, file pointer to print created puzzle (NULL if not needed)
 * 
 * output: a randomly created, solveable sudoku puzzle
 * 
 * Notes: 
 * - each puzzle will have only one solution
 * - a user can specify how many tiles they would like removed from the puzzle
 * - if user doesn't specify, -1 should be passed in
 * - because a pointer to a puzzle is returned, the user should call puzzleDelete() on the puzzle
 */
void create(int num_tiles, int time, FILE* fp);
