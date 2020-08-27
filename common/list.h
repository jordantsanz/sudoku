/*
 * list.h - interface for list module for CS50 final project
 * 
 * contains the interface for the list module in the sudoku common library
 * 
 * Author: Alexandre Hamel, James Verschleiser, Jordan Sanz
 * Date: 08/19/2020
 * Class: CS50
 * Professor: Xia Zhou
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../libcs50/memory.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct list list_t;

/**************** global types ****************/

/**************** global functions ****************/

/************************************************ list_new ****************************/
/*
* Creates memory for a new list and returns a pointer to that list
* Will return NULL if cannot allocate memory for the list
* list will have numbers 1-9 in a random order
* list should be deleted by calling list_delete()
*/
list_t* list_new();

/************************************************ list_pop ***************************/
/* Pops off the number stored at the last index of the list and returns it;
* Deletes the number from the list as well as frees the slot of the list
* Decrements the length of the list by one
* Returns int
*/
int list_pop(list_t* list);

/************************************************* list_delete **************************/
/* deletes a given list
* frees each slot that remains in the list
* 
*/
void list_delete(list_t* );

/**************** local functions ****************/

/************************************** swap ***************************/
/* Helper function used by list_new to swap two values in a list
* Takes two indices in a list and swaps them in the given list; no return
*/
void swap(list_t* list, int i, int j);

/********************* seed functions ***********/
/* Set the randomizing seed for the start of the program based on time
* Then changes the randomizing seed throughout the program
*/
void set_seed(int time);
void reset_seed(int num);
