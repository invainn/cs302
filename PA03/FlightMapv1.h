#include <iostream>
#include <string>
#include <list>
#include <map>

class City {
    public:
        City(std::string);
        void setCityName(const std::string);
        void setCityVisited(const bool);
        std::string getCityName() const;
        bool getCityVisited() const;
        City& operator=(const City&);
        friend bool operator<(const City&, const City&);
        friend bool operator==(const City&, const City&);
        friend bool operator!=(const City&, const City&);
        friend std::ostream& operator<<(std::ostream&, const City&);
    private:
        std::string cityName;
        bool cityVisited;
};

class FlightMap {
    public:
        void readFlightMap(std::string, std::string);
        void markVisited(City&);
        void unvisitAll();
        City getNextCity(City);
        bool isPath(City, City);
        bool isVisited(const City) const;
        bool isServed(const City);
    private:
        std::map<City, std::list<City> > flightMap;
};