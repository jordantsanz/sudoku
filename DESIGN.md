# DESIGN.md
## Alex Hamel, James Verschleiser, Jordan Sanz; CS50, Summer 2020

### Sudoku Project Design Spec

The **creator** generates a random, solvable sudoku puzzle by first creating a completed puzzle, and then removing numbers from that puzzle to create a solvable puzzle. 
It generates a completed puzzle by looping through each tile of the puzzle and placing a valid number there; after, it removes numbers up until a solvable puzzle remains, checking after each number removal to make sure that there is still only one solution.

The **solver** takes an input of any solveable sudoku puzzle and completes it, filling in the missing spaces with numbers that are valid in regards to the rules of sudoku. It loops through all of the tiles on the gameboard and tries every possible solution, backtracking when a current possible solution becomes impossible.


### User interface

The programs's interface with the user is on the command-line and then through the keyboard.

The initial command has no arguments

```
./puzzle
```

After that the user has the option to create a puzzle by entering

```
create
```

And then solve the puzzle by entering

```
solve
```

### Inputs and outputs

Input: the only inputs are keyboard generated; see the User Interface above.

Output: For `create` command, the program outputs a puzzle with a unique solution. For `solve` command, the program outputs a fully solved puzzle.


### Functional decomposition into modules

We anticipate the following modules or functions:

 1. *main*, which parses arguments and initializes other modules
 2. *create*, which generates a random puzzle that is solveable
 3. *solve*, which solves the blanks in any random, unsolved sudoku puzzle

And some helper modules that provide data structures:

 1. *puzzle* of arrays of numbers stored within a puzzle's tiles
 2. *list* of an array of numbers that acts as a stack, allowing for a randomized selection of numbers

### Pseudo code for logic/algorithmic flow

1. execute from keyboard as shown in the User Interface

For `create`:
2. Set a random seed based off of the current time
3. Create a blank puzzle
4. Call *fillInSquare*, which begins to fill in the squares of the puzzle by:
    5. Creating a `list_t list` by calling *list_new*
    6. Calling *inputSquareTile*, passing in the starting x and y values of (0,0); this function does the following for every tile:
        7. Initialize value and return value variables
        8. Call *list_pop* to get a random value from 1-9, and while there are still numbers in the list to pop:
            9. Set the value of the number at those x and y coordinates of that tile to be the random, popped value
            10. If the puzzle is still valid after that value is entered:
                11. If the y coordinate isn't at the end of the puzzle (on the last column):
                    12. recursively call *inputSquareTile* and add one to the y coordinate, and set `returnValue` as the return value of this call
                13. If the y coordinate is on the last column, but the x coordinate isn't on the last row:
                    14. recursively call *inputSquareTile* and add one to the x coordinate, and set `returnValue` to the return value of this call
                15. If the x coordinate is on the last row and the y coordinate is on the last column:
                    16. Set `returnValue` to 0
                17. If `returnValue` is 0:
                    18. Delete the `list` by calling *list_delete* and return `returnValue`
            19. If the set value is not valid, then simply continue in the while loop
        20. If there are no values in the list left, then:
            21. Delete the `list` by calling *list_delete*
            22. Set the current tile's value of the puzzle back to `0`
            23. Return -1
            24. The program then backtraces until a puzzle is generated successfully, and *fillInSquare* returns.
25. Once the puzzle has been generated correctly, begin to remove numbers by doing the following:
    26. Select a random x-y pairing
    27. Attempt to remove that number and replace it with 0, and save the removed number temporarily
        28. Pass the puzzle as it stands to solver
        29. If the puzzle is still solveable, keep the 0 in the empty spot, discard the temporarily saved number
            30. continue with another random x-y pairing until enough numbers are removed
        31. Else, replace the number and start again with a random x-y pairing
32. Once enough numbers have been removed, print the puzzle to stdout
33. Exit successfully

For `solve`:
2. loops through x-values from 0-8
    3. loops through y-values from 0-8
        4. if the current square is empty
            5. for int from 1-9
                6. if the int doesn't break the rules of sudoku
                    7. set the current square to that number
                    8. if multiple solutions haven't been found yet
                        9. run solve recursively with this new board
                    10. set the current square equal to 0
            11. return current number of solutions
12. if the puzzle is solved
    13. prints out the solved board
    14. increments solved_count
15. return current number of solutions


**solveable** means that each number is a unique number in that row, column, and square. The puzzle is visualized as a 9x9 square of 3x3 squares. A solveable puzzle means that there is a solution where each tile in the puzzle can be filled with a number from 1-9, where each number is unique in its row, column, and square. A solveable puzzle is also not completed, and has at least 40 missing numbers from the puzzle. 

### Dataflow through modules

For creator:
 1. *main* parses parameters to validate that there are none. A valid signal is passed to creator. 
 2. *creator* randomly generates a puzzle by passing data to getter and setter helper functions, as well as functions `checkRow`, `checkColumn`, `checkSquare`, and `isValidPuzzle` to validate that the puzzle being built is valid. The *creator* then passes the solveable puzzle to *solver*.
 3. *solver* takes the puzzle and attempts to solve it, returning either a completed puzzle if *creator* ran as expected or an error message if the puzzle is unsolveable. It passes tile values to `checkRow`, `checkColumn`, and `checkSquare` in the `common` directory. *Solver* outputs the completed puzzle to `stdout`. 

For solver:
1. *main* parses parameters to validate that there was a valid puzzle input. The valid puzzle is then sent to the *solver*.
2. *solver* takes the puzzle and attempts to solve it, returning either a completed puzzle if *creator* ran as expected or an error message if the puzzle is unsolveable. It passes tile values to `checkRow`, `checkColumn`, and `checkSquare` in the `common` directory. *Solver* outputs the completed puzzle to `stdout`. 

### Major data structures

We use a data structure to hold the puzzle.

The structure holds an array of arrays. The main array has room for nine arrays that each hold nine integers. Each sub-array corresponds to one of the rows of the puzzles.

We also have created set and get functions to aid in updating the puzzle as we solve it.

### Testing plan

*Unit testing*.  A small test program to test each module to make sure it does what it's supposed to do.

*Integration testing*.  Use puzzles we find online to validate that `solve` works correctly and the solution it outputs is valid.

0. Test **creator** to make sure that there are no arguments given to it beyong the program name.

0. Test **solver** for correct argument parsing from the command-line by giving it no puzzle.

0. Test **solver** for correct argument parsing from the command-line by giving it multiple commands.

1. Test **solver** with a given, already completed puzzle.

2. Test **solver** with a given, unsolveable puzzle.

3. Test **solver** with a given, solveable puzzle with one solution.

4. Test **solver** with a given, solveable puzzle with multiple solutions.

5. Test **creator** by checking to see if the generated puzzle is actually solveable by passing the puzzle to **solver**. 