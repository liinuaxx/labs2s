.PHONY: clean all

all: test

test: HashTable.o
	g++ HashTable.cpp -L. -lHashTest -o test

HashTable.o: HashTable.cpp HashTable.h
	g++ -c HashTable.cpp -o HashTable.o

clean:
	rm -f HashTable.o test
