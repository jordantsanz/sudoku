/* groupnamepending testing - CS50
*
*Authors: Alex Hamel, James Verschleiser, Jordan Sanz
*
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../common/puzzle.h"
#include "../common/list.h"
#include "../solve/solve.h"
#include "../libcs50/memory.h"
#include "../create/create.h"

void waitFor (unsigned int secs);

int main(const int argc, const char* argv[]){

        /// fuzz testing loop
    if (argc != 2){
        printf("Not enough arguments. \n");
        return 1;
    }
    
    // number of tiles to test and number of times to run
    int num_tiles = 45;
    int num_times = atoi(argv[1]);
    int times_run = 0;

    // while still times to run
    while (num_times > times_run){
        
        puzzle_t* puzzletest = create(num_tiles);
        if (puzzletest == NULL){
            fprintf(stderr, "Failed to allocate memory for puzzletest.\n");
            exit(1);
        }
        if (!puzzleValid(puzzletest)){
            fprintf(stderr, "Failed create test.");
            puzzleDelete(puzzletest);
            exit(2);
        }
        int empty_counter = 0;
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++){
                if (puzzleGetTile(puzzletest, i, j) == 0){
                    empty_counter++;
                }
            }
        }
        if (empty_counter != num_tiles){
            fprintf(stderr, "Incorrect number of removed squares.\n");
            puzzleDelete(puzzletest);
            exit(3);
        }
        puzzle_t* buffer = puzzleNew();
        if (buffer == NULL){
            fprintf(stderr, "Failed to allocate memory for buffer.\n");
            puzzleDelete(puzzletest);
            exit(1);
        }
        int solutions = solve(puzzletest, buffer, 0);
        if (!puzzleSolved(buffer) || solutions != 1){
            fprintf(stderr, "Failed solve test.\n");
            puzzleDelete(puzzletest);
            puzzleDelete(buffer);
            exit(4);
        }

        waitFor(1);

        times_run += 1;

        puzzleDelete(puzzletest);
        puzzleDelete(buffer);

    }
    printf("Passed %d fuzz tests.\n", atoi(argv[1]));
    return 0;
}

// function taken from https://stackoverflow.com/questions/3930363/implement-time-delay-in-c

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}
