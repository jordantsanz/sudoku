# TIMELINE.md

Deadlines:
- DESIGN.md - August 21
- Project - August 27

Checklist:


- Decide on a data structure
    - 2D array
    - 3D array
    - maybe make some simple common functions
- Common header file
- Make DESIGN.md
- Write the solver function
    - recursive solution, brute force
    - loop through each tile, try each number in it, move to next; if the current solution doesn't work, then backtrace by returning a 1; keep going until a solution is found
- Solver header file, too
- Write the creator function
    - create a fully solved puzzle
    - remove numbers one by one, checking each time if the puzzle has more than one solution still
        - this would probably be a function in common, since creator would use this and solver could use this too for EC? 
- TESTING.md and any other testing to be done
- IMPLEMENTATION.md writing
- - - - - - - - - Extra Credit
- Create UI
    - look into java/javascript
    - see how to package C module and export into java/javascript; can do this in python easily if absolutely necessary
    - Could create a website then! Would be very simple if we can get the C code there, jordan could do this part
- Other extra credit?
    - Websockets might be possible