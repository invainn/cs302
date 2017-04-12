#include <iostream>
#include <cstdlib>
#include "SortAlg.h"

int main() {

	SortAlg testObj;
	int counter = 0;

	// generate 1k
	std::cout << "Sorting for 1k numbers" << std::endl;
	testObj.generateDataSet(1000);
	std::vector<int> dataSet = testObj.getDataSet();

	for(counter = 0; counter < 10; counter++) {
		dataSet = testObj.getDataSet();
		testObj.bubbleSort(dataSet, 0, dataSet.size());
	}
	std::cout << "Bubble Sort Results" << std::endl;
	testObj.avg(10);
	std::cout << std::endl;

	for(counter = 0; counter < 10; counter++) {
		dataSet = testObj.getDataSet();
		testObj.quickSort(dataSet, 0, dataSet.size());
	}
	std::cout << "Quick Sort Results" << std::endl;
	testObj.avg(10);
	std::cout << std::endl;

	for(counter = 0; counter < 10; counter++) {
		dataSet = testObj.getDataSet();
		testObj.countingSort(dataSet);
	}
	std::cout << "Counting Sort Results" << std::endl;
	testObj.avg(10);
	std::cout << std::endl;
	testObj.clearDataSet();
	std::cout << std::endl;

	dataSet = testObj.getDataSet();
	testObj.countingSort(dataSet);
	testObj.clearTotals();


	// sorted 1k
	std::cout << "Testing sorted 1k list" << std::endl;
	for(counter = 0; counter < 10; counter++) {
		testObj.bubbleSort(dataSet, 0, dataSet.size());
	}
	std::cout << "Bubble Sort Results" << std::endl;
	testObj.avg(10);
	std::cout << std::endl;

	for(counter = 0; counter < 10; counter++) {
		testObj.quickSort(dataSet, 0, dataSet.size());
	}
	std::cout << "Quick Sort Results" << std::endl;
	testObj.avg(10);
	std::cout << std::endl;

	for(counter = 0; counter < 10; counter++) {
		testObj.countingSort(dataSet);
	}
	std::cout << "Counting Sort Results" << std::endl;
	testObj.avg(10);
	std::cout << std::endl;




	// generate 10k
	std::cout << "Sorting for 10k numbers" << std::endl;
	testObj.generateDataSet(10000);
	dataSet = testObj.getDataSet();

	for(counter = 0; counter < 10; counter++) {
		testObj.bubbleSort(dataSet, 0, dataSet.size());
	}
	std::cout << "Bubble Sort Results" << std::endl;
	dataSet = testObj.getDataSet();
	testObj.avg(10);
	std::cout << std::endl;

	for(counter = 0; counter < 10; counter++) {
		testObj.quickSort(dataSet, 0, dataSet.size());
	}
	std::cout << "Quick Sort Results" << std::endl;
	dataSet = testObj.getDataSet();
	testObj.avg(10);
	std::cout << std::endl;

	for(counter = 0; counter < 10; counter++) {
		testObj.countingSort(dataSet);
	}
	std::cout << "Counting Sort Results" << std::endl;
	testObj.avg(10);
	std::cout << std::endl;
	testObj.clearDataSet();
	std::cout << std::endl;

	dataSet = testObj.getDataSet();
	testObj.countingSort(dataSet);
	testObj.clearTotals();


	// sorted 10k
	std::cout << "Testing sorted 10k list" << std::endl;
	for(counter = 0; counter < 10; counter++) {
		testObj.bubbleSort(dataSet, 0, dataSet.size());
	}
	std::cout << "Bubble Sort Results" << std::endl;
	testObj.avg(10);
	std::cout << std::endl;

	for(counter = 0; counter < 10; counter++) {
		testObj.quickSort(dataSet, 0, dataSet.size());
	}
	std::cout << "Quick Sort Results" << std::endl;
	testObj.avg(10);
	std::cout << std::endl;

	for(counter = 0; counter < 10; counter++) {
		testObj.countingSort(dataSet);
	}
	std::cout << "Counting Sort Results" << std::endl;
	testObj.avg(10);
	std::cout << std::endl;


	//generate 100k
	std::cout << "Sorting for 100k numbers" << std::endl;
	testObj.generateDataSet(100000);
	dataSet = testObj.getDataSet();

	for(counter = 0; counter < 1; counter++) {
		testObj.bubbleSort(dataSet, 0, dataSet.size());
	}
	std::cout << "Bubble Sort Results" << std::endl;
	dataSet = testObj.getDataSet();
	testObj.avg(1);
	std::cout << std::endl;

	for(counter = 0; counter < 1; counter++) {
		testObj.quickSort(dataSet, 0, dataSet.size());
	}
	std::cout << "Quick Sort Results" << std::endl;
	testObj.avg(1);
	std::cout << std::endl;

	for(counter = 0; counter < 10; counter++) {
		testObj.countingSort(dataSet);
	}
	std::cout << "Counting Sort Results" << std::endl;
	testObj.avg(10);
	std::cout << std::endl;
	testObj.clearDataSet();
	std::cout << std::endl;
	
	dataSet = testObj.getDataSet();
	testObj.countingSort(dataSet);
	testObj.clearTotals();

	// sorted 100k
	std::cout << "Testing sorted 100k list" << std::endl;
	for(counter = 0; counter < 10; counter++) {
		testObj.bubbleSort(dataSet, 0, dataSet.size());
	}
	std::cout << "Bubble Sort Results" << std::endl;
	testObj.avg(1);
	std::cout << std::endl;

	for(counter = 0; counter < 10; counter++) {
		testObj.quickSort(dataSet, 0, dataSet.size());
	}
	std::cout << "Quick Sort Results" << std::endl;
	testObj.avg(1);
	std::cout << std::endl;

	for(counter = 0; counter < 10; counter++) {
		testObj.countingSort(dataSet);
	}
	std::cout << "Counting Sort Results" << std::endl;
	testObj.avg(10);
	std::cout << std::endl;

	return 0;
}

