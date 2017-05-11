#include <iostream>
#include <string>
#include <vector>

class JSONParser {
	public:
		JSONParser(std::string fileName);

		void writeToFile();
		void editNumber(std::string, int, std::size_t, int);
		std::size_t findOccurrence(std::string, int, std::size_t);
		void editPlayer(std::string, std::vector<std::vector<int> >);
		float calculateWinRate(int, int);
		int calculateFastestWinOverall(std::vector<std::vector<int> >);
		int calculateFewestMovesOverall(std::vector<std::vector<int> >);
		int calculateTopScoreOverall(std::vector<std::vector<int> >);
	private:
		std::string fileString;
};