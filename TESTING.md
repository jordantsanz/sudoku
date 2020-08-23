# TESTING.md for Sudoku Final Project
## Alex Hamel, James Verschleiser, Jordan Sanz

# create

Testing for `create` is as follows:

0. Test of giving `create` too high of a `num_tiles`

1. Create a puzzle with 40 `num_tiles`, wait one second, and create another puzzle with 40 `num_tiles`, and check to see if they are different

2. Create a puzzle with 55 `num_tiles`

3. Check to see if each puzzle created passes `solve`