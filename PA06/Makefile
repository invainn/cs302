CC=g++

all: main

main: PA06.cpp BST.o
	g++ -std=c++11 PA06.cpp BST.o -o main

BST.o: BST.cpp
	g++ -c -std=c++11 BST.cpp

clean: rm -rf *.o main