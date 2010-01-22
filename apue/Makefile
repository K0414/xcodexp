# Common make definitions, customized for each platform

# Definitions required in all program directories to compile and link
# C programs using gcc.

WKDIR=/home/liufc/books/APUE/code
CC=gcc
LDLIBS=lib/libapue.a
CFLAGS=-DLINUX -ansi -Iinclude -Wall -D_GNU_SOURCE

PROGS =	test

all:	${PROGS}

test: test.o
	$(CC) -o test test.c $(LDLIBS) $(CFLAGS)

clean:
	-rm -f ${PROGS} *.o
