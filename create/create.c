/* create.c - program for creating a random sudoku puzzle
* 
* Author: Alexandre Hamel, James Verschleiser, Jordan Sanz
* Date: 08/17/2020
* Class: CS50
* Professor: Xia Zhou
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "../libcs50/memory.h"
#include "puzzle.h"
#include "list.h"

/***************** prototypes *************/
void fillInDiagSquare(puzzle_t* puzzle, int startX, int startY);
int fillInSquare(puzzle_t* puzzle, int startX, int startY);
int inputSquareTile(puzzle_t* puzzle, int x, int y, list_t* list);

int main(const int argc, const char* argv[])
{
    set_seed(); // set randomized seed

    puzzle_t* puzzle = assertp(puzzleNew(), "Puzzle could not be created.");  // puzzle


    // fill-in all squares
    if(fillInSquare(puzzle, 0, 0) == -1){
        printf("Puzzle not filled in correctly. \n");
    };

    // print the puzzle
    puzzlePrint(puzzle, stdout);

    // check that the puzzle solved
    if(!puzzleSolved(puzzle)){
        printf("Puzzle is not valid. :( \n");
    }
    else{
        printf("Puzzle is valid! \n");
    }

    // delete the puzzle for now
    puzzleDelete(puzzle);

    return 0;

}

int fillInSquare(puzzle_t* puzzle, int startX, int startY)
{
    list_t* list = list_new();
    int returnValue = inputSquareTile(puzzle, startX, startY, list);
    return returnValue;

}

int inputSquareTile(puzzle_t* puzzle, int x, int y, list_t* list)
{
    int value;  // list_pop value
    int returnVal; // keeps track of return value

    while((value = list_pop(list)) != -1){  // while numbers to try

        puzzleSetTile(puzzle, x, y, value);  // input value into the puzzle

        if (puzzleValidTile(puzzle, x, y)){ 
             // if the value is valid, then move to next tile to right (or down and back to first column)

            // not on last column, so move one right
            if (y != 8){
                returnVal = inputSquareTile(puzzle, x, y+1, list_new());
            }

            // on last column but not last row, so down one row and back to first column
            else if (y == 8 && x != 8){
                returnVal = inputSquareTile(puzzle, x+1, 0, list_new());
            }

            // last column and last row; this is base case
            else{
                returnVal = 0;
            }

            // if returnVal is 0, free and return; success
            if (returnVal == 0){
                list_delete(list);
                return returnVal;
            }
        }
    }

    // impossible input now; need to backtrack
    list_delete(list);
    puzzleSetTile(puzzle, x, y, 0);  // reset tile to 0
    return -1; 
}

