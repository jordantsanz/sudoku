# TESTING.md for Sudoku Final Project
## Alex Hamel, James Verschleiser, Jordan Sanz

### puzzle

testing is in test/puzzletest

0. Test puzzleLoad with a too many rows

0. Test puzzleLoad with too few rows

0. Test puzzleLoad with too many columns

0. Test puzzleLoad with too few columns

0. Test puzzleLoad with consecutive digits

0. Test puzzleLoad with an invalid character

    1. Test puzzleLoad with a basic puzzle

    2. Test puzzleLoad with a wierdly whitespaced file

0. Test puzzleGetTile with a null puzzle

0. Test puzzleGetTile with OOB rows

0. Test puzzleGetTile with OOB columns

    3. Test getting an expected result from a puzzle with puzzleGetTile

0. Test puzzleSetTile with a null puzzle

0. Test puzzleSetTile with OOB rows

0. Test puzzleSetTile with OOB columns

0. Test puzzleSetTile with OOB values

    4. Test setting and getting the same value with puzzleSetTile

5. Test if puzzleValid recognizes a valid puzzle

6. Test if puzzleValid recognizes an invalid puzzle

7. Test subfunctions used by puzzleValid for the previous tests of 5 and 6

8. Test puzzleValidTile with valid and invalid tiles

9. Test checkPossible against expected results

10. Test puzzleSolved on a unsolved and solved puzzle

11. Test puzzleCopy from the solved puzzle to an initially empty puzzle to see if it copies it over.

12. Test puzzlePrint to console

13. Test puzzleDelete by running valgrind on ./puzzletest

### create

Testing for `create` is as follows:

0. Test of giving `create` too high of a `num_tiles`

1. Create a puzzle with 40 `num_tiles`, wait one second, and create another puzzle with 40 `num_tiles`, and check to see if they are different

2. Create a puzzle with 55 `num_tiles`

3. Check to see if each puzzle created passes `solve`

### solve

Testing for `solve` is as follows:

0. Test on normal solvable puzzle

1. Test on empty puzzle

2. Test on puzzle with no solutions

3. Test on puzzle with multiple solutions

### fuzz

Tests the program as a whole. Runs a loop that constantly creates new sudoku puzzles and makes sure they have only one unique solutions. Then solves the puzzle and makes sure the solution is valid.
