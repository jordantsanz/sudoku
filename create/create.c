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
#include <unistd.h>
#include "create.h"
#include "../libcs50/memory.h"
#include "../common/puzzle.h"
#include "../common/list.h"
#include "../solve/solve.h"

/***************** prototypes *************/
void create(int num_tiles, int time, FILE* fp);
int fillInSquare(puzzle_t* puzzle, int startX, int startY);
int inputSquareTile(puzzle_t* puzzle, int x, int y, list_t* list);
void puzzleRemoveTiles(puzzle_t* puzzle, int num_tiles);
puzzle_t* makePuzzleCopy(puzzle_t* puzzle);

void create(int num_tiles, int time, FILE* fp)
{

    // check for if number of tiles is set, or default
    if (num_tiles == -1) {
        num_tiles = 40;
    }

    else if (num_tiles > 55){
        printf("Cannot remove that many tiles. \n");
        return;
    }

    set_seed(time); // set randomized seed

    puzzle_t* puzzle = assertp(puzzleNew(), "Puzzle could not be created.");  // puzzle


    // fill-in all squares
    if(fillInSquare(puzzle, 0, 0) == -1){
        printf("Puzzle not filled in correctly. \n");
        puzzleDelete(puzzle);
        return;
    };

    // check that the puzzle solved
    if(!puzzleSolved(puzzle)){
        printf("Puzzle is not valid. :( \n");
        puzzleDelete(puzzle);
        return;
    }

    if (fp == NULL){
        FILE* fp1;
        fp1 = fopen("./uipuzzles/solvedpuzzle.txt", "w");
        if (fp1 == NULL){
            fprintf(stderr, "Couldn't write to fp1.\n");
            return;
        }
        puzzlePrint(puzzle, fp1);
        fclose(fp1);
    }
    

    // remove tiles from puzzle
    puzzleRemoveTiles(puzzle, num_tiles);

    // check to make sure one solution only:
    if(solve(puzzle, NULL, 0, stdout) != 1){
        printf("There wasn't only one solution. \n");
        puzzleDelete(puzzle);
        return;
    }

    if (fp != NULL){
        puzzlePrint(puzzle, fp);
    }
    else{
        FILE* fp2;
        fp2 = fopen("./uipuzzles/newpuzzle.txt", "w");
        if (fp2 == NULL){
            fprintf(stderr, "Couldn't write to fp2.\n");
            return;
        }
        puzzlePrint(puzzle, fp2);
        fclose(fp2);
    }

    free(puzzle);
}

int fillInSquare(puzzle_t* puzzle, int startX, int startY)
{
    list_t* list = assertp(list_new(), "A new list could not be created");
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
                returnVal = inputSquareTile(puzzle, x, y+1, assertp(list_new(), "A new list could not be created"));
            }

            // on last column but not last row, so down one row and back to first column
            else if (y == 8 && x != 8){
                returnVal = inputSquareTile(puzzle, x+1, 0, assertp(list_new(), "A new list could not be created"));
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

void puzzleRemoveTiles(puzzle_t* puzzle, int num_tiles)
{

    int x = -1; // x row to grab tile from
    int y = -1; // y col to grab tile from
    int tile = 0; // value of tile
    int removed_tiles = 0; // number of removed tiles
    puzzle_t* copy;

    // while there are still tiles to remove
    while(removed_tiles < num_tiles){

        // selects random, filled value from puzzle
        while (tile == 0){

            x = rand() % 9; // choose random number 0-8
            y = rand() % 9;  // choose random number 0-8

            tile = puzzleGetTile(puzzle, x, y);
        }

        puzzleSetTile(puzzle, x, y, 0); // attempt to set as 0
        copy = assertp(puzzleNew(), "Could not allocate memory for puzzle copy.\n");
        puzzleCopy(puzzle, copy);
        
        if(solve(copy, NULL, 0, stdin) != 1){  // if not only one solution
            puzzleSetTile(puzzle, x, y, tile); // reset tile
        }

        else{
            removed_tiles += 1; // successful removal
        }

        puzzleDelete(copy);

        tile = 0;

    }

}
