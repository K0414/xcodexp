CC=g++
CFLAGS=-Wall
TARGET=foo
SRC=foo.cpp

.PHONY: all clean

all:$(TARGET)

$(TARGET):$(SRC)
	$(CC) -o $(TARGET) $(CFLAGS) $(SRC) -lm

clean:
	-rm -rf *.o foo
