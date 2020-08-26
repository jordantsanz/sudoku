# Makefile for entire sudoku project library for use in python
#   Builds and compiles all these utility functions into a library.
#
# CS50, Summer 2020

# object files, and the target library
OBJS = ../solve/solve.c ../create/create.c ../common/list.c ../common/puzzle.c ../libcs50/file.c ../libcs50/memory.c ./helloworld.c
LIB = sudokumodule.so

CFLAGS = -fPIC -shared
CC = cc

# Build the library by archiving object files
$(LIB): $(OBJS)
	$(CC) $(CFLAGS) -o $(LIB) $(OBJS)

.PHONY: clean

# clean up after our compilation
clean:
	rm -f core
	rm -f $(LIB) *~ *.o
	rm -f *.so
