# Makefile for common library
#
# Author: Alexandre Hamel
# Date: 08/18/2020
# Class: CS50
# Professor: Xia Zhou

# object files, and the target library
OBJS = puzzle.o
LIB = common.a

# add -DMEMTEST for memory tracking report in indexer
# (and run `make clean; make` whenever you change this)
FLAGS = # -DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc

# Build the library by archiving object files
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# Dependencies: object files depend on header files
puzzle.o: puzzle.h

.PHONY: clean

# clean up after our compilation
clean:
	rm -f core
	rm -f $(LIB) *~ *.o
