/*
 * puzzle.c - data structure for CS50 final project
 * 
 * See puzzle.h for details
 * 
 * Author: Alexandre Hamel
 * Date: 08/17/2020
 * Class: CS50
 * Professor: Xia Zhou
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "puzzle.h"
#include "../libcs50/file.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct puzzle {
  int** grid;
} puzzle_t;

/**************** global types ****************/

/**************** global functions ****************/
/* that is, visible outside this file */

/**************** local functions ****************/
/* not visible outside this file */

/**************** puzzleNew() ****************/
/*
 * See puzzle.h for details
 */
puzzle_t*
puzzleNew(){

  puzzle_t* puzzle = malloc(sizeof(puzzle_t));
  if (puzzle == NULL){
    fprintf(stderr, "Couldn't allocate memory for puzzle\n");
    return NULL;
  }

  int** array = (int**)calloc(9, sizeof(int*));
  if (array == NULL){
    fprintf(stderr, "Couldn't allocate memory for array\n");
    free(puzzle);
    return NULL;
  }
  for (int i = 0; i < 9; i++){
    int* subArray = (int*)calloc(9, sizeof(int));
    if (subArray == NULL){
      fprintf(stderr, "Couldn't allocate memory for subArray\n");
      for (int j = 0; j < i; i++){  
        free(array[j]);
      }
      free(array);
      free(puzzle);
      return NULL;
    }
    array[i] = subArray;
  }

  for (int i = 0; i < 9; i++){
    for(int j = 0; j< 9; j++){
      array[i][j] = 0;
    }
  }

  puzzle->grid = array;

  return puzzle;

}

/**************** puzzleNew() ****************/
/*
 * See puzzle.h for details
 */
void
puzzleLoad(puzzle_t* puzzle, FILE* fp){

  char* line;
  char* original;
  int lineNum = 0;
  int numInLine;
  int value;
  bool singleDigit;
  bool foundDigit;
  while((line = freadlinep(fp)) != NULL){

    numInLine = 0;
    singleDigit = false;
    foundDigit = false;
    original = line;
    for( ; *line; ++line){
      if (isdigit(*line) != 0){
        if (lineNum > 8){
          fprintf(stderr, "Too many lines in source file.\n");
          free(original);
          return;
        }
        if (!singleDigit){
          singleDigit = true;
          foundDigit = true;
          if (numInLine > 8){
            fprintf(stderr, "Too many entries in line %d.\n", lineNum);
            free(original);
            return;
          }
          sscanf(line, "%d", &value);
          puzzle->grid[lineNum][numInLine] = value;
          numInLine++;
        }
        else{
          fprintf(stderr, "Puzzle file has two consecutive digits.\n");
          free(original);
          return;
        }
      }
      else if (isspace(*line) != 0){
        singleDigit = false;
      }
      else if (iscntrl(*line) == 0){
        fprintf(stderr, "Non-digit, non-space character in puzzle file.\n");
        free(original);
        return;
      }
    }
    if (numInLine < 9 && foundDigit){
      fprintf(stderr, "Too few entries in line %d.\n", lineNum);
      free(original);
      return;
    }
    if (foundDigit){
      lineNum++;
    }
    free(original);
  }

  if (lineNum < 9){
    fprintf(stderr, "Too few lines in source file.\n");
    return;
  }

}

/**************** puzzleGetTile() ****************/
/*
 * See puzzle.h for details
 */
int
puzzleGetTile(puzzle_t* puzzle, int row, int column){

  if (puzzle != NULL && row >= 0 && row < 9 && column >= 0 && column < 9){
    return puzzle->grid[row][column];
  }
  else{
    fprintf(stderr, "Puzzle is null or row/column out of bounds.\n");
    return -1;
  }

}

/**************** puzzleSetTile() ****************/
/*
 * See puzzle.h for details
 */
void
puzzleSetTile(puzzle_t* puzzle, int row, int column, int value){

  if (puzzle != NULL && row >= 0 && row < 9 && column >= 0 && column < 9 && value >= 0 && value < 10){
    puzzle->grid[row][column] = value;
  }
  else{
    fprintf(stderr, "Puzzle is null or row/column/value out of bounds.\n");
  }

}

/**************** puzzleValid() ****************/
/*
 * See puzzle.h for details
 */
bool
puzzleValid(puzzle_t* puzzle){
  
  if (puzzle == NULL){
    fprintf(stderr, "Puzzle is null.\n");
    return false;
  }

  for (int i = 0; i < 9; i++){
    if (!puzzleValidRow(puzzle, i) || !puzzleValidColumn(puzzle, i)){
      return false;
    }
  }

  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      if (!puzzleValidSquare(puzzle, i, j)){
        return false;
      }
    }
  }

  return true;

}

/**************** puzzleValidTile() ****************/
/*
 * See puzzle.h for details
 */
bool
puzzleValidTile(puzzle_t* puzzle, int row, int column){

  int subGridRow;
  int subGridColumn;
  if (puzzle == NULL || row < 0 || row >= 9 || column < 0 || column >= 9){
    fprintf(stderr, "Puzzle is null or row/column is out of bounds.\n");
    return false;
  }

  if (row >= 0 && row < 3){
    subGridRow = 0;
  }
  else if (row >= 3 && row < 6){
    subGridRow = 1;
  }
  else{
    subGridRow = 2;
  }

  if (column >= 0 && column < 3){
    subGridColumn = 0;
  }
  else if (column >= 3 && column < 6){
    subGridColumn = 1;
  }
  else{
    subGridColumn = 2;
  }

  if (puzzleValidRow(puzzle, row) && puzzleValidColumn(puzzle, column) && puzzleValidSquare(puzzle, subGridRow, subGridColumn)){
    return true;
  }
  else{
    return false;
  }

}

/**************** puzzleValidRow() ****************/
/*
 * See puzzle.h for details
 */
bool
puzzleValidRow(puzzle_t* puzzle, int row){

  if (puzzle == NULL || row < 0 || row >= 9){
    fprintf(stderr, "Puzzle is null or row is out of bounds.\n");
    return false;
  }

  int check[9];
  for (int i = 0; i < 9; i++){
    check[i] = 0;
  }

  int value;
  for (int i = 0; i < 9; i++){
    value = puzzle->grid[row][i];
    if (value != 0){
      if (check[value - 1] == 0){
        check[value - 1] = 1;
      }
      else{
        return false;
      }
    }
  }

  return true;

}

/**************** puzzleValidColumn() ****************/
/*
 * See puzzle.h for details
 */
bool
puzzleValidColumn(puzzle_t* puzzle, int column){

  if (puzzle == NULL || column < 0 || column >= 9){
    fprintf(stderr, "Puzzle is null or column is out of bounds.\n");
    return false;
  }

  int check[9];
  for (int i = 0; i < 9; i++){
    check[i] = 0;
  }

  int value;
  for (int i = 0; i < 9; i++){
    value = puzzle->grid[i][column];
    if (value != 0){
      if (check[value - 1] == 0){
        check[value - 1] = 1;
      }
      else{
        return false;
      }
    }
  }

  return true;

}

/**************** puzzleValidSquare() ****************/
/*
 * See puzzle.h for details
 */
bool
puzzleValidSquare(puzzle_t* puzzle, int row, int column){

  if (puzzle == NULL || row < 0 || row >= 3 || column < 0 || column >= 3){
    fprintf(stderr, "Puzzle is null or row/column is out of bounds.\n");
    return false;
  }

  int check[9];
  for (int i = 0; i < 9; i++){
    check[i] = 0;
  }

  int value;
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      value = puzzle->grid[(row * 3) + i][(column * 3) + j];
      if (value != 0){
        if (check[value - 1] == 0){
          check[value - 1] = 1;
        }
        else{
          return false;
        }
      }
    }
  }

  return true;

}

/**************** puzzleSolved() ****************/
/*
 * See puzzle.h for details
 */
bool
puzzleSolved(puzzle_t* puzzle){

  if (puzzle == NULL){
    fprintf(stderr, "Puzzle is null.\n");
    return false;
  }

  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      if (puzzle->grid[i][j] == 0){
        return false;
      }
    }
  }

  return puzzleValid(puzzle);

}

/**************** puzzlePrint() ****************/
/*
 * See puzzle.h for details
 */
void
puzzlePrint(puzzle_t* puzzle, FILE* fp){

  if (puzzle != NULL && fp != NULL){
    for (int i = 0; i < 9; i++){
      for (int j = 0; j < 8; j++){
        fprintf(fp, "%d ", puzzle->grid[i][j]);
      }
      fprintf(fp, "%d\n", puzzle->grid[i][8]);
    }
  }

}

/**************** puzzleDelete() ****************/
/*
 * See puzzle.h for details
 */
void
puzzleDelete(puzzle_t* puzzle){

  for (int i = 0; i < 9; i++){
    free(puzzle->grid[i]);
  }
  free(puzzle->grid);
  free(puzzle);

}
