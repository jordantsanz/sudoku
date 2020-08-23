/*
 * solvetest.c - a test file for solve
 * 
 * usage: ./solvetest
 * 
 * Author: Alex Hamel, James Verschleiser, Jordan Sanz
 * Date: 08/19/2020
 * Class: CS50
 * Professor: Xia Zhou
 */

#include <stdio.h>
#include <stdlib.h>
#include "../common/puzzle.h"
#include "../solve/solve.c"

int main() 
{
    // test on normal solvable puzzle
    FILE* Fp = fopen("../examplepuzzles/puzzle1.txt", "r");
    if (Fp == NULL) {
        fprintf(stderr, "File couldn't be opened\n");
        return 1;
    }
    puzzle_t* puzzle = puzzleNew();
    puzzleLoad(puzzle, Fp);
    solve(puzzle, 0, stdout);
    fclose(Fp);
    puzzleDelete(puzzle);
    fprintf(stdout, "ran test 1\n");

    // test on empty puzzle
    puzzle = puzzleNew();
    solve(puzzle, 0, stdout);
    puzzleDelete(puzzle);
    fprintf(stdout, "ran test 2\n");

    // test on puzzle with no solutions
    FILE* Fp2 = fopen("../examplepuzzles/unsolveablepuzzle1.txt", "r");
    if (Fp2 == NULL) {
        fprintf(stderr, "File couldn't be opened\n");
        return 1;
    }
    puzzle = puzzleNew();
    puzzleLoad(puzzle, Fp2);
    solve(puzzle, 0, stdout);
    fclose(Fp2);
    puzzleDelete(puzzle);
    fprintf(stdout, "ran test 3\n");

    // test on puzzle with multiple solutions
    FILE* Fp3 = fopen("../examplepuzzles/puzzlemultiplesolutions.txt", "r");
    if (Fp3 == NULL) {
        fprintf(stderr, "File couldn't be opened\n");
        return 1;
    }
    puzzle = puzzleNew();
    puzzleLoad(puzzle, Fp3);
    solve(puzzle, 0, stdout);
    fclose(Fp3);
    puzzleDelete(puzzle);
    fprintf(stdout, "ran test 4\n");

    return 0;
}

