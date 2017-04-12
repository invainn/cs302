#include <iostream>
#include <list>
#include <map>
#include <string>
#include <stack>
#include <fstream>
#include "FlightMapv1.h"

/** Constructs a city object.
    @param cityName  A std::string that is to be set to this->cityName
**/
City::City(std::string cityName) {
	this->cityName = cityName;
	this->cityVisited = false;
}
/** Sets an object's city name
    @param cityName  A const std::string that is to be set to this->cityName
**/
void City::setCityName(const std::string cityName) {
	this->cityName = cityName;
}
/** Sets an object's cityVisited boolean
    @param truthVal  A const bool that is to be set to this->cityVisited
**/
void City::setCityVisited(const bool truthVal) {
	this->cityVisited = truthVal;
}
/** Gets a city's name
    @return  The std::string of the city's name.
**/
std::string City::getCityName() const {
	return this->cityName;
}
/** Returns if a city is visited
    @return  True if city was visited, or false if not
**/
bool City::getCityVisited() const {
	return this->cityVisited;
}
/** Overloaded assignment operator for class City
    @param inp  A referenced const City object to be copied values from to *this
**/
City& City::operator=(const City& inp) {
	this->setCityVisited(inp.getCityVisited());
	this->setCityName(inp.getCityName());
}
/** Overloaded equality operator for class City
    @param inp1  A referenced const City to be compared to inp2
    @param inp2  A referenced const City to be compared to inp1
    @return True if both city names are equal, false if not.
**/
bool operator==(const City& inp1, const City& inp2) {
	if(inp1.getCityName() == inp2.getCityName()) {
		return true;
	} else {
		return false;
	}
}
/** Overloaded inequality operator for class City
    @param inp1  A referenced const City to be compared to inp2
    @param inp2  A referenced const City to be compared to inp1
    @return True if both city names are not equal, false if they are.
**/
bool operator!=(const City& inp1, const City& inp2) {
	if(!(inp1 == inp2)) {
		return true;
	} else {
		return false;
	}
}
/** Overloaded < operator used for strict weak ordering
    @param inp1  A referenced const City to be compared to inp2
    @param inp2  A referenced const City to be compared to inp1
    @return True if inp1 is less than inp2, false if not.
**/
bool operator<(const City& inp, const City& inp2) {
	return inp.getCityName() < inp2.getCityName();
}
/** Overloaded output stream operator
    @param os  A referenced std::ostream used to output inp 
    @param inp  A referenced const City object to be output
    @return  The output stream.
**/
std::ostream& operator<<(std::ostream& os, const City& inp) {
	std::cout << inp.getCityName();
	return os;
}
/** Reads the cities into the map and the flights into each list.
	Flights are read by using the key value to find the mapped list and then inserting it using push_back
    @param cityFileName  A std::string used to represent the file name for the cities
    @param flightFileName  A std::string used to represent the file name for the flights
    @post Each key value city in the map will have their corresponding adjacent cities in the mapped value list
**/
void FlightMap::readFlightMap(std::string cityFileName, std::string flightFileName) {
	std::ifstream currentFile;
	std::string tempCityInp;
	std::string tempAdjCityInp;
	char charInp;

	currentFile.open(cityFileName.c_str());
	while(!currentFile.eof()) {
		std::getline(currentFile, tempCityInp);
		this->flightMap[City(tempCityInp)] = std::list<City>();
	}
	currentFile.close();
	currentFile.open(flightFileName.c_str());
	while(!currentFile.eof()) {
		std::getline(currentFile, tempCityInp, ',');
		currentFile.ignore(256, ' ');
		std::getline(currentFile, tempAdjCityInp, '\t');
		currentFile.ignore(256, '\n');
		this->flightMap[City(tempCityInp)].push_back(tempAdjCityInp);
	}
}
/** Marks a city as visited in the entire map and all of its lists.
    @param originCity  A referenced City that represents the City to be set to visited 
    @post All instances of the originCity in the map and its lists are set to visited
**/
void FlightMap::markVisited(City& originCity) {
	std::map<City, std::list<City> >::iterator mapIt;
	std::list<City>::iterator listIt;

	for(mapIt = this->flightMap.begin(); mapIt != this->flightMap.end(); ++mapIt) {
		for(listIt = mapIt->second.begin(); listIt != mapIt->second.end(); ++listIt) {
			if(originCity == *listIt) {
				listIt->setCityVisited(true);
			}
		}
	}
}
/** Sets cityVisited to false in all cities in the map and its lists
    @post All cities in the map and its lists will be unvisited.
**/
void FlightMap::unvisitAll() {
	std::map<City, std::list<City> >::iterator mapIt;
	std::list<City>::iterator listIt;

	for(mapIt = this->flightMap.begin(); mapIt != this->flightMap.end(); ++mapIt) {
		for(listIt = mapIt->second.begin(); listIt != mapIt->second.end(); ++listIt) {
			listIt->setCityVisited(false);
		}
	}
}
/** Gets the next adjacent city that is unvisited in the originCity's adjacency list
    @param aCity  A City object that represents the origin city and used to grab its list.
    @return If an adjacent unvisited city is found, it returns true, if not, return NO_CITY indicating that no city suitable was found.
**/
City FlightMap::getNextCity(City aCity) {
	std::list<City>::iterator listIt;
	for(listIt = this->flightMap[aCity].begin(); listIt != this->flightMap[aCity].end(); ++listIt) {
		if(listIt->getCityVisited() == false) {
			return *listIt;
		}
	}
	City NO_CITY("NO_CITY");
	return NO_CITY;

}
/** Finds a connecting flight between two cities.
    @pre Assumes map is populated with values.
    @param originCity  A City object used as a key value to find its adjacency list in the map
    @param destCity  A City object that is used to compare to other cities to see if originCity connects to it
    @return If there is a connecting graph of originCity and destcity, then return true, if not, return false.
**/
bool FlightMap::isPath(City originCity, City destCity) {
	std::stack<City> cityStack;
	std::stack<City> cityStackCopy;
	City NO_CITY("NO_CITY"); // if we cannot find an unvisited city
	this->unvisitAll();
	int counter = 0;
	std::ofstream logFile("logv1.txt", std::ios_base::app);

	cityStack.push(originCity);
	this->markVisited(originCity);

	City topCity = cityStack.top();
	while(!cityStack.empty() && (topCity != destCity)) {
		City nextCity = getNextCity(topCity);
		if(nextCity == originCity) {
			return false;
		}
		if(nextCity == NO_CITY) {
			cityStack.pop();
			logFile << "\nCannot find unvisited city, popping cityStack...\n";
			logFile << "Current cityStack after popping (top of the stack is left most)\n";
			logFile << "\n----------------------------------------\n";
			for(counter = 0; counter < cityStack.size(); counter++) {
				cityStackCopy.push(cityStack.top());
				cityStack.pop();
				logFile << cityStackCopy.top().getCityName() << " ";
			}
			for(counter = 0; counter < cityStackCopy.size(); counter++) {
				cityStack.push(cityStackCopy.top());
				cityStackCopy.pop();
			}
			logFile << "\n----------------------------------------\n";
		} else {
			cityStack.push(nextCity);
			this->markVisited(nextCity);
			logFile << "\nFound unvisited city, pushing onto stack\n";
			logFile << "Current cityStack after pushing (top of the stack is left most)\n";
			logFile << "\n----------------------------------------\n";
			for(counter = 0; counter < cityStack.size(); counter++) {
				cityStackCopy.push(cityStack.top());
				cityStack.pop();
				logFile << cityStackCopy.top().getCityName() << " ";
			}
			for(counter = 0; counter < cityStackCopy.size(); counter++) {
				cityStack.push(cityStackCopy.top());
				cityStackCopy.pop();
			}
			logFile << "\n----------------------------------------\n";
		}

		if(!cityStack.empty()) {
			topCity = cityStack.top();
		}
	}
	if(!cityStack.empty()) {
		logFile << "\n\nFound Path!\n\n";
		logFile << "++++++++++++++++++++++++++++++++++++++++\n";
	} else {
		logFile << "\n\nDid not find path\n\n";
		logFile << "++++++++++++++++++++++++++++++++++++++++\n";
	}
	return !cityStack.empty();
}
/** Checks if a city is visited
    @param aCity  A const City object that is checked to see if it is visited or not
    @return True if aCity is visited, false if not.
**/
bool FlightMap::isVisited(const City aCity) const {
	return aCity.getCityVisited();
}
/** Checks if to see if HPAir serves a particular city
    @param aCity  A const City object that is checked to see if it is served or not
    @return True if city is served, false if not.
**/
bool FlightMap::isServed(const City originCity) {
	std::map<City, std::list<City> >::iterator mapIt;

	for(mapIt = this->flightMap.begin(); mapIt != this->flightMap.end(); ++mapIt) {
		if(mapIt->first == originCity) {
			if(mapIt->second.empty()) {
				return false;
			}
		}
	}
	return true;
}