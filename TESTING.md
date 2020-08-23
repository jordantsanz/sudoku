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

11. Test puzzlePrint to console

12. Test puzzleDelete by running valgrind on ./puzzletest
