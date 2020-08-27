/*
 * puzzle.c - data structure for CS50 final project
 * 
 * See puzzle.h for details
 * 
 * Author: Alexandre Hamel, James Verschleiser, Jordan Sanz
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

  // allocate memory for puzzle structure
  puzzle_t* puzzle = malloc(sizeof(puzzle_t));
  if (puzzle == NULL){
    fprintf(stderr, "Couldn't allocate memory for puzzle\n");
    return NULL;
  }

  // allocate memory for 2-D array to conatin the puzzle
  int** array = (int**)calloc(9, sizeof(int*));

  // mem check
  if (array == NULL){
    fprintf(stderr, "Couldn't allocate memory for array\n");
    free(puzzle);
    return NULL;
  }

  // allocate memory for each row
  for (int i = 0; i < 9; i++){
    int* subArray = (int*)calloc(9, sizeof(int));
    if (subArray == NULL){

      // if at any point you fail to allocate memory for a row, free the already allocated rows, the array, and the puzzle, and return NULL
      fprintf(stderr, "Couldn't allocate memory for subArray\n");
      for (int j = 0; j < i; i++){  
        free(array[j]);
      }

      // free and return
      free(array);
      free(puzzle);
      return NULL;
    }
    // insert the pointer of the row to each row number, so that a call to any tile is array[row][column]
    array[i] = subArray;
  }

  // initialize all the tiles in the puzzle array as 0, or empty in the puzzle
  for (int i = 0; i < 9; i++){
    for(int j = 0; j< 9; j++){
      array[i][j] = 0;
    }
  }

  puzzle->grid = array;

  return puzzle;

}

/**************** puzzleLoad() ****************/
/*
 * See puzzle.h for details
 */
void
puzzleLoad(puzzle_t* puzzle, FILE* fp){

  // holds the line from the file
  char* line;
  // holds the pointer to the start of the line, so it can be freed later
  char* original;
  // keeps track of which line number you are on for placing the data in a row into the puzzle
  int lineNum = 0;
  // keeps track of which number within a line you are on for placing data in a column into the puzzle
  int numInLine;
  // variable to extract the char of the integer into an int using sscanf
  int value;
  // checks to make sure there are no consecutive digits in a file
  bool singleDigit;
  // checks to see if a digit was found within a line
  bool foundDigit;
  // for each line in the document you wish to load the puzzle from
  while((line = freadlinep(fp)) != NULL){

    numInLine = 0;
    singleDigit = false;
    foundDigit = false;
    original = line;
    // for each character in the line
    for( ; *line; ++line){
      // if it is a digit
      if (isdigit(*line) != 0){
        // make sure we haven't seen too many lines with numbers in the file
        if (lineNum > 8){
          fprintf(stderr, "Too many lines in source file.\n");
          free(original);
          return;
        }
        // if this is an isolated digit
        if (!singleDigit){
          singleDigit = true;
          foundDigit = true;
          // make sure we haven't seen too many entires in a line
          if (numInLine > 8){
            fprintf(stderr, "Too many entries in line %d.\n", lineNum);
            free(original);
            return;
          }
          // scan the number from line
          sscanf(line, "%d", &value);
          // insert it into the puzzle
          puzzle->grid[lineNum][numInLine] = value;
          // increment the entry number for that line
          numInLine++;
        }
        // if this is a consecutuve digit, then it isn't 0-9 and is an invalid puzzle file
        else{
          fprintf(stderr, "Puzzle file has two consecutive digits.\n");
          free(original);
          return;
        }
      }
      // if you find a space reset singleDigit as the next digit you find will not have a digit immediately preceeding it
      else if (isspace(*line) != 0){
        singleDigit = false;
      }
      // if we reach this point and the character isn't a digit, space, or control charcter like '\n' we have an invalid character and puzzle file
      else if (iscntrl(*line) == 0){
        fprintf(stderr, "Non-digit, non-space character in puzzle file.\n");
        free(original);
        return;
      }
    }
    
    // before we move to the next line make sure we extratcted 9 numbers for that row, if we have too few return
    if (numInLine < 9 && foundDigit){
      fprintf(stderr, "Too few entries in line %d.\n", lineNum);
      free(original);
      return;
    }
    // if we found a digit in this line we move on to the next row for insertion
    if (foundDigit){
      lineNum++;
    }
    free(original);
  }

  // if we reach the end of the file and have not found 9 rows, there are too few lines and it is an invalid character file
  if (lineNum < 9){
    fprintf(stderr, "Too few lines in source file.\n");
    return;
  }

  if (!puzzleValid(puzzle)){
    fprintf(stderr, "Puzzle file does not contain a valid sudoku puzzle.\n");
    return;
  }

}

/**************** puzzleGetTile() ****************/
/*
 * See puzzle.h for details
 */
int
puzzleGetTile(puzzle_t* puzzle, int row, int column){

  // if puzzle is not null and we have a coordinate within bounds of the puzzle
  if (puzzle != NULL && row >= 0 && row < 9 && column >= 0 && column < 9){
    // return the value at that coordinate
    return puzzle->grid[row][column];
  }
  else{
    fprintf(stderr, "Puzzle is null or row/column out of bounds.\n");
    // if there is an error return -1 for error handling
    return -1;
  }

}

/**************** puzzleSetTile() ****************/
/*
 * See puzzle.h for details
 */
void
puzzleSetTile(puzzle_t* puzzle, int row, int column, int value){

  // if puzzle is not null, we have a coordinate in bounds, and the value to be assigned is 0 representing empty or 1-9
  if (puzzle != NULL && row >= 0 && row < 9 && column >= 0 && column < 9 && value >= 0 && value < 10){
    // set the coordinate to the value
    puzzle->grid[row][column] = value;
  }
  // else print out about the error
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
  
  // check to make sure puzzle isn't null
  if (puzzle == NULL){
    fprintf(stderr, "Puzzle is null.\n");
    return false;
  }

  // for each row and each column, make sure they are valid rows/columns
  for (int i = 0; i < 9; i++){
    if (!puzzleValidRow(puzzle, i) || !puzzleValidColumn(puzzle, i)){
      return false;
    }
  }

  // for each 3x3 square, make sure they are valid
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      if (!puzzleValidSquare(puzzle, i, j)){
        return false;
      }
    }
  }

  return true;

}

/**************** puzzleValidUI() ****************/
/*
 * See puzzle.h for details
 */
bool
puzzleValidUI(){
  
  FILE* fp = fopen("./uipuzzles/newpuzzle.txt", "r");

  // check to make sure it can open
  if (fp == NULL){
      fprintf(stderr, "Failed to read from newpuzzle.txt.\n");
      return false;
  }

  puzzle_t* puzzle = puzzleNew();
  if (puzzle == NULL){
    fprintf(stderr, "Failed to allocate memory for puzzle.\n");
    fclose(fp);
    return false;
  }

  puzzleLoad(puzzle, fp);
  fclose(fp);

  bool valid = puzzleValid(puzzle);

  puzzleDelete(puzzle);
  return valid;

}

/**************** puzzleValidTile() ****************/
/*
 * See puzzle.h for details
 */
bool
puzzleValidTile(puzzle_t* puzzle, int row, int column){

  int subGridRow;
  int subGridColumn;

  // if the puzzle is null or the coordinate is out of bound, error handle
  if (puzzle == NULL || row < 0 || row >= 9 || column < 0 || column >= 9){
    fprintf(stderr, "Puzzle is null or row/column is out of bounds.\n");
    return false;
  }

  // find what 3x3 row your coordinate is in
  if (row >= 0 && row < 3){
    subGridRow = 0;
  }
  else if (row >= 3 && row < 6){
    subGridRow = 1;
  }
  else{
    subGridRow = 2;
  }

  // find what 3x3 column your coordinate is in
  if (column >= 0 && column < 3){
    subGridColumn = 0;
  }
  else if (column >= 3 && column < 6){
    subGridColumn = 1;
  }
  else{
    subGridColumn = 2;
  }

  // check to see if the coordinates row, column, and square are valid
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

  // check to make sure puzzle is not null and row is in bounds
  if (puzzle == NULL || row < 0 || row >= 9){
    fprintf(stderr, "Puzzle is null or row is out of bounds.\n");
    return false;
  }

  // initialize a 9 digit array with 0's to denote the cooresponding digit hasn't been found
  // ie [1-0(Not found), 2-0(Not Found), ..., 9-0(Not Found)]
  int check[9];
  for (int i = 0; i < 9; i++){
    check[i] = 0;
  }

  int value;
  // for each value in the given row
  for (int i = 0; i < 9; i++){
    value = puzzle->grid[row][i];

    // if this is a non-0 (ie non empty) value
    if (value != 0){
      // if we haven't seen this value before

      if (check[value - 1] == 0){
        // denote that value as seen by setting its tracker to 1, we value-1 to convert to index on 0
        check[value - 1] = 1;
      }

      // else if we have seen it, this isn't a valid row
      else{
        return false;
      }

    }
  }

  // if we reach this point all non-0 values in the row were unique, so return true
  return true;

}

/**************** puzzleValidColumn() ****************/
/*
 * See puzzle.h for details
 */
bool
puzzleValidColumn(puzzle_t* puzzle, int column){

  // check to make sure puzzle is not null and column is in bounds
  if (puzzle == NULL || column < 0 || column >= 9){
    fprintf(stderr, "Puzzle is null or column is out of bounds.\n");
    return false;
  }

  // initialize a 9 digit array with 0's to denote the cooresponding digit hasn't been found
  // ie [1-0(Not found), 2-0(Not Found), ..., 9-0(Not Found)]
  int check[9];
  for (int i = 0; i < 9; i++){
    check[i] = 0;
  }

  int value;
  // for each value in the given column
  for (int i = 0; i < 9; i++){
    value = puzzle->grid[i][column];

    // if this is a non-0 (ie non empty) value
    if (value != 0){

      // if we haven't seen this value before
      if (check[value - 1] == 0){

        // denote that value as seen by setting its tracker to 1, we value-1 to convert to index on 0
        check[value - 1] = 1;
      }

      // else if we have seen it, this isn't a valid column
      else{
        return false;
      }
    }
  }

  // if we reach this point all non-0 values in the column were unique, so return true
  return true;
}

/**************** puzzleValidSquare() ****************/
/*
 * See puzzle.h for details
 */
bool
puzzleValidSquare(puzzle_t* puzzle, int row, int column){

  // check to make sure puzzle is not null and 3x3 square is in bounds
  if (puzzle == NULL || row < 0 || row >= 3 || column < 0 || column >= 3){
    fprintf(stderr, "Puzzle is null or row/column is out of bounds.\n");
    return false;
  }

  // initialize a 9 digit array with 0's to denote the cooresponding digit hasn't been found
  // ie [1-0(Not found), 2-0(Not Found), ..., 9-0(Not Found)]
  int check[9];
  for (int i = 0; i < 9; i++){
    check[i] = 0;  // set every number in array to 0
  }

  int value;
  // for each value in the given 3x3 square
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      value = puzzle->grid[(row * 3) + i][(column * 3) + j];

      // if this is a non-0 (ie non empty) value
      if (value != 0){

        // if we haven't seen this value before
        if (check[value - 1] == 0){

          // denote that value as seen by setting its tracker to 1, we value-1 to convert to index on 0
          check[value - 1] = 1;
        }

        // else if we have seen it, this isn't a valid square
        else{
          return false;
        }
      }
    }
  }
  // if we reach this point all non-0 values in the square were unique, so return true
  return true;

}

/**************** checkPossible() ****************/
/*
 * See puzzle.h for details
 */
bool checkPossible(puzzle_t* puzzle, int row, int column, int n) {

  // check to make sure puzzle is not null and all parameters are in bounds
  if (puzzle == NULL || row < 0 || row >= 9 || column < 0 || column >= 9 || n < 0 || n >= 10){
    fprintf(stderr, "Puzzle is null or row/column/value out of bounds.\n");
    return false;
  }

  // copy the value currently in the coordinate
  int value = puzzleGetTile(puzzle, row, column);

  // set the coordinate to the value you want to try
  puzzleSetTile(puzzle, row, column, n);

  // if the tile is valid with the new value
  if (puzzleValidTile(puzzle, row, column)) {

    // reset the value
    puzzleSetTile(puzzle, row, column, value);

    // return true to tell user this is a possible entry
    return true;
  }

  else {
    // reset the value
    puzzleSetTile(puzzle, row, column, value);

    // return false to tell user this isn't a possible entry
    return false;
  }
}

/**************** puzzleSolved() ****************/
/*
 * See puzzle.h for details
 */
bool
puzzleSolved(puzzle_t* puzzle){

  // check to make sure the puzzle isn't null
  if (puzzle == NULL){
    fprintf(stderr, "Puzzle is null.\n");
    return false;
  }

  // check to make sure no tile is empty
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){

      // if we find an empty tile, ie 0
      if (puzzle->grid[i][j] == 0){

        // return false as the puzzle isn't solved
        return false;
      }
    }
  }

  return puzzleValid(puzzle);

}

/**************** puzzleCopy() ****************/
/*
 * See puzzle.h for details
 */
void
puzzleCopy(puzzle_t* puzzle1, puzzle_t* puzzle2){

  // check that both puzzles exist
  if (puzzle1 != NULL && puzzle2 != NULL){

    // loop through all tiles
    for (int i = 0; i < 9; i++){
      for (int j = 0; j < 9; j++){

        // set tile as whatever the other tile is
        puzzleSetTile(puzzle2, i, j, puzzleGetTile(puzzle1, i, j));
      }
    }
  }

}

/**************** puzzleCompare() ****************/
/*
 * See puzzle.h for details
 */
puzzle_t*
puzzleCompare(puzzle_t* puzzle1, puzzle_t* puzzle2){

  // check for puzzles
  if (puzzle1 == NULL || puzzle2 == NULL){
    fprintf(stderr, "puzzle passed to puzzleComapre is NULL.\n");
    return NULL;
  }

  // create new puzzle
  puzzle_t* compare = puzzleNew();
  if (compare == NULL){
    fprintf(stderr, "Error creating compare puzzle.\n");
    return NULL;
  }

  // grab each puzzle tile and check it, if same set to 0, if not, set to 1
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      if (puzzleGetTile(puzzle1, i, j) == puzzleGetTile(puzzle2, i, j)){
        puzzleSetTile(compare, i, j, 0);
      }
      else{
        puzzleSetTile(compare, i, j, 1);
      }
    }
  }

  return compare;

}

/**************** puzzlePrint() ****************/
/*
 * See puzzle.h for details
 */
void
puzzlePrint(puzzle_t* puzzle, FILE* fp){

  // if the puzzle and fp aren't null
  if (puzzle != NULL && fp != NULL){
    for (int i = 0; i < 9; i++){
      for (int j = 0; j < 8; j++){
        // print the first 8 elements of a row to the file
        fprintf(fp, "%d ", puzzle->grid[i][j]);
      }
      // print the final element of the row without an extra space and add a new line character
      fprintf(fp, "%d\n", puzzle->grid[i][8]);
    }
  }
  else if (puzzle != NULL && fp == NULL){
    for (int i = 0; i < 9; i++){
      for (int j = 0; j < 8; j++){
        // print the first 8 elements of a row to the file
        fprintf(stdout, "%d ", puzzle->grid[i][j]);
      }
      // print the final element of the row without an extra space and add a new line character
      fprintf(stdout, "%d\n", puzzle->grid[i][8]);
    }
  }

}

/**************** puzzleDelete() ****************/
/*
 * See puzzle.h for details
 */
void
puzzleDelete(puzzle_t* puzzle){

  // for each row in the 2-D array
  for (int i = 0; i < 9; i++){
    // free the memory of that row
    free(puzzle->grid[i]);
  }
  // free the memory of the array that used to point to each row
  free(puzzle->grid);
  // free the puzzle struct itself
  free(puzzle);

}
