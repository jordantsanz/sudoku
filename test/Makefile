# Makefile for Testing subdirectory CS50 Final Project Sudoku
#
# CS 50, Summer 2020

PROG = fuzz
OBJS = fuzz.o ../solve/solve.o ../create/create.o ../common/puzzle.o
LIBS = ../libcs50/libcs50.a ../common/common.a -lm

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I./libcs50 -I./common
VFLAGS = --leak-check=full --show-leak-kinds=all -s
CC = gcc
MAKE = make
NUMTESTS = 100

.PHONY: all valgrind clean

############## default: make all libs and programs ##########
all: 
	make -C puzzletest
	make -C solvetest
	make -C createtest
	make fuzz

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

fuzz.o: ../solve/solve.h ../create/create.h ../common/puzzle.h

############## valgrind all programs ##########
valgrind: all
	make -C puzzletest valgrind
	make -C solvetest valgrind
	make -C createtest valgrind
	valgrind $(VFLAGS) ./fuzz $(NUMTESTS)

############## clean  ##########
clean:
	rm -f *~
	rm -fr data
	rm -f *.o
	rm -f fuzz
	make -C puzzletest clean
	make -C solvetest clean
	make -C createtest clean
