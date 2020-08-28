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
#include "../../common/puzzle.h"
#include "../../solve/solve.h"

int main() 
{
    // test on normal solvable puzzle
    FILE* Fp = fopen("../../examplepuzzles/puzzle1.txt", "r");
    if (Fp == NULL) {
        fprintf(stderr, "File couldn't be opened\n");
        return 1;
    }
    puzzle_t* puzzle = puzzleNew();
    puzzle_t* solved = puzzleNew();
    puzzleLoad(puzzle, Fp);
    solve(puzzle, solved, 0);
    fclose(Fp);
    puzzlePrint(solved, stdout);
    puzzleDelete(puzzle);
    puzzleDelete(solved);
    fprintf(stdout, "ran test 1\n");

    // test on empty puzzle
    puzzle = puzzleNew();
    solved = puzzleNew();
    solve(puzzle, solved, 0);
    puzzlePrint(solved, stdout);
    puzzleDelete(puzzle);
    puzzleDelete(solved);
    fprintf(stdout, "ran test 2\n");

    // test on puzzle with no solutions
    FILE* Fp2 = fopen("../../examplepuzzles/unsolveablepuzzle1.txt", "r");
    if (Fp2 == NULL) {
        fprintf(stderr, "File couldn't be opened\n");
        return 1;
    }
    puzzle = puzzleNew();
    solved = puzzleNew();
    puzzleLoad(puzzle, Fp2);
    solve(puzzle, solved, 0);
    fclose(Fp2);
    fprintf(stdout, "Below should be all 0's:\n");
    puzzlePrint(solved, stdout);
    puzzleDelete(puzzle);
    puzzleDelete(solved);
    fprintf(stdout, "ran test 3\n");

    // test on puzzle with multiple solutions
    FILE* Fp3 = fopen("../../examplepuzzles/puzzlemultiplesolutions.txt", "r");
    if (Fp3 == NULL) {
        fprintf(stderr, "File couldn't be opened\n");
        return 1;
    }
    puzzle = puzzleNew();
    solved = puzzleNew();
    puzzleLoad(puzzle, Fp3);
    solve(puzzle, solved, 0);
    fclose(Fp3);
    puzzlePrint(solved, stdout);
    puzzleDelete(puzzle);
    puzzleDelete(solved);
    fprintf(stdout, "ran test 4\n");

    return 0;
}
