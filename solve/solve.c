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
        if (solvedHolder != NULL){
            puzzleCopy(puzzle, solvedHolder);
            if (fp == NULL){
                FILE* fp2;
                fp2 = fopen("./uipuzzles/solvedpuzzle.txt", "w");
                if (fp2 == NULL){
                    fprintf(stderr, "Failed to write to solvedpuzzle.txt.\n");
                    return 0;
                }
                puzzlePrint(solvedHolder, fp2);
                fclose(fp2);
            }
        }
        solved_count++;
    }

    return solved_count;
    
}

void solveUI(){

    puzzle_t* loadIn = puzzleNew();
    if (loadIn == NULL){
        fprintf(stderr, "Couldn't allocate memory for loadIn.\n");
        return;
    }
    puzzle_t* buffer = puzzleNew();
    if (buffer == NULL){
        fprintf(stderr, "Couldn't allocate memory for buffer.\n");
        puzzleDelete(loadIn);
        return;
    }
    FILE* fp1 = fopen("./uipuzzles/newpuzzle.txt", "r");
    if (fp1 == NULL){
        fprintf(stderr, "Failed to read from newpuzzle.txt.\n");
        puzzleDelete(loadIn);
        puzzleDelete(buffer);
        return;
    }
    puzzleLoad(loadIn, fp1);
    fclose(fp1);
    solve(loadIn, buffer, 0, NULL);
    free(loadIn);
    free(buffer);

}
