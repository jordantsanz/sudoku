/*
 * puzzletest.c - a test file for the puzzle_t struct
 * 
 * usage: ./puzzletest
 * 
 * Author: Alexandre Hamel
 * Date: 08/18/2020
 * Class: CS50
 * Professor: Xia Zhou
 */

#include <stdio.h>
#include <stdlib.h>
#include "puzzle.h"

/* **************************************** */
int main() 
{

  //assumes the approriate files are present ../examplepuzzles

  //puzzleNew
  //error handling
  FILE* fp;
  puzzle_t* puzzle;
  puzzle = puzzleNew();
  //too many rows in source file
  fp = fopen("../examplepuzzles/puzzletoomanyrows.txt", "r");
  if (fp == NULL){
    fprintf(stderr, "Couldn't open file.\n");
    exit(1);
  }
  puzzleLoad(puzzle, fp);
  fclose(fp);

  //too few rows in source file
  fp = fopen("../examplepuzzles/puzzlenotenoughrows.txt", "r");
  if (fp == NULL){
    fprintf(stderr, "Couldn't open file.\n");
    exit(3);
  }
  puzzleLoad(puzzle, fp);
  fclose(fp);

  //too many columns in source file
  fp = fopen("../examplepuzzles/puzzletoomanycolumns.txt", "r");
  if (fp == NULL){
    fprintf(stderr, "Couldn't open file.\n");
    exit(5);
  }
  puzzleLoad(puzzle, fp);
  fclose(fp);

  //too few columns in source file
  fp = fopen("../examplepuzzles/puzzlenotenoughcolumns.txt", "r");
  if (fp == NULL){
    fprintf(stderr, "Couldn't open file.\n");
    exit(7);
  }
  puzzleLoad(puzzle, fp);
  fclose(fp);

  //two conscutive digits in source file / value > 9
  fp = fopen("../examplepuzzles/puzzleconsecutivedigits.txt", "r");
  if (fp == NULL){
    fprintf(stderr, "Couldn't open file.\n");
    exit(9);
  }
  puzzleLoad(puzzle, fp);
  fclose(fp);

  //non-digit, non-space character in source file
  fp = fopen("../examplepuzzles/puzzlewrongchar.txt", "r");
  if (fp == NULL){
    fprintf(stderr, "Couldn't open file.\n");
    exit(11);
  }
  puzzleLoad(puzzle, fp);
  fclose(fp);

  //realtest
  fp = fopen("../examplepuzzles/puzzle1.txt", "r");
  if (fp == NULL){
    fprintf(stderr, "Couldn't open file.\n");
    exit(13);
  }
  puzzleLoad(puzzle, fp);
  fclose(fp);

  //realtest wierd whitespace
  puzzle_t* puzzleWhitespace;
  puzzleWhitespace = puzzleNew();
  fp = fopen("../examplepuzzles/puzzlewhitespace.txt", "r");
  if (fp == NULL){
    fprintf(stderr, "Couldn't open file.\n");
    exit(15);
  }
  puzzleLoad(puzzleWhitespace, fp);
  fclose(fp);

  //puzzleGetTile
  //error handling
  //puzzle null
  int value;
  value = puzzleGetTile(NULL, 0, 0);
  if (value == -1){
    fprintf(stdout, "Puzzle NULL error handled.\n");
  }
  else{
    fprintf(stderr, "Puzzle NULL error not handled.\n");
    exit(17);
  }

  //row OOB
  value = puzzleGetTile(puzzle, -1, 0);
  if (value == -1){
    fprintf(stdout, "Row OOB error handled.\n");
  }
  else{
    fprintf(stderr, "Row OOB error not handled.\n");
    exit(18);
  }
  value = puzzleGetTile(puzzle, 9, 0);
  if (value == -1){
    fprintf(stdout, "Row OOB error handled.\n");
  }
  else{
    fprintf(stderr, "Row OOB error not handled.\n");
    exit(18);
  }

  //column OOB
  value = puzzleGetTile(puzzle, 0, -1);
  if (value == -1){
    fprintf(stdout, "Column OOB error handled.\n");
  }
  else{
    fprintf(stderr, "Column OOB error not handled.\n");
    exit(19);
  }
  value = puzzleGetTile(puzzle, 0, 9);
  if (value == -1){
    fprintf(stdout, "Column OOB error handled.\n");
  }
  else{
    fprintf(stderr, "Column OOB error not handled.\n");
    exit(19);
  }

  //realtest
  value = puzzleGetTile(puzzle, 7, 3);
  if (value == 4){
    fprintf(stdout, "Successfully got Tile.\n");
  }
  else{
    fprintf(stderr, "Failed to get tile.\n");
    exit(20);
  }

  //puzzleSetTile
  //error handling
  //puzzle null
  puzzleSetTile(NULL, 0, 0, 0);

  //row OOB
  puzzleSetTile(puzzle, -1, 0, 0);
  puzzleSetTile(puzzle, 9, 0, 0);

  //column OOB
  puzzleSetTile(puzzle, 0, -1, 0);
  puzzleSetTile(puzzle, 0, 9, 0);

  //value OOB
  puzzleSetTile(puzzle, 0, 0, -1);
  puzzleSetTile(puzzle, 0, 0, 10);

  //realtest
  puzzleSetTile(puzzle, 0, 0, 1);
  if (puzzleGetTile(puzzle, 0, 0) == 1){
    fprintf(stdout, "Succesfully set tile.\n");
  }
  else{
    fprintf(stderr, "Failed to set tile.\n");
    exit(21);
  }

  puzzleSetTile(puzzle, 0, 0, 5);

  fprintf(stdout, "Regular:\n");
  puzzlePrint(puzzle, stdout);
  puzzleDelete(puzzle);

  fprintf(stdout, "Whitespace:\n");
  puzzlePrint(puzzleWhitespace, stdout);
  puzzleDelete(puzzleWhitespace);

  return 0;

}
