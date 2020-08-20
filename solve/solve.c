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

void solve(puzzle_t* puzzle, char* filename) {
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            if (puzzleGetTile(puzzle, y, x) == 0) {
                for (int i = 1; i < 10; i++) {
                    if (checkPossible(puzzle, y, x, i) == true) {
                        puzzleSetTile(puzzle, y, x, i);
                        solve(puzzle, filename);
                        puzzleSetTile(puzzle, y, x, 0);
                    }
                }
                return;
            }
        }
    }
    FILE* Fp = fopen(filename, "w");
    if (Fp == NULL) {
        fprintf(stderr, "File could not be written in\n");
        return;
    }
    puzzlePrint(puzzle, Fp);
    fclose(Fp);
    exit(0);
}
