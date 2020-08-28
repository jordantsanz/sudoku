/*
 * solve.c - solve function for CS50 final project
 * 
 * contains the function that solves sudoku puzzles
 * 
 * Author: Alex Hamel, James Verschleiser, Jordan Sanz
 * Date: 08/19/2020
 * Class: CS50
 * Professor: Xia Zhou
 */

#include <stdio.h>
#include <stdlib.h>
#include "../common/puzzle.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/

/**************** global types ****************/

/**************** global functions ****************/
/* that is, visible outside this file */

/**************** local functions ****************/
/* not visible outside this file */

/**************** solve() ****************/
/*
 * solves sudoku puzzles
 * 
 * input: a sudoku puzzle
 * 
 * output: completed sudoku puzzle
 */
int solve(puzzle_t* puzzle, puzzle_t* solvedHolder, int solved_count);
