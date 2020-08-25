/*
 * createtest.c - a test file for create
 * 
 * usage: ./solvetest [num_tiles]
 * 
 * Author: Alex Hamel, James Verschleiser, Jordan Sanz
 * Date: 08/19/2020
 * Class: CS50
 * Professor: Xia Zhou
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../common/puzzle.h"
#include "../common/list.h"
#include "../solve/solve.h"
#include "../libcs50/memory.h"
#include "../create/create.h"

void waitFor(unsigned int sect);


int main(const int argc, const char* argv[])
{
    int num_tiles;
    if (argc == 1){
        num_tiles = -1;
    }
    else if (argc == 2){
        num_tiles = atoi(argv[1]);
    }
    else{
        fprintf(stderr, "Too many arguments. Usage: .createtest [num_tiles]\n");
        exit(1);
    }

    create(56, NULL);

    // try and make random puzzle
    puzzle_t* puzzle = create(num_tiles, NULL);
    
    waitFor(1);
    // try and make another random puzzle
    puzzle_t* puzzle2 = create(num_tiles, NULL);

    waitFor(1);

    // try a hard puzzle!
    puzzle_t* puzzle3 = create(55, NULL);

    // print the puzzles
    FILE* fp1 = fopen("output/puzzle1output.txt", "w");
    FILE* fp2 = fopen("output/puzzle2output.txt", "w");
    FILE* fp5 = fopen("output/puzzle3output.txt", "w");

    FILE* fp3 = fopen("output/puzzle1solved.txt", "w");
    FILE* fp4 = fopen("output/puzzle2solved.txt", "w");
    FILE* fp6 = fopen("output/puzzle3solve.txt", "w");
    puzzlePrint(puzzle, fp1);
    puzzlePrint(puzzle2, fp2);
    puzzlePrint(puzzle3, fp5);

    puzzle_t* puzzle1Solve = assertp(puzzleNew(), "Could not allocate memory for puzzle1Solve.\n");
    puzzle_t* puzzle2Solve = assertp(puzzleNew(), "Could not allocate memory for puzzle2Solve.\n");
    puzzle_t* puzzle3Solve = assertp(puzzleNew(), "Could not allocate memory for puzzle3Solve.\n");
    // try and solve the puzzles
    int count1 = solve(puzzle, puzzle1Solve, 0, fp3);
    puzzlePrint(puzzle1Solve, fp3);
    puzzleDelete(puzzle1Solve);
    int count2 = solve(puzzle2, puzzle2Solve, 0, fp4);
    puzzlePrint(puzzle2Solve, fp4);
    puzzleDelete(puzzle2Solve);
    int count3 = solve(puzzle3, puzzle3Solve, 0, fp6);
    puzzlePrint(puzzle3Solve, fp6);
    puzzleDelete(puzzle3Solve);

    // print num of solutions
    printf("Number of sols in 1: %d \n", count1);
    printf("Number of sols in 2: %d \n", count2);
    printf("Number of sols in 3: %d \n", count3);

    puzzleDelete(puzzle);
    puzzleDelete(puzzle2);
    puzzleDelete(puzzle3);
}

// function taken from https://stackoverflow.com/questions/3930363/implement-time-delay-in-c

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}
