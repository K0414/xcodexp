CC = gcc
CXX = g++
LINK = $(CXX)

COBJS = caller.o
CXXOBJS = func.o adder.o

all: abin

.PHONY: all clean

abin: $(COBJS) $(CXXOBJS)
	$(LINK) -o abin $(COBJS) $(CXXOBJS)

caller.o: caller.c func.h
	$(CC) -c caller.c

func.o: func.cpp func.h adder.h
	$(CXX) -c func.cpp

adder.o: adder.cpp adder.h
	$(CXX) -c adder.cpp

clean:
	-rm *.o abin
