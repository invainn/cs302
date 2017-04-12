CC=g++

all: main

main: PA05.cpp Bank.o
	g++ -std=c++11 PA05.cpp Bank.o -o main

Bank.o: Bank.cpp
	g++ -c -std=c++11 Bank.cpp

clean: rm -rf *.o main