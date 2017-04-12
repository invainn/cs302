#include <iostream>
#include <string>
#include <stack>
#include <list>
#include <vector>
#include <map>

class City {
    public:
        City(std::string);
        void setCityName(const std::string);
        std::string getCityName() const;
        City& operator=(const City&);
        friend bool operator<(const City&, const City&);
        friend bool operator==(const City&, const City&);
        friend bool operator!=(const City&, const City&);
        friend std::ostream& operator<<(std::ostream&, const City&);
    private:
        std::string cityName;
};

class FlightMap {
    public:
        void readFlightMap(std::string, std::string);
        void markVisited(City&);
        void unvisitAll();
        City getNextCity(City, std::stack<std::list<City>::iterator>&);
        bool isPath(City, City);
        bool isServed(const City);
    private:
        std::map<City, std::list<City> > flightMap;
        std::vector<City> visitedCities;
};