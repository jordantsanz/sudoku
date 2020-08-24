/* list.c - module for having a list_t struct used in creating a puzzle more efficiently
*
*
*
* Author: Alexandre Hamel, James Verschleiser, Jordan Sanz
* Date: 08/19/2020
* Class: CS50
* Professor: Xia Zhou
*
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "../libcs50/memory.h"


/**************************** file local global-variables *************/


/****************************** local types ************************/
typedef struct list {
    int* numberList;    /// array of numbers
    unsigned capacity; // number of things in it, for convenience
    int top; // keeps track of the end of the list
} list_t;

/**************** global types ****************/

/**************** global functions ****************/
/* that is, visible outside this file */

/**************** local functions ****************/
void swap(int numberList[], int i, int j);
void set_seed();
void reset_seed(int num);


/********************************* list_new() ************************/

list_t* list_new()
{   
    // allocate memory for list
    list_t* list = assertp(count_malloc(sizeof(list_t)), "cannot allocate memory for list");

    // allocate memory for array of pointers within list
    list->numberList = assertp(count_malloc(sizeof(int*) * 9 + sizeof(list->numberList)), "cannot allocate memory for inner array");
    list->capacity = 8;
    list->top = 8;

    // allocate memory for each inner slot of the list
    for (int i = 0; i < 9; i++){
        list->numberList[i] = i + 1; 
    }

    // shuffle list, looping through backwards; code adapted from techiedelight.com for randomizing
    for (int i = 8; i > -1; i--){

        int j = rand() % (i + 1);  // generates random index 0 <= j <= i in the list

        swap(list->numberList, i, j);
    }

    reset_seed(rand()); // reset seed to something else

    return list;

}

// helper function to swap the places of two indices in a list
void swap(int numberList[], int i, int j)
{
    int temp = numberList[i];
    numberList[i] = numberList[j];
    numberList[j] = temp;
}

/*********************************** list_pop *************************/
// code adapted from geeksforgeeks.com
int list_pop(list_t* list)
{   
    if (list->top == -1){ // then at end of stack
        return -1;
    }
    list->capacity -= 1;
    return list->numberList[list->top--]; // return thing on end of list
}

/******************************************** list_delete *************************/
void list_delete(list_t* list)
{
    // free the lists themselves
    free(list->numberList);
    free(list);
}

/**************************** reset_seed *************/
void reset_seed(int num)
{
    srand(time(NULL) % num * num);
}

/**************************** set_seed ************/
void set_seed(int num)
{
    srand(time(NULL));
}
