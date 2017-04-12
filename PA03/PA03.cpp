#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "FlightMapv1.h" // change depending on which solution to test

void readRequestFlights(std::string, std::vector<City>&, std::vector<City>&);
void findConnectingFlights(std::vector<City>, std::vector<City>, FlightMap);

int main() {
	FlightMap test;
	std::string cityFileName = "cityFile.txt";
	std::string flightFileName = "flightFile.txt";
	std::string requestFileName = "requestFile.txt";
	std::vector<City> originCity;
	std::vector<City> destCity;

	test.readFlightMap(cityFileName, flightFileName);
	readRequestFlights(requestFileName, originCity, destCity);
	findConnectingFlights(originCity, destCity, test);

	return 0;
}

void readRequestFlights(std::string requestFileName, std::vector<City>& originCity, std::vector<City>& destCity) {
	std::ifstream currentFile;
	std::string tempOriginCityInp;
	std::string tempDestCityInp;
	char charInp;

	currentFile.open(requestFileName.c_str());
	while(!currentFile.eof()) {
		std::getline(currentFile, tempOriginCityInp, ',');
		currentFile.get(); // moves file pointer to next char
		std::getline(currentFile, tempDestCityInp);

		originCity.push_back(City(tempOriginCityInp));
		destCity.push_back(City(tempDestCityInp));
	}
	currentFile.close();
}

void findConnectingFlights(std::vector<City> originCity, std::vector<City> destCity, FlightMap flightMap) {
	int counter = 0;

	for(counter = 0; counter < originCity.size(); counter++) {
		std::cout << "Request is to fly from " << originCity[counter].getCityName() << " to " << destCity[counter].getCityName() << "." << std::endl;
		if(!flightMap.isServed(originCity[counter])) {
			std::cout << "Sorry, HPAir does not serve " << originCity[counter].getCityName() << "." << std::endl;
			std::cout << std::endl;
		} else if(!flightMap.isServed(destCity[counter])) {
			std::cout << "Sorry, HPAir does not serve " << destCity[counter].getCityName() << "." << std::endl;
			std::cout << std::endl;
		} else if(flightMap.isPath(originCity[counter], destCity[counter])) {
			std::cout << "HPAir flies from " << originCity[counter].getCityName() << " to " << destCity[counter].getCityName() << "." << std::endl;
			std::cout << std::endl;
		} else {
			std::cout << "Sorry, HPAir does not fly from " << originCity[counter].getCityName() << " to " << destCity[counter].getCityName() << "." << std::endl;
			std::cout << std::endl;
		}
	}
}