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