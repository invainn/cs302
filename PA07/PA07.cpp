#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "JSONParser.h"

int main() {

	std::string fileName = "PlayerStatistics.json";

	JSONParser jParse(fileName);

	std::vector<std::vector<int> > playerYouStats(3);
	// One Suit
	playerYouStats[0].push_back(5);
	playerYouStats[0].push_back(5);
	playerYouStats[0].push_back(30);
	playerYouStats[0].push_back(18);
	playerYouStats[0].push_back(78);
	// Two Suits
	playerYouStats[1].push_back(3);
	playerYouStats[1].push_back(5);
	playerYouStats[1].push_back(45);
	playerYouStats[1].push_back(34);
	playerYouStats[1].push_back(98);
	// Four Suits
	playerYouStats[2].push_back(0);
	playerYouStats[2].push_back(5);
	playerYouStats[2].push_back(999);
	playerYouStats[2].push_back(999);
	playerYouStats[2].push_back(86);

	std::vector<std::vector<int> > playerMeStats(3);
	// One Suit
	playerMeStats[0].push_back(0);
	playerMeStats[0].push_back(5);
	playerMeStats[0].push_back(999);
	playerMeStats[0].push_back(999);
	playerMeStats[0].push_back(12);
	// Two Suits
	playerMeStats[1].push_back(2);
	playerMeStats[1].push_back(5);
	playerMeStats[1].push_back(65);
	playerMeStats[1].push_back(11);
	playerMeStats[1].push_back(78);
	// Four Suits
	playerMeStats[2].push_back(5);
	playerMeStats[2].push_back(5);
	playerMeStats[2].push_back(56);
	playerMeStats[2].push_back(67);
	playerMeStats[2].push_back(98);

	jParse.editPlayer("You", playerYouStats);
	jParse.editPlayer("Me", playerMeStats);
	jParse.writeToFile();
	
	return 0;
}