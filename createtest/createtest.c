/*
 * createtest.c - a test file for create
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

    // try and make random puzzle
    puzzle_t* puzzle = create(num_tiles);
    
    waitFor(1);
    // try and make another random puzzle
    puzzle_t* puzzle2 = create(num_tiles);

    // print the puzzles
    FILE* fp1 = fopen("output/puzzle1output.txt", "w");
    FILE* fp2 = fopen("output/puzzle2output.txt", "w");

    FILE* fp3 = fopen("output/puzzle1solved.txt", "w");
    FILE* fp4 = fopen("output/puzzle2solved.txt", "w");
    puzzlePrint(puzzle, fp1);
    puzzlePrint(puzzle2, fp2);

    // try and solve the puzzles
    int count1 = solve(puzzle, 0, fp3);
    int count2 = solve(puzzle2, 0, fp4);

    // print num of solutions
    printf("Number of sols in 1: %d \n", count1);
    printf("Number of sols in 2: %d \n", count2);

    puzzleDelete(puzzle);
    puzzleDelete(puzzle2);
}

// function taken from https://stackoverflow.com/questions/3930363/implement-time-delay-in-c

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}