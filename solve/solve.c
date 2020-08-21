/*
 * Solve.c file for CS50 final project
 *
 * Input:
 * Output: solved sudoko puzzle
 *
 */ 

#include <stdio.h>
#include <stdlib.h>
#include "../common/puzzle.h"

int solve(puzzle_t* puzzle, int solved_count, char* filename) {
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            if (puzzleGetTile(puzzle, y, x) == 0) {
                for (int i = 1; i < 10; i++) {
                    if (checkPossible(puzzle, y, x, i) == true) {
                        puzzleSetTile(puzzle, y, x, i);
                        if (solved_count < 2) {
                            solved_count = solve(puzzle, solved_count, filename);
                        }
                        puzzleSetTile(puzzle, y, x, 0);
                    }
                }
                return solved_count;
            }
        }
    }
    FILE* Fp = fopen(filename, "w");
    if (Fp == NULL) {
        fprintf(stderr, "File could not be written in\n");
        exit(1);
    }
    puzzlePrint(puzzle, Fp);
    fprintf(Fp, "\n");
    if (solved_count == 1) {
        if (puzzleSolved(puzzle) == true) {
            fprintf(Fp, "More than one solution\n");
        }
        else {
            fprintf(Fp, "Only one solution\n");
        }
    }
    else if (solved_count == 0) {
        if (puzzleSolved(puzzle) == false) {
            fprintf(Fp, "Puzzle has no solution\n");
        }
    }
    fclose(Fp);
    solved_count++;
    return solved_count;
}
