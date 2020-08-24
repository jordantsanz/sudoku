# Makefile for solve testing portion of final project sudoku
#
# Author: Alex Hamel, James Verschleiser, Jordan Sanz
# Date: 08/19/2020
# Class: CS50
# Professor: Xia Zhou

PROG = createtest
OBJS = createtest.o ../../create/create.o ../../solve/solve.o
LIBS = ../../common/common.a ../../libcs50/libcs50.a -lm

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I../../libcs50 -I../../common
VFLAGS = --leak-check=full --show-leak-kinds=all -s
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

createtest.o: ../../solve/solve.h ../../common/common.a ../../libcs50/libcs50.a

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
