/*
 * Solve.c file for CS50 final project
 * Authors: Alex Hamel, James Verschleiser, Jordan Sanz
 *
 * Input:
 * Output: solved sudoko puzzle
 *
 */ 

#include <stdio.h>
#include <stdlib.h>
#include "../common/puzzle.h"

int solve(puzzle_t* puzzle, int solved_count, FILE* fp) 
{
    // loop through all of the squares is the sudoku puzzle
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {

            // check to see if the current square is empty
            if (puzzleGetTile(puzzle, y, x) == 0) {
                // start checking if numbers work
                for (int i = 1; i < 10; i++) {

                    // if the number works then set it equal to that number
                    if (checkPossible(puzzle, y, x, i) == true) {

                        puzzleSetTile(puzzle, y, x, i);

                        // if the puzzle doesn't already have multiple solutions than recurse with this more filled in puzzle
                        if (solved_count < 2) {
                            solved_count = solve(puzzle, solved_count, fp);
                        }

                        // if we get back to here then solution has been found so set back to 0
                        puzzleSetTile(puzzle, y, x, 0);
                    }
                }
                return solved_count;

            }
        }
    }
    // if the puzzle is currently solved then print it out
    if (puzzleSolved(puzzle) == true) {
        puzzlePrint(puzzle, fp);
        fprintf(fp, "\n");
        solved_count++;
    }

    // if this is the second solution than print that there are multiple solutions
    if (solved_count == 2) {

        if (puzzleSolved(puzzle) == true) {
            fprintf(fp, "More than one solution\n");
        }

    }

    // if it reaches here with no prior solutions and isn't current solved then it is unsolvable
    // some unsolvable puzzles won't reach this point
    if (solved_count == 0) {
        if (puzzleSolved(puzzle) == false) {
            fprintf(fp, "Puzzle has no solution\n");
        }

    }

    return solved_count;
    
}
