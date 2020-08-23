/*
 * play.c - executable for CS50 final project
 * 
 * to run use ./play
 * 
 * Author: Alexandre Hamel, James Verschleiser, Jordan Sanz
 * Date: 08/17/2020
 * Class: CS50
 * Professor: Xia Zhou
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libcs50/file.h"
#include "../create/create.h"
#include "../solve/solve.h"
#include "../common/puzzle.h"
#include "../common/list.h"

void interface();

int main(const int argc, const char *argv[]) 
{
    if (argc != 1) {
        fprintf(stderr, "Please run with no arguments\n");
    }

    interface();
    
}

void interface() 
{
    fprintf(stdout, "Please type in 'create' to make new puzzle\n");

    puzzle_t* puzzle = puzzleNew();
    char* line;
    char* difficulty;

    while ((line = freadlinep(stdin)) != NULL) 
    {
        if (strcmp(line, "create") == 0) {
            fprintf(stdout, "easy, medium, or hard?\n");
            difficulty = freadlinep(stdin);

            if (strcmp(difficulty, "easy")) {
                puzzle = create(35);
                puzzlePrint(puzzle, stdout);
            }

            else if (strcmp(difficulty, "medium")) {
                puzzle = create(40);
                puzzlePrint(puzzle, stdout);
            }

            else if (strcmp(difficulty, "hard")) {
                puzzle = create(50);
                puzzlePrint(puzzle, stdout);
            }

            else {
                fprintf(stdout, "Invalid difficulty level\n");
                free(difficulty);
                free(line);
                interface();
            }

            free(difficulty);
            fprintf(stdout, "Type 'create' for new puzzle or 'solve' to solve current puzzle");
        }

        else if (strcmp(line, "solve") == 0) {

            if (puzzle != NULL) {
                solve(puzzle, 0, stdout);
            }
            
            fprintf(stdout, "Please type in 'create' to make new puzzle\n");
        }

        else {
            fprintf(stdout, "invlaid command\n");
            interface();
        }

        free(line);
    }

    return;

}
