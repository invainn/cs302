#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include <vector>
#include "JSONParser.h"

JSONParser::JSONParser(std::string fileName) {
	std::ifstream inputFile(fileName);
	std::string bufferString((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>()); // read entire stream into string container
	this->fileString = bufferString;
}

void JSONParser::writeToFile() {
	std::ofstream out("PlayerStatistics.json", std::ofstream::trunc);
	out << this->fileString;
	out.close();
}

void JSONParser::editNumber(std::string typeName, int numToReplace, std::size_t startPos, int commaOn) {
	std::size_t found;
	std::string sNumber;

	found = this->fileString.find(typeName, startPos) + typeName.length() + 3;

	if(commaOn) {
		sNumber = std::to_string(numToReplace) + ",";
	} else {
		sNumber = std::to_string(numToReplace);
	}
	this->fileString.replace(found, sNumber.length(), sNumber);
}

std::size_t JSONParser::findOccurrence(std::string input, int nthOcc, std::size_t startPos) {
	int counter = 0;
	std::size_t nthOccPos = startPos;

	for(counter = 0; counter < nthOcc; counter++) {
		nthOccPos = this->fileString.find(input, nthOccPos+1);
	}

	return nthOccPos--;
}

void JSONParser::editPlayer(std::string playerName, std::vector<std::vector<int> > playerStats) {
	std::string gamesWon = "Games Won";
	std::string winRate = "Win Rate";
	std::string gamesPlayed = "Games Played";
	std::string fastestWin = "Fastest Win";
	std::string fewestMoves = "Fewest Moves";
	std::string topScore = "Top Score";

	std::size_t playerNamePos = this->findOccurrence(playerName, 1, 0);
	std::size_t gwPos = this->findOccurrence(gamesWon, 2, playerNamePos);
	std::size_t wrPos = this->findOccurrence(winRate, 2, playerNamePos);
	std::size_t gpPos = this->findOccurrence(gamesPlayed, 2, playerNamePos);
	std::size_t fwPos = this->findOccurrence(fastestWin, 2, playerNamePos);
	std::size_t fmPos = this->findOccurrence(fewestMoves, 2, playerNamePos);
	std::size_t tsPos = this->findOccurrence(topScore, 2, playerNamePos);


	int counter = 2;
	for(counter = 2; counter < 5; counter++) {
		editNumber(gamesWon, playerStats[counter-2][0], gwPos, 1);
		editNumber(winRate, this->calculateWinRate(playerStats[counter-2][1], playerStats[counter-2][0]), wrPos, 1);
		editNumber(gamesPlayed, playerStats[counter-2][1], gpPos, 1);
		editNumber(fastestWin, playerStats[counter-2][2], fwPos, 1);
		editNumber(fewestMoves, playerStats[counter-2][3], fmPos, 1);
		editNumber(topScore, playerStats[counter-2][4], tsPos, 0);

		gwPos = this->findOccurrence(gamesWon, counter+1, playerNamePos);
		wrPos = this->findOccurrence(winRate, counter+1, playerNamePos);
		gpPos = this->findOccurrence(gamesPlayed, counter+1, playerNamePos);
		fwPos = this->findOccurrence(fastestWin, counter+1, playerNamePos);
		fmPos = this->findOccurrence(fewestMoves, counter+1, playerNamePos);
		tsPos = this->findOccurrence(topScore, counter+1, playerNamePos);
	}

	int totalGamesWon = playerStats[0][0]+playerStats[1][0]+playerStats[2][0];
	int totalGamesPlayed = playerStats[0][1]+playerStats[1][1]+playerStats[2][1];

	editNumber(gamesWon, totalGamesWon, playerNamePos, 1);
	editNumber(winRate, (int)calculateWinRate(totalGamesPlayed, totalGamesWon), playerNamePos, 1);
	editNumber(gamesPlayed, totalGamesPlayed, playerNamePos, 1);
	editNumber(fastestWin, calculateFastestWinOverall(playerStats), playerNamePos, 1);
	editNumber(fewestMoves, calculateFewestMovesOverall(playerStats), playerNamePos, 1);
	editNumber(topScore, calculateTopScoreOverall(playerStats), playerNamePos, 0);
}

float JSONParser::calculateWinRate(int gamesPlayed, int gamesWon) {
	return ((float)gamesWon/(float)gamesPlayed)*100;
}

int JSONParser::calculateFastestWinOverall(std::vector<std::vector<int> > playerStats) {
	int fastestWinOverall = 9999;
	int counter = 0;

	for(counter = 0; counter < 3; counter++) {
		if(playerStats[counter][2] < fastestWinOverall) {
			fastestWinOverall = playerStats[counter][2];
		}
	}

	return fastestWinOverall;
}

int JSONParser::calculateFewestMovesOverall(std::vector<std::vector<int> > playerStats) {
	int fewestMovesOverall = 9999;
	int counter = 0;

	for(counter = 0; counter < 3; counter++) {
		if(playerStats[counter][3] < fewestMovesOverall) {
			fewestMovesOverall = playerStats[counter][3];
		}
	}

	return fewestMovesOverall;
}

int JSONParser::calculateTopScoreOverall(std::vector<std::vector<int> > playerStats) {
	int topScoreOverall = 0;
	int counter = 0;

	for(counter = 0; counter < 3; counter++) {
		if(playerStats[counter][4] > topScoreOverall) {
			topScoreOverall = playerStats[counter][4];
		}
	}

	return topScoreOverall;
}