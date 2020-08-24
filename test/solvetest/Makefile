# Makefile for solve testing portion of final project sudoku
#
# Author: Alexandre Hamel, Jordan Sanz, James Verschleiser
# Date: 08/19/2020
# Class: CS50
# Professor: Xia Zhou

PROG = solvetest
OBJS = solvetest.o ../../solve/solve.o
LIBS = ../../common/common.a ../../libcs50/libcs50.a -lm

# uncomment the following to turn on push/pop queue messages, along with notices about unaccessible pages
#TESTING=-DQUEUETEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../../libcs50 -I../../common
VFLAGS = --leak-check=full --show-leak-kinds=all -s
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

solvetest.o: ../../common/common.a ../../libcs50/libcs50.a

.PHONY: test valgrind clean

test: $(PROG)
	./$(PROG)

valgrind: $(PROG)
	valgrind $(VFLAGS) ./$(PROG)

clean:
	rm -rf *.dSYM
	rm -f *~ *.o
	rm -f $(PROG)
	rm -f core
