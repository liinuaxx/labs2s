.PHONY: clean all

all: Stack.o list.o vector.o
	g++ Stack.o list.o vector.o -o test -L. -lStackTest

Stack.o: Stack.cpp Stack.h list.h vector.h
	g++ -c Stack.cpp -o Stack.o

list.o: list.cpp list.h StackImplementation.h
	g++ -c list.cpp -o list.o

vector.o: vector.cpp vector.h StackImplementation.h
	g++ -c vector.cpp -o vector.o

clean:
	rm -f Stack.o list.o vector.o test
