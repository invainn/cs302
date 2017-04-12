#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <random>
#include <iomanip>
#include "Bank.h"

// constructor
BankEvent::BankEvent() {
	this->time = 0;
	this->transactionTime = 0;
	this->lineNumber = 0;
	this->isArrivalEvent = false;
}

// parameterized constructor
BankEvent::BankEvent(int aTime, int tTime, int lineNum, bool isArrival) {
	this->time = aTime;
	this->transactionTime = tTime;
	this->lineNumber = lineNum;
	this->isArrivalEvent = isArrival;
}

// copy constructor
BankEvent::BankEvent(const BankEvent& src) {
	this->time = src.getTime();
	this->transactionTime = src.getTransactionTime();
	this->lineNumber = src.getLineNumber();
	this->isArrivalEvent = src.getIsArrivalEvent();
}

// overloaded equality operator
BankEvent& BankEvent::operator=(const BankEvent& src) {
	this->time = src.getTime();
	this->transactionTime = src.getTransactionTime();
	this->isArrivalEvent = src.getIsArrivalEvent();

	return *this;
}

// overloaded less than operator
bool operator<(const BankEvent& inp1, const BankEvent& inp2) {
	return inp1.getTime() < inp2.getTime();
}

// sets private member variables 
void BankEvent::setEvent(int aTime, int tTime, bool isArrival) {
	this->time = aTime;
	this->transactionTime = tTime;
	this->isArrivalEvent = isArrival;
}

int BankEvent::getTime() const {
	return this->time;
}

int BankEvent::getTransactionTime() const {
	return this->transactionTime;
}

int BankEvent::getLineNumber() const {
	return this->lineNumber;
}

bool BankEvent::getIsArrivalEvent() const {
	return this->isArrivalEvent;
}

// constructor
BankSimulation::BankSimulation() {
	this->tellerOneAvailable = false;
	this->tellerTwoAvailable = false;
	this->tellerThreeAvailable = false;
	this->currentTime = 0;
	this->totalProcessed = 0; // total people processed
	this->maxWaitTime = 0;
	this->maxLengthOfLine = 0;
	this->totalWaitTime = 0.0;
	this->avgLengthOfLine = 0.0;

	this->outputFile.open("output", std::ofstream::out | std::ios_base::trunc);
}

// using mersenne_twister_engine for generating values and outputting to file
void BankSimulation::generateData(int num) {
	std::string inpName = "input";
	inpName += std::to_string(num);
	std::ofstream inputFile(inpName, std::ios_base::trunc);
	int counter = 0;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis1(1, 540);
	std::uniform_int_distribution<> dis2(1, 20);

	for(counter = 0; counter < 99; counter++) {
		inputFile << dis1(gen) << "\t" << dis2(gen) << std::endl; // (e.g. "302\t5\n")
	}
	inputFile << dis1(gen) << "\t" << dis2(gen);
}

// simulation for one teller, one line
void BankSimulation::simulateOneTeller(int num) {
	// set up queues for one line
	BankQueue bankLine;
	BankPriorityQueue eventPriorityQueue;

	this->tellerOneAvailable = true; // enable tellerOne

	std::string tempTime;
	std::string tempTrans;
	std::ifstream currentFile;

	std::string inpName = "input";
	inpName += std::to_string(num);
	currentFile.open(inpName);
	// read in files
	while(!currentFile.eof()) {
		std::getline(currentFile, tempTime, '\t');
		std::getline(currentFile, tempTrans, '\n');
		BankEvent newArrivalEvent(std::stoi(tempTime), std::stoi(tempTrans), 0, true);
		eventPriorityQueue.enqueue(newArrivalEvent);
	}

	outputFile << " One Teller Simulation Begins" << std::endl;

	// event loop
	while(!eventPriorityQueue.isEmpty()) {
		BankEvent newEvent = eventPriorityQueue.peekFront();

		this->currentTime = newEvent.getTime();

		if(newEvent.getIsArrivalEvent()) {
			this->processArrival(newEvent, eventPriorityQueue, bankLine, 0);
		} else {
			this->processDeparture(newEvent, eventPriorityQueue, bankLine);
		}
	}

	totalWaitTime /= totalProcessed;
	avgLengthOfLine /= (totalProcessed*2); // factoring arrival and departure updates

	outputFile << "Simulation Ends" << std::endl;
	outputFile << std::endl;
	outputFile << "Final Statistics:" << std::endl;
	outputFile << "    Total number of people processed: " << this->totalProcessed << std::endl;
	outputFile << "    Average amount of time spent waiting: " << this->totalWaitTime << std::endl;
	outputFile << "    Maximum length of line: " << this->maxLengthOfLine << std::endl;
	outputFile << "    Maximum waiting time of a customer: " << this->maxWaitTime << std::endl;
	outputFile << "    Average length of line: " << this->avgLengthOfLine << std::endl;

	this->oneTellerResults.push_back(this->totalProcessed);
	this->oneTellerResults.push_back(this->totalWaitTime);
	this->oneTellerResults.push_back(this->maxLengthOfLine);
	this->oneTellerResults.push_back(this->maxWaitTime);
	this->oneTellerResults.push_back(this->avgLengthOfLine);
	outputFile << std::endl;
	this->reset();
}

void BankSimulation::simulateThreeTellers(int num) {
	BankQueue bankLineOne;
	BankQueue bankLineTwo;
	BankQueue bankLineThree;
	BankPriorityQueue eventPriorityQueue;

	this->tellerOneAvailable = true; // enable all three tellers
	this->tellerTwoAvailable = true;
	this->tellerThreeAvailable = true;

	std::string tempTime;
	std::string tempTrans;
	std::ifstream currentFile;

	std::string inpName = "input";
	inpName += std::to_string(num);
	currentFile.open(inpName);
	// read in files
	while(!currentFile.eof()) {
		std::getline(currentFile, tempTime, '\t');
		std::getline(currentFile, tempTrans, '\n');
		BankEvent newArrivalEvent(std::stoi(tempTime), std::stoi(tempTrans), 0, true);
		eventPriorityQueue.enqueue(newArrivalEvent);
	}

	outputFile << "Three Teller Simulation Begins" << std::endl;

	while(!eventPriorityQueue.isEmpty()) {
		BankEvent newEvent = eventPriorityQueue.peekFront();

		this->currentTime = newEvent.getTime();

		if(newEvent.getIsArrivalEvent()) { 
			this->chooseArrivalLine(bankLineOne, bankLineTwo, bankLineThree, eventPriorityQueue, newEvent);
		} else {
			this->chooseDepartureLine(bankLineOne, bankLineTwo, bankLineThree, eventPriorityQueue, newEvent);
		}
	}

	this->totalWaitTime /= this->totalProcessed;
	this->avgLengthOfLine /= (this->totalProcessed*2); // factoring arrival and departure updates

	outputFile << "Simulation Ends" << std::endl;
	outputFile << std::endl;
	outputFile << "Final Statistics:" << std::endl;
	outputFile << "    Total number of people processed: " << this->totalProcessed << std::endl;
	outputFile << "    Average amount of time spent waiting: " << this->totalWaitTime << std::endl;
	outputFile << "    Maximum length of a line: " << this->maxLengthOfLine << std::endl;
	outputFile << "    Maximum waiting time of a customer: " << this->maxWaitTime << std::endl;
	outputFile << "    Average length of a line: " << this->avgLengthOfLine << std::endl;

	this->threeTellerResults.push_back(this->totalProcessed);
	this->threeTellerResults.push_back(this->totalWaitTime);
	this->threeTellerResults.push_back(this->maxLengthOfLine);
	this->threeTellerResults.push_back(this->maxWaitTime);
	this->threeTellerResults.push_back(this->avgLengthOfLine);
	outputFile << std::endl;
	this->reset();
}

void BankSimulation::simulateOneLine(int num) {
	BankQueue bankLine;
	BankPriorityQueue eventPriorityQueue;

	std::string tempTime;
	std::string tempTrans;
	std::ifstream currentFile;

	this->tellerOneAvailable = true; // enable three tellers
	this->tellerTwoAvailable = true;
	this->tellerThreeAvailable = true;

	std::string inpName = "input";
	inpName += std::to_string(num);
	currentFile.open(inpName);
	// read in files
	while(!currentFile.eof()) {
		std::getline(currentFile, tempTime, '\t');
		std::getline(currentFile, tempTrans, '\n');
		BankEvent newArrivalEvent(std::stoi(tempTime), std::stoi(tempTrans), 0, true);
		eventPriorityQueue.enqueue(newArrivalEvent);
	}

	outputFile << "Simulation Begins" << std::endl;

	while(!eventPriorityQueue.isEmpty()) {
		BankEvent newEvent = eventPriorityQueue.peekFront();

		this->currentTime = newEvent.getTime();

		if(newEvent.getIsArrivalEvent()) {
			this->chooseTellerArrival(newEvent, eventPriorityQueue, bankLine);
		} else {
			this->processDeparture(newEvent, eventPriorityQueue, bankLine);
		}
	}

	totalWaitTime /= totalProcessed;
	avgLengthOfLine /= (totalProcessed*2); // factoring arrival and departure updates

	outputFile << "Simulation Ends" << std::endl;
	outputFile << std::endl;
	outputFile << "Final Statistics:" << std::endl;
	outputFile << "    Total number of people processed: " << this->totalProcessed << std::endl;
	outputFile << "    Average amount of time spent waiting: " << this->totalWaitTime << std::endl;
	outputFile << "    Maximum length of line: " << this->maxLengthOfLine << std::endl;
	outputFile << "    Maximum waiting time of a customer: " << this->maxWaitTime << std::endl;
	outputFile << "    Average length of line: " << this->avgLengthOfLine << std::endl;
	outputFile << std::endl;

	this->oneLineResults.push_back(this->totalProcessed);
	this->oneLineResults.push_back(this->totalWaitTime);
	this->oneLineResults.push_back(this->maxLengthOfLine);
	this->oneLineResults.push_back(this->maxWaitTime);
	this->oneLineResults.push_back(this->avgLengthOfLine);
}

// processes arrival of any of the simulations
void BankSimulation::processArrival(BankEvent& arrivalEvent, BankPriorityQueue& pQueue, BankQueue& bQueue, int lineNum) {
	BankEvent customer = arrivalEvent;
	pQueue.dequeue();

	outputFile << "Processing an arrival event at time:\t" << this->currentTime << std::endl;
	this->totalProcessed++; // counts each arrival as a person processed
	if(bQueue.isEmpty() && this->isTellerAvailable(lineNum)) {
		int departureTime = this->currentTime + customer.getTransactionTime();
		BankEvent newDepartureEvent(departureTime, 0, lineNum, false);
		pQueue.enqueue(newDepartureEvent);

		// chooses which teller to set unavailable using lineNum
		switch(lineNum) {
		case 1:
			this->tellerOneAvailable = false;
			break;
		case 2:
			this->tellerTwoAvailable = false;
			break;
		case 3:
			this->tellerThreeAvailable = false;
			break;
		default:
			this->tellerOneAvailable = false;
		}

		this->avgLengthOfLine += bQueue.length();
	} else {
		bQueue.enqueue(customer);
		this->maxLineLength(bQueue.length());
		this->avgLengthOfLine += bQueue.length();
	}
}

// process Departure 
void BankSimulation::processDeparture(BankEvent& departureEvent, BankPriorityQueue& pQueue, BankQueue& bQueue) {
	int lineNum = pQueue.peekFront().getLineNumber();
	pQueue.dequeue();
	outputFile << "Processing a departure event at time:\t" << this->currentTime << std::endl;

	if(!bQueue.isEmpty()) {
		BankEvent customer = bQueue.peekFront();
		bQueue.dequeue();
		int departureTime = this->currentTime + customer.getTransactionTime();
		BankEvent newDepartureEvent(departureTime, 0, lineNum, false);
		pQueue.enqueue(newDepartureEvent);

		int customerWaitTime = this->currentTime-customer.getTime();
		this->totalWaitTime += customerWaitTime;
		this->maxWaitInLine(customerWaitTime);

		this->avgLengthOfLine += bQueue.length();
	} else {
		switch(lineNum) {
		case 1:
			this->tellerOneAvailable = true;
			break;
		case 2:
			this->tellerTwoAvailable = true;
			break;
		case 3:
			this->tellerThreeAvailable = true;
			break;
		default:
			this->tellerOneAvailable = true;
		}
		this->avgLengthOfLine += bQueue.length();
	}
}

void BankSimulation::chooseArrivalLine(BankQueue& bQueue1, BankQueue& bQueue2, BankQueue& bQueue3, BankPriorityQueue& pQueue, BankEvent& arrivalEvent) {
	// if teller is avilable, then go straight to them
	if(this->tellerOneAvailable) {
		this->processArrival(arrivalEvent, pQueue, bQueue1, 1);
		return;
	} else if(this->tellerTwoAvailable) {
		this->processArrival(arrivalEvent, pQueue, bQueue2, 2);
		return;
	} else if(this->tellerThreeAvailable) {
		this->processArrival(arrivalEvent, pQueue, bQueue3, 3);
		return;
	}

	// if not, find the shortest line
	if(bQueue1.length() <= bQueue2.length()) {
		if(bQueue1.length() <= bQueue3.length()) {
			// bQueue1 is smallest
			this->processArrival(arrivalEvent, pQueue, bQueue1, 1);
		} else {
			// bQueue3 is smallest
			this->processArrival(arrivalEvent, pQueue, bQueue3, 3);
		}
	} else {
		if(bQueue2.length() <= bQueue3.length()) {
			// bQueue2 is smallest
			this->processArrival(arrivalEvent, pQueue, bQueue2, 2);
		} else {
			// bQueue3 is smallest
			this->processArrival(arrivalEvent, pQueue, bQueue3, 3);
		}
	}
}

void  BankSimulation::chooseDepartureLine(BankQueue& bQueue1, BankQueue& bQueue2, BankQueue& bQueue3, BankPriorityQueue& pQueue, BankEvent& departureEvent) {
	// chooses which queue for the departure event
	switch(departureEvent.getLineNumber()) {
	case 2:
		this->processDeparture(departureEvent, pQueue, bQueue2);
		break;
	case 3:
		this->processDeparture(departureEvent, pQueue, bQueue3);
		break;
	default:
		this->processDeparture(departureEvent, pQueue, bQueue1);
	}
}

void BankSimulation::chooseTellerArrival(BankEvent& arrivalEvent, BankPriorityQueue& pQueue, BankQueue& bQueue) {
	// chooses which queue for the arrival event
	if(this->tellerOneAvailable) {
		this->processArrival(arrivalEvent, pQueue, bQueue, 1);
		return;
	} else if(this->tellerTwoAvailable) {
		this->processArrival(arrivalEvent, pQueue, bQueue, 2);
		return;
	} else if(this->tellerThreeAvailable) {
		this->processArrival(arrivalEvent, pQueue, bQueue, 3);
		return;
	} else {
		this->processArrival(arrivalEvent, pQueue, bQueue, 0);
	}
}

bool BankSimulation::isTellerAvailable(int lineNum) {
	// check is any teller is available
	if(lineNum == 2) {
		return this->tellerTwoAvailable;
	} else if(lineNum == 3) {
		return this->tellerThreeAvailable;
	} else {
		return this->tellerOneAvailable;
	}
}

void BankSimulation::maxWaitInLine(int customerWaitTime) {
	if(customerWaitTime > this->maxWaitTime) {
		this->maxWaitTime = customerWaitTime;
	}
}

void BankSimulation::maxLineLength(int currentLineLength) {
	if(currentLineLength > this->maxLengthOfLine) {
		this->maxLengthOfLine = currentLineLength;
	}
}

void BankSimulation::reset() {
	// resets all the values to default values for next simulation run
	this->tellerOneAvailable = false;
	this->tellerTwoAvailable = false;
	this->tellerThreeAvailable = false;
	this->currentTime = 0;
	this->totalProcessed = 0;
	this->maxWaitTime = 0;
	this->maxLengthOfLine = 0;
	this->totalWaitTime = 0.0;
	this->avgLengthOfLine = 0.0;
}

void BankSimulation::generateResultsTable() {
	std::ofstream results("results", std::ios_base::app);

	results << "Results" << std::endl;
	results << std::left << std::setw(8) << std::setfill(' ') << "One Teller Simulation ";
	results << std::left << std::setw(11) << std::setfill(' ') << " ";
	results << std::left << std::setw(8) << std::setfill(' ') << this->oneTellerResults[1];
	results << std::left << std::setw(8) << std::setfill(' ') << this->oneTellerResults[2];
	results << std::left << std::setw(8) << std::setfill(' ') << this->oneTellerResults[3];
	results << std::left << std::setw(8) << std::setfill(' ') << this->oneTellerResults[4];
	results << std::endl;

	results << std::left << std::setw(8) << std::setfill(' ') << "Three Tellers Simulation ";
	results << std::left << std::setw(8) << std::setfill(' ') << " ";
	results << std::left << std::setw(8) << std::setfill(' ') << this->threeTellerResults[1];
	results << std::left << std::setw(8) << std::setfill(' ') << this->threeTellerResults[2];
	results << std::left << std::setw(8) << std::setfill(' ') << this->threeTellerResults[3];
	results << std::left << std::setw(8) << std::setfill(' ') << this->threeTellerResults[4];
	results << std::endl;

	results << std::left << std::setw(8) << std::setfill(' ') << "One Line Simulation ";
	results << std::left << std::setw(13) << std::setfill(' ') << " ";
	results << std::left << std::setw(8) << std::setfill(' ') << this->oneLineResults[1];
	results << std::left << std::setw(8) << std::setfill(' ') << this->oneLineResults[2];
	results << std::left << std::setw(8) << std::setfill(' ') << this->oneLineResults[3];
	results << std::left << std::setw(8) << std::setfill(' ') << this->oneLineResults[4];
	results << "\n" << std::endl;

	oneLineResults.clear();
	oneTellerResults.clear();
	threeTellerResults.clear();
}

BankNode::BankNode(int aTime, int tTime, bool isArrival, BankNode* nxt) {
	this->data.setEvent(aTime, tTime, isArrival);
	this->next = nxt;
}

BankQueue::BankQueue() {
	this->frontPtr = NULL;
	this->backPtr = NULL;
	this->queueLength = 0;
}

BankQueue::~BankQueue() {
	while(!this->isEmpty()) {
		this->dequeue();
	}
}

bool BankQueue::isEmpty() const {
	return this->backPtr == NULL;
}

bool BankQueue::enqueue(const BankEvent& newEvent) {
	BankNode* tempEventPtr = new BankNode(newEvent.getTime(), newEvent.getTransactionTime(), newEvent.getIsArrivalEvent(), NULL);

	if(this->isEmpty()) {
		this->frontPtr = tempEventPtr;
	} else {
		BankNode* backTempPtr = this->backPtr;
		backTempPtr->next = tempEventPtr;
	}

	this->backPtr = tempEventPtr;
	this->queueLength++;

	return true;
}

bool BankQueue::dequeue() {
	if(this->isEmpty()) {
		return false;
	} else {
		BankNode* toBeDeletedPtr = this->frontPtr;

		if(this->frontPtr == this->backPtr) {
			this->frontPtr = NULL;
			this->backPtr = NULL;
		} else {
			BankNode* frontTempPtr = this->frontPtr;
			this->frontPtr = frontTempPtr->next;
		}

		toBeDeletedPtr->next = NULL;
		delete toBeDeletedPtr;
		this->queueLength--;

		return true;
	}
}

int BankQueue::length() const {
	return this->queueLength;
}

BankEvent BankQueue::peekFront() const {
	return this->frontPtr->data;
}

BankPriorityQueue::BankPriorityQueue() {}

bool BankPriorityQueue::isEmpty() const {
	return this->bankList.empty();
}

bool BankPriorityQueue::enqueue(const BankEvent& newEvent) {
	this->bankList.push_back(newEvent);
	this->bankList.sort();
	return true;
}

bool BankPriorityQueue::dequeue() {
	if(this->isEmpty()) {
		return false;
	} else {
		this->bankList.pop_front();
		return true;
	}
}

BankEvent BankPriorityQueue::peekFront() const {
	return this->bankList.front();
}