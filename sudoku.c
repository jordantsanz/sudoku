/*
 * sudoku.c - executable for CS50 final project
 * 
 * to run use ./sudoku
 * 
 * Author: Alexandre Hamel, James Verschleiser, Jordan Sanz
 * Date: 08/17/2020
 * Class: CS50
 * Professor: Xia Zhou
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "./libcs50/file.h"
#include "./libcs50/memory.h"
#include "./create/create.h"
#include "./solve/solve.h"
#include "./common/puzzle.h"
#include "./common/list.h"

void interface();
static void space();

int main(const int argc, const char *argv[]) 
{
    if (argc < 2) {
        fprintf(stderr, "Too few arguments. usage: ./sudoku create or ./sudoku solve\n");
        exit(1);
    }
    if (argc > 2){
        fprintf(stderr, "Too many arguments. usage: ./sudoku create or ./sudoku solve\n");
        exit(1);
    }

    if (strcmp(argv[1], "create") != 0 && strcmp(argv[1], "solve") != 0){
        fprintf(stderr, "Argument may only be 'create' or 'solve'. usage: ./sudoku create or ./sudoku solve\n");
        exit(2);
    }

    interface(argv[1]);
    return 0;
    
}

void interface(char* arg) 
{
    if (strcmp(arg, "create") == 0){
        puzzle_t* created = assertp(create(40), "Error generating a sudoku puzzle.\n");
        puzzlePrint(created, stdout);
        puzzleDelete(created);
    }
    else if (strcmp(arg, "solve") == 0){
        puzzle_t* toSolve = assertp(puzzleNew(), "Error creating an empty sudoku puzzle.\n");
        puzzleLoad(toSolve, stdin);
        puzzle_t* solvedHolder = assertp(puzzleNew(), "Error creating an empty sudoku puzzle.\n");
        int solvedCount = solve(toSolve, solvedHolder, 0, stdout);
        space();
        if (solvedCount > 1){
            fprintf(stdout, "More than one solution. Here is one possible solution.\n");
        }
        if (solvedCount != 0){
            puzzlePrint(solvedHolder, stdout);
        }
        else{
            fprintf(stdout, "There are no solutions.\n");
        }
        puzzleDelete(toSolve);
        puzzleDelete(solvedHolder);
    }
    else{
        fprintf(stderr, "Error with handling argument.\n");
        exit(3);
    }
}

static void
space(void)
{
  // print a space iff stdin is a tty (terminal)
  if (isatty(fileno(stdin))) {
    printf("\n");
  }
}
