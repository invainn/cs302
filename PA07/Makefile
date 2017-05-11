CC=g++

all: main

main: PA07.cpp JSONParser.o
	g++ -std=c++11 PA07.cpp JSONParser.o -o main

JSONParser.o: JSONParser.cpp
	g++ -c -std=c++11 JSONParser.cpp

clean: rm -rf *.o main