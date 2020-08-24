# Makefile for CS50 Final Project Sudoku
#
# CS 50, Summer 2020

PROG = sudoku
OBJS = sudoku.o ./solve/solve.o ./create/create.o ./common/puzzle.o ./common/list.o ./libcs50/file.o
LIBS = ./libcs50/libcs50.a ./common/common.a -lm
TEST = ./examplepuzzles/puzzle1.txt

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I./libcs50 -I./common
VFLAGS = --leak-check=full --show-leak-kinds=all -s
CC = gcc
MAKE = make


.PHONY: all valgrind clean

############## default: make all libs and programs ##########
all:
	make -C libcs50
	make -C common
	make -C test
	make -C create
	make -C solve
	make -C python
	make sudoku

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

sudoku.o: ./libcs50/file.h ./libcs50/memory.h ./common/puzzle.h ./common/list.h  ./solve/solve.h ./create/create.h

############## valgrind all programs ##########
valgrind: all
	make -C test valgrind
	valgrind $(VFLAGS) ./sudoku create
	valgrind $(VFLAGS) ./sudoku solve < $(TEST)
	
############## clean  ##########
clean:
	rm -f *~
	rm -fr data
	rm -f *.o
	rm -f sudoku
	make -C libcs50 clean
	make -C common clean
	make -C test clean
	make -C create clean
	make -C solve clean
	make -C python clean
