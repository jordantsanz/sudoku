# Makefile for create program
#
# Author: Alexandre Hamel, James Verschleiser, Jordan Sanz
# Date: 08/18/2020
# Class: CS50
# Professor: Xia Zhou

PROG = create
OBJS = create.o
LIBS = ../libcs50/libcs50.a ../common/common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50 -I../common
CC = gcc
MAKE = MAKE

$(PROG): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@



create.o: ../libcs50/memory.h


.PHONY: test valgrind clean

# test: testing.sh
# 	bash -v testing.sh &> testing.out

valgrind: $(PROG)
	valgrind ./$(PROG)

clean:
	rm -rf *.dSYM 
	rm -f *~ *.o
	rm -f $(PROG)
