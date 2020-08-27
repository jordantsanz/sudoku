/* groupnamepending testing - CS50
*
*Authors: Alex Hamel, James Verschleiser, Jordan Sanz
*
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../common/puzzle.h"
#include "../common/list.h"
#include "../solve/solve.h"
#include "../libcs50/memory.h"
#include "../create/create.h"

int main(const int argc, const char* argv[]){

        /// fuzz testing loop
    if (argc != 2){
        print("Not enough arguments. \n");
        return 1;
    }
    
    // number of tiles to test and number of times to run
    int num_tiles = 45;
    int num_times = (int) argv[2];
    int times_run = 0;

    // while still times to run
    while (num_times > times_run){
        
        puzzle_t* puzzletest = create(num_tiles);
        puzzlePrint(puzzletest, stdout);
        solve(puzzletest, NULL, 0, stdout);
        waitFor(1);

        times_run += 1;

        puzzleDelete(puzzletest);

    }
    return 0;
}