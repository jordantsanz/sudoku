### puzzle

#### Overview
This is the data structure that holds the actual sudoku puzzle and has functions to operate on it. These functions include creating a bvlank puzzle, loading the puzzle in from a file, getters and setters for the puzzle, a series of functions to see if the puzzle is valid, if an individual tile is valid, if a row is valid, if a column is valid, if a 3x3 square is valid, if a puzzle would still be valid after inserting a new number, if the puzzle is solved, a print function, and a delete function for the structure. These fucntions are used internally in the file and also by create and solve to faciliate the process of checking for validity within the rules of the game of sudoku, namely each row, column, and 3x3 square may only have the numbers 1-9 appear once in each.

#### Pseudocode
puzzleNew()
0. Initialize memory for the puzzle structure
1. Create an array (row pointers) of arrays (rows)
2. Turn that array into a 2-D array by crearting an array for each row
3. For each tile in our full array
    4. Initialize the space to empty, ie 0
5. Assign the array to the puzzle struct
6. Return the struct

puzzleLoad()
1. For each line in the puzzle file
    2. For each charcter in the line
        3. Make sure we don't have too many rows
        4. Make sure we don't have too many columns
        5. Assign the value from the file to the appropriate coordinate
        6. Make sure we don't have consecutive digits
        7. Make sure we don't have a non-digit, space, or control character
    3. Make sure there weren't too few columns
4. Make sure we don't have too few lines

puzzleGetTile()
1. Return value within grid for coordinate

puzzleSetTile()
1. Assign given value to coordinate within grid

puzzleValid()
1. For each row and column
    2. Check if the row/column is valid
3. For each 3x3 sqaure
    4. Check if the square is valid

puzzleValidTile()
1. Find the 3x3 square for your coordinate
2. Check if the coordinates row, column, and square are valid

puzzleValidRow()
1. Create an array of 9 0's which correspond to the values 1-9
2. For each value in the given row
    3. If this is the first time we see it, set the corresponding array value to 1
    4. If this is the second time we see it, this isn't a valid row return false
5. If we reach here in the code all values were unique, return true

puzzleValidColumn()
1. Create an array of 9 0's which correspond to the values 1-9
2. For each value in the given column
    3. If this is the first time we see it, set the corresponding array value to 1
    4. If this is the second time we see it, this isn't a valid column return false
5. If we reach here in the code all values were unique, return true

puzzleValidSquare()
1. Create an array of 9 0's which correspond to the values 1-9
2. For each value in the given 3x3 square
    3. If this is the first time we see it, set the corresponding array value to 1
    4. If this is the second time we see it, this isn't a valid 3x3 square return false
5. If we reach here in the code all values were unique, return true

checkPossible()
1. Set the coordinate to the given value
2. Check that tile with puzzleValidTile
3. Reset the value
4. return true if puzzleValidTile returns true, false if it returns false

puzzleSolved()
1. For each tile in the puzzle
    2. Check to make sure the tile is filed
3. Run puzzleValid and return waht it returns

puzzlePrint()
1. For each row
    2. For the first 8 elements in a row
        3. Print the element and a space
    4. Print the final element and a new line character

puzzleDelete()
1. For each row in the array
    2. Free the memory for that row
3. Free the array that held the pointer to each row
4. Free the puzzle struct

#### Conventions

This puzzle.c file has no main and is meant to act simply as a data structure to be used by solve and create. You can test the data structure by running ./test/puzzletest/puzzletest

#### Data Structures

This is a data structure itself and implements an array of arrays (2-D array) to hold the values of the sudoku puzzle.

#### Assumptions

If the user passes an invalidly structured puzzle file (two consecutive digits, non-digit/space/control characters, too few/many rows/columns, etc.) to puzzleLoad, the puzzle will take and store values until it encounters an error and will not revert it back to its original form should a invalidly structured file be passed

#### Exit Codes

puzzle.c:
No Exit Codes

puzzletest.c:
1: File can't be opened
2: Puzzle null for getter
3: Row OOB for getter
4: Column OOB for getter
5: Failed to get tile
6: Failed to set tile
7: Failed to validate puzzle
8: Error with validate subfunction
9: Error with puzzleValidTile
10: Error with checkPossible
11: Error with puzzleSolved
12: Error with puzzleCopy

#### Resource Management

Puzzle array takes up the minimum amount of space necessary. All memory are freed before exits and returns.

#### Persistent Storage

Only things puzzle.c stores longer than the execution of its code is if you print the puzzle to file. That file will keep the printed puzzle.


## Solve

The solve library contains a solve function that takes a puzzle, an integer, and a FILE/stdout as arguments. 

The function will test to see if there is a solution for the given sudoku puzzle. If a solution exists then it will print the sudoku puzzle to the given file/console. The function also keeps track of how many solutions have been found so far. However, it will only search for valid solutions until it finds at most 2. Therefore, the function can tell you if the given puzzle has no solution, a unique solution, or multiple solutions.

### Inputs and Outputs

Input: a puzzle, an integer, and a FILE/stdout

Output: if a solution exists then the solved puzzle, if no solution exists than a message saying so, and if multiple solutions exist then 2 solutions and a message saying multiple solutions exist.

### Pseudocode

1. loops through x-values from 0-8
    2. loops through y-values from 0-8
        3. if the current square is empty
            4. for int from 1-9
                5. if the int doesn't break the rules of sudoku
                    6. set the current square to that number
                    7. if multiple solutions haven't been found yet
                        8. run solve recursively with this new board
                    9. set the current square equal to 0
            10. return current number of solutions
11. if the puzzle is solved
    12. prints out the solved board
    13. increments solved_count
14. return current number of solutions

## Create

The create library contains a create function that takes an integer as an argument. 

The function will create a 9x9, blank sudoku puzzle, with each tile filled in with a zero. It will then loop through all of the tiles in the sudoku grid, and overwrite each tile with a randomly selected integer from 1-9, then checking to make sure that the puzzle being created is still a *valid* sudoku puzzle.

Once it fills the entire sudoku grid, the puzzle will be a fully-completed sudoku puzzle. `create` will then randomly select tiles from the grid, and replace the filled-in values with zero; after removing each tile, it will check to make sure that the puzzle still has only *one* solution by calling `solve`. If the puzzle has more than one solution, `create` will put a zero back in the tile that it removed from, and will try again with another tile. This will end when the number of tiles successfully removed is the *integer* passed in as an argument.

### Inputs and Outputs

Input: `int num_tiles`

Output: A solveable 9x9 `puzzle_t* puzzle`, printed to *stdout* and returned by `create`. This `puzzle` will have only one solution, and will have `int num_tiles` zeros in the grid. 

### Pseudocode

```
1. Check to see if `int num_tiles` is -1
    2. If it is -1, set `num_tiles` as 40, giving it the default value for removing tiles
    3. Else, keep `num_tiles` as the passed-in value
4. Call *set_seed*, which:
    5. Sets the `random generator` seed as the current time
6. Create a new `puzzle_t* puzzle` by calling *puzzleNew*
7. Call *fillInSquare* to fill in the tiles of the puzzle by:
    8. Creating a new `list_t* list` by calling *list_new*
    9. Saving the return value of, passing the `list`, `puzzle`, and a `startX` and `startY` of 0 and 0 to, and calling *inputSquareTile*, which:
        10. Initializes an `int value` and `int returnVal`
        11. While `value`, which is the return value of *list_pop* of `list` is not -1:
            12. Call *puzzleSetTile* to set the tile at `x`, `y` in the `puzzle` to `value`
            13. Call *puzzleValidTile* to see if the tile at that `x` and `y` with the new `value` still makes a *valid* puzzle, meaning that no sudoku rules are violated
            14. If `y` is not on the last, 9th column:
                15. Set `returnVal` to the value of *inputSquareTile*, passing in the same `puzzle` and `x`, but passing in `y+1` as `y` and `list_new()` as `list`
            16. Else, if `y` is on the last column, but `x` is not on the last row:
                17. Set `returnVal` to the value of *inputSquareTile*, passing in the same `puzzle`, but passing in `x+1` as `x`, `0` as `y`, and `list_new()` as `list`
            18. Else:
                19. Set `returnVal` to 0, since the `x` and `y` at this point are the last tile to be checked
            20. If `returnVal` is `0`:
                21. Delete the `list` by calling *list_delete*
                22. Return `returnVal`
        23. If the while loop is broken out of, this means that the `list` is empty, and every number in this list has failed to create a *valid* puzzle with the current tile. Thus, the following happens:
            24. The `list` is deleted by calling *list_delete*
            25. The current tile at `x`, `y` in teh `puzzle` is set to 0 by calling *puzzleSetTile*
            26. Return `-1`
27. The puzzle will now be completely filled in. Call *puzzleSolved* to check that it was completely filled in validly
28. Call *puzzleRemoveTiles*, passing in the `puzzle` and the `num_tiles` and:
    29. Set `int x` to -1, `int y` to -1, `int tile` to 0, `int removed_tiles` to 0, and initialize `puzzle_t* puzzleCopy`
    30. While `removed_tiles` is less than `num_tiles`:
        31. While `tile` is 0:
            32. Set `x` to a random number mod 9
            33. Set `y` to a random number mod 9
            34. Set `tile` to the puzzle tile at that `x` and `y` by calling *puzzleGetTile*
        35. Set the tile at `x` and `y` in the `puzzle` to 0
        36. Create a `puzzleCopy` puzzle by calling *makePuzzleCopy*, which:
            37. Creates a new `puzzle_t` puzzle pointer
            38. Loops through all of the tiles of the main `puzzle` and copies the values over to the `puzzleCopy`
        39. If there is not only one solution to the `puzzleCopy`, found by calling *solve*:
            40. Set the tile at `x` and `y` in `puzzle` back to the value of `tile`
        41. Else, increase `removed_tiles` by one
        42. Delete `puzzleCopy` and set `tile` to 0
43. Once this occurs, call *solve* again to check one final time that the `puzzle` has one solution
44. Return `puzzle`
```

### Files 

* `create.c` - The implementation for create library
* `create.h` - The interface for create library
* `Makefile` - Makefile for create library
* `README.md` - Documentation on the create library

### Error Handling

- If memory cannot be allocated for `puzzle_t* puzzle`, then print an error and exit
- If the puzzle could not be filled in correctly, an error message is printed and `NULL` is returned
- If the puzzle was not completely filled in with a valid solution, print error and return with `NULL`
- If the puzzle has more than one solution, print error and return with `NULL`
- If memory for a new `list` could not be allocated, print error and exit
- If `num_tiles` is greater than 55, print error and return `NULL`
