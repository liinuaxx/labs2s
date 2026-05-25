.PHONY: clean all

all: test

test: RBT.o
	g++ RBT.o -o test -L. -lRBTreeTest

BST.o: BST.cpp BST.h
	g++ -c RBT.cpp -o RBT.o

clean:
	rm -f RBT.o test
