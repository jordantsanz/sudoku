# Makefile for solve library
#
# Author: Alex Hamel, James Verschleiser, Jordan Sanz
# Date: 08/19/2020
# Class: CS50
# Professor: Xia Zhou

# object files, and the target library
OBJS = solve.o
LIB = solve.a

# add -DMEMTEST for memory tracking report in indexer
# (and run `make clean; make` whenever you change this)
FLAGS = # -DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc

# Build the library by archiving object files
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# Dependencies: object files depend on header files
solve.o: solve.h

.PHONY: clean

# clean up after our compilation
clean:
	rm -f core
	rm -f $(LIB) *~ *.o
