/*
 * solvetest.c - a test file for solve
 * 
 * usage: ./solvetest
 * 
 * Author: James Verschleiser
 * Date: 08/19/2020
 * Class: CS50
 * Professor: Xia Zhou
 */

#include <stdio.h>
#include <stdlib.h>
#include "../common/puzzle.h"
#include "../solve/solve.c"

int main() {
    FILE* Fp = fopen("../examplepuzzles/puzzle1.txt", "r");
    if (Fp == NULL) {
        fprintf(stderr, "File couldn't be opened\n");
        return 1;
    }
    puzzle_t* puzzle = puzzleNew();
    puzzleLoad(puzzle, Fp);
    solve(puzzle, 0, "solveOutput.txt");
    fclose(Fp);
    puzzleDelete(puzzle);

    puzzle = puzzleNew();
    solve(puzzle, 0, "solveOutput2.txt");
    puzzleDelete(puzzle);
    return 0;
}

