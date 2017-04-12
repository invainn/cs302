#include <iostream>
#include "Bank.h"

int main() {
	int counter = 0;

	BankSimulation bank;

	for(counter = 0; counter < 5; counter++) {
		bank.generateData(counter);
		bank.simulateOneTeller(counter);
		bank.simulateThreeTellers(counter);
		bank.simulateOneLine(counter);
		bank.generateResultsTable();
	}
	return 0;
}