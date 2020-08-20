# Makefile for CS50 Final Project Sudoku
#
# CS 50, Summer 2020

.PHONY: all valgrind clean

############## default: make all libs and programs ##########
all: 
	make -C libcs50
	make -C common
	make -C test
	make -C create

############## valgrind all programs ##########
valgrind: all
	make -C test valgrind

############## clean  ##########
clean:
	rm -f *~
	rm -fr data
	make -C libcs50 clean
	make -C common clean
	make -C test clean
	make -C create clean
