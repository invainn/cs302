CC=g++

all: main

main: PA03.cpp FlightMapv1.o
	g++ PA03.cpp FlightMapv1.o -o main

FlightMapv1.o: FlightMapv1.cpp
	g++ -c FlightMapv1.cpp

clean: rm -rf *.o main