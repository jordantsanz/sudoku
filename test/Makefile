# Makefile for Testing subdirectory CS50 Final Project Sudoku
#
# CS 50, Summer 2020

.PHONY: all valgrind clean

############## default: make all libs and programs ##########
all: 
	make -C puzzletest
	make -C solvetest
	make -C createtest

############## valgrind all programs ##########
valgrind: all
	make -C puzzletest valgrind
	make -C solvetest valgrind
	make -C createtest valgrind

############## clean  ##########
clean:
	rm -f *~
	rm -fr data
	make -C puzzletest clean
	make -C solvetest clean
	make -C createtest clean
