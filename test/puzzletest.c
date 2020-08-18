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
  //too many rows in source file
  fp = fopen("../examplepuzzles/puzzletoomanyrows.txt", "r");
  if (fp == NULL){
    fprintf(stderr, "Couldn't open file.\n");
    exit(1);
  }
  puzzle = puzzleNew(fp);
  fclose(fp);
  if (puzzle == NULL){
    fprintf(stdout, "Too many rows in source file error handled.\n");
  }
  else{
    fprintf(stderr, "Too many rows error not handled.\n");
    exit(2);
  }

  //too few rows in source file
  fp = fopen("../examplepuzzles/puzzlenotenoughrows.txt", "r");
  if (fp == NULL){
    fprintf(stderr, "Couldn't open file.\n");
    exit(1);
  }
  puzzle = puzzleNew(fp);
  fclose(fp);
  if (puzzle == NULL){
    fprintf(stdout, "Too few rows in source file error handled.\n");
  }
  else{
    fprintf(stderr, "Too few rows error not handled.\n");
    exit(2);
  }

  //too many columns in source file
  fp = fopen("../examplepuzzles/puzzletoomanycolumns.txt", "r");
  if (fp == NULL){
    fprintf(stderr, "Couldn't open file.\n");
    exit(1);
  }
  puzzle = puzzleNew(fp);
  fclose(fp);
  if (puzzle == NULL){
    fprintf(stdout, "Too many columns in source file error handled.\n");
  }
  else{
    fprintf(stderr, "Too many columns error not handled.\n");
    exit(3);
  }

  //too few columns in source file
  fp = fopen("../examplepuzzles/puzzlenotenoughcolumns.txt", "r");
  if (fp == NULL){
    fprintf(stderr, "Couldn't open file.\n");
    exit(1);
  }
  puzzle = puzzleNew(fp);
  fclose(fp);
  if (puzzle == NULL){
    fprintf(stdout, "Too few columns in source file error handled.\n");
  }
  else{
    fprintf(stderr, "Too few columns error not handled.\n");
    exit(3);
  }

  //two conscutive digits in source file / value > 9
  fp = fopen("../examplepuzzles/puzzleconsecutivedigits.txt", "r");
  if (fp == NULL){
    fprintf(stderr, "Couldn't open file.\n");
    exit(1);
  }
  puzzle = puzzleNew(fp);
  fclose(fp);
  if (puzzle == NULL){
    fprintf(stdout, "Consecutive digits in source file error handled.\n");
  }
  else{
    fprintf(stderr, "Consecutive digits error not handled.\n");
    exit(4);
  }

  //non-digit, non-space character in source file
  fp = fopen("../examplepuzzles/puzzlewrongchar.txt", "r");
  if (fp == NULL){
    fprintf(stderr, "Couldn't open file.\n");
    exit(1);
  }
  puzzle = puzzleNew(fp);
  fclose(fp);
  if (puzzle == NULL){
    fprintf(stdout, "Wrong character in source file error handled.\n");
  }
  else{
    fprintf(stderr, "Wrong character digits error not handled.\n");
    exit(4);
  }

  //realtest
  fp = fopen("../examplepuzzles/puzzle1.txt", "r");
  if (fp == NULL){
    fprintf(stderr, "Couldn't open file.\n");
    exit(1);
  }
  puzzle = puzzleNew(fp);
  fclose(fp);
  if (puzzle != NULL){
    fprintf(stdout, "Successfully created puzzle.\n");
  }
  else{
    fprintf(stderr, "Failed to create puzzle.\n");
    exit(5);
  }

  //realtest wierd whitespace
  puzzle_t* puzzleWhitespace;
  fp = fopen("../examplepuzzles/puzzlewhitespace.txt", "r");
  if (fp == NULL){
    fprintf(stderr, "Couldn't open file.\n");
    exit(1);
  }
  puzzleWhitespace = puzzleNew(fp);
  fclose(fp);
  if (puzzle != NULL){
    fprintf(stdout, "Successfully created whitespace puzzle.\n");
  }
  else{
    fprintf(stderr, "Failed to create whitespace puzzle.\n");
    exit(5);
  }

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
    exit(6);
  }

  //row OOB
  value = puzzleGetTile(puzzle, -1, 0);
  if (value == -1){
    fprintf(stdout, "Row OOB error handled.\n");
  }
  else{
    fprintf(stderr, "Row OOB error not handled.\n");
    exit(7);
  }
  value = puzzleGetTile(puzzle, 9, 0);
  if (value == -1){
    fprintf(stdout, "Row OOB error handled.\n");
  }
  else{
    fprintf(stderr, "Row OOB error not handled.\n");
    exit(7);
  }

  //column OOB
  value = puzzleGetTile(puzzle, 0, -1);
  if (value == -1){
    fprintf(stdout, "Column OOB error handled.\n");
  }
  else{
    fprintf(stderr, "Column OOB error not handled.\n");
    exit(8);
  }
  value = puzzleGetTile(puzzle, 0, 9);
  if (value == -1){
    fprintf(stdout, "Column OOB error handled.\n");
  }
  else{
    fprintf(stderr, "Column OOB error not handled.\n");
    exit(8);
  }

  //realtest
  value = puzzleGetTile(puzzle, 7, 3);
  if (value == 4){
    fprintf(stdout, "Successfully got Tile.\n");
  }
  else{
    fprintf(stderr, "Failed to get tile.\n");
    exit(9);
  }

  fprintf(stdout, "Regular:\n");
  puzzlePrint(puzzle, stdout);
  puzzleDelete(puzzle);

  fprintf(stdout, "Whitespace:\n");
  puzzlePrint(puzzleWhitespace, stdout);
  puzzleDelete(puzzleWhitespace);

  return 0;

}
