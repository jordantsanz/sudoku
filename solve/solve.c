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
#include "solve.h"
#include "../common/puzzle.h"

int solve(puzzle_t* puzzle, puzzle_t* solvedHolder, int solved_count, FILE* fp) 
{

    // check that puzzle exists
    if (puzzle == NULL){
        fprintf(stderr, "Puzzle passed into solve is NULL.\n");
        return 0;
    }

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
                            solved_count = solve(puzzle, solvedHolder, solved_count, fp);
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

        // check that solved holder exists
        if (solvedHolder != NULL){

            // create puzzle copy
            puzzleCopy(puzzle, solvedHolder);

            // if filepointer is null, write to file for UI
            if (fp == NULL){
                FILE* fp2;
                fp2 = fopen("./uipuzzles/solvedpuzzle.txt", "w");

                // if filepointer 2 is null, cannot open file to write
                if (fp2 == NULL){
                    fprintf(stderr, "Failed to write to solvedpuzzle.txt.\n");
                    return 0;
                }

                // print puzzle
                puzzlePrint(solvedHolder, fp2);
                fclose(fp2);
            }
        }
        solved_count++;
    }

    return solved_count;
    
}

// for graphics UI solving 
void solveUI(){

    // create new puzzle
    puzzle_t* loadIn = puzzleNew();

    // mem check
    if (loadIn == NULL){
        fprintf(stderr, "Couldn't allocate memory for loadIn.\n");
        return;
    }

    // create buffer puzzle
    puzzle_t* buffer = puzzleNew();

    // mem check
    if (buffer == NULL){
        fprintf(stderr, "Couldn't allocate memory for buffer.\n");
        puzzleDelete(loadIn);
        return;
    }

    // open ui puzzles from create
    FILE* fp1 = fopen("./uipuzzles/newpuzzle.txt", "r");

    // check to make sure it can open
    if (fp1 == NULL){
        fprintf(stderr, "Failed to read from newpuzzle.txt.\n");
        puzzleDelete(loadIn);
        puzzleDelete(buffer);
        return;
    }

    // load in puzzle to puzzle structure from create puzzle
    puzzleLoad(loadIn, fp1);
    fclose(fp1);

    // solve puzzle and free
    solve(loadIn, buffer, 0, NULL);
    free(loadIn);
    free(buffer);

}
