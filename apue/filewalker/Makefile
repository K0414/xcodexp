# Common make definitions, customized for each platform

# Definitions required in all program directories to compile and link
# C programs using gcc.

CC=gcc
LDLIBS=../lib/libapue.a
CFLAGS=-DLINUX -ansi -I../include -Wall -D_GNU_SOURCE

PROGS =	filewalker

all:	${PROGS}

filewalker: main.o
	$(CC) -o filewalker main.c $(LDLIBS) $(CFLAGS)

clean:
	-rm -f ${PROGS} *.o *~
