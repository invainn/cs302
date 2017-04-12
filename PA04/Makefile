CC=g++

all: main

main: PA04.cpp SortAlg.o
	g++ -std=c++11 PA04.cpp SortAlg.o -o main

SortAlg.o: SortAlg.cpp
	g++ -c -std=c++11 SortAlg.cpp

clean: rm -rf *.o main