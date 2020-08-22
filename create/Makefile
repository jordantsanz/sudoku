# Makefile for solve library
#
# Author: James Verschleiser
# Date: 08/19/2020
# Class: CS50
# Professor: Xia Zhou

# object files, and the target library
OBJS = create.o
LIB = create.a ../common/common.a ../solve/solve.a

# add -DMEMTEST for memory tracking report in indexer
# (and run `make clean; make` whenever you change this)
FLAGS = # -DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I../libcs50 -I../common -I../solve
CC = gcc

# Build the library by archiving object files
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# Dependencies: object files depend on header files
create.o: create.h ../libcs50/memory.h

.PHONY: clean

# clean up after our compilation
clean:
	rm -f core
	rm -f create.a *~ *.o
