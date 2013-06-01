OBJECTS=huffman.o main.o

huffman: $(OBJECTS)
	$(CXX) -o huffman $(OBJECTS)
huffman.o: huffman.cpp huffman.h
	$(CXX) -c huffman.cpp
main.o: main.cpp main.h
	$(CXX) -c main.cpp

clean:
	rm huffman huffman.o main.o