# Makefile for CS50 final project executable
#
# Authors: Alex Hamel, James Verschleiser, Jordan Sanz
#
# CS50, Summer 2020

PROG = play
OBJS = play.o solve.o create.o puzzle.o list.o
LIBS = ../solve/solve.a ../create/create.a ../common/common.a ../libcs50/libcs50.a

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

play.o: ../solve/solve.h ../create/create.h ../libcs50/memory.h ../common/puzzle.h ../libcs50/file.h ../common/list.h ../libcs50/memory.h
solve.o: ../solve/solve.h ../common/puzzle.h ../common/common.a
create.o: ../create/create.h ../libcs50/memory.h ../common/puzzle.h ../common/common.a
puzzle.o: ../puzzle/puzzle.h ../libcs50/file.h
list.o: ../common/list.h ../libcs50/memory.h


.PHONY: clean

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)