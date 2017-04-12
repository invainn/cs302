#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include "SortAlg.h"

void SortAlg::generateDataSet(int amountOfNum) {
	int counter = 0;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 1000000);

	for(counter = 0; counter < amountOfNum; counter++) {
		int genNumber = dis(gen);

		this->dataSet.push_back(genNumber);
	}
}

void SortAlg::clearDataSet() {
	this->dataSet.clear();
}

void SortAlg::bubbleSort(std::vector<int>& dataSet, int first, int last) {
	clock_t start = clock();
	clock_t end;
	double overallTime;

	std::vector<int> dataSample = dataSet;

	int numOfComparisons = 0;
	double numOfSwaps = 0.0;

	bool sorted = false;
	int pass = 1;
	int index = first;
	int nextIndex = 0;
	int vectorSize = last;
	while(!sorted && (pass < vectorSize)) {
		sorted = true;
		for(index = 0; index < vectorSize - pass; index++) {
			nextIndex = index + 1;
			if(dataSample[index] > dataSample[nextIndex]) {
				std::swap(dataSample[index], dataSample[nextIndex]);
				numOfSwaps++;
				sorted = false;
			}
			numOfComparisons++;
		}
		pass++;
	}

	end = clock();
	overallTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	this->sortTimes.push_back(overallTime);
	this->totalComparisons.push_back(numOfComparisons);
	this->totalSwaps.push_back(numOfSwaps);

}

void SortAlg::quickSort(std::vector<int> dataSet, int first, int last) {
	clock_t start = clock();
	clock_t end;
	double overallTime;

	std::vector<int> dataSample = dataSet;

	int numOfComparisons = 0;
	double numOfSwaps = 0.0;

	if((last - first + 1) < 4) {
		this->bubbleSort(dataSample, first, last);
	} else {
		int pivotIndex = this->partition(dataSample, first, last, numOfComparisons, numOfSwaps);

		this->quickSort(dataSample, first, pivotIndex-1, numOfComparisons, numOfSwaps);
		this->quickSort(dataSample, pivotIndex+1, last, numOfComparisons, numOfSwaps);
	}

	end = clock();
	overallTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	this->sortTimes.push_back(overallTime);
	this->totalComparisons.push_back(numOfComparisons);
	this->totalSwaps.push_back(numOfSwaps);
}

void SortAlg::quickSort(std::vector<int>& dataSet, int first, int last, int &numOfComparisons, double &numOfSwaps) {
	if((last - first + 1) < 4) {
		this->bubbleSort(dataSet, first, last);
	} else {
		int pivotIndex = this->partition(dataSet, first, last, numOfComparisons, numOfSwaps);

		this->quickSort(dataSet, first, pivotIndex-1, numOfComparisons, numOfSwaps);
		this->quickSort(dataSet, pivotIndex+1, last, numOfComparisons, numOfSwaps);
	}
}

void SortAlg::countingSort(std::vector<int>& dataSet) {
	clock_t start = clock();
	clock_t end;
	double overallTime;

	std::vector<int> dataSample = dataSet;

	int index = 0;
	int maxNum = 0;
	std::vector<int> outputVec(dataSet.size());
	
	for(index = 0; index < dataSet.size(); index++) {
		if(dataSet[index] > maxNum) {
			maxNum = dataSample[index];
		}
	}

	std::vector<int> countVec(maxNum+1,0);
	for(index = 1; index < dataSet.size(); index++) {
		countVec[dataSample[index]]++;
	}

	for(index = 1; index <= maxNum; index++) {
		countVec[index] += countVec[index-1];
	}

	for(index = dataSet.size(); index >= 1; index--) {
		outputVec[countVec[dataSample[index]]] = dataSample[index];
		countVec[dataSample[index]]--;
	}


	end = clock();
	overallTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	this->sortTimes.push_back(overallTime);
}

std::vector<int> SortAlg::getDataSet() {
	return this->dataSet;
}

int SortAlg::partition(std::vector<int>& dataSet, int first, int last, int &numOfComparisons, double &numOfSwaps) {
	int mid = first + (last-first)/2;
	this->sortFirstMiddleLast(dataSet, first, mid, last, numOfComparisons, numOfSwaps);
	std::swap(dataSet[mid], dataSet[last-1]);
	int pivotIndex = last - 1;
	int pivot = dataSet[pivotIndex];

	int indexFromLeft = first + 1;
	int indexFromRight = last - 2;

	bool done = false;
	while(!done) {
		while(dataSet[indexFromLeft] < pivot) {
			indexFromLeft++;
		}
		numOfComparisons++;

		while(dataSet[indexFromRight] > pivot) {
			indexFromRight--;
		}
		numOfComparisons++;

		if(indexFromLeft < indexFromRight) {
			std::swap(dataSet[indexFromLeft], dataSet[indexFromRight]);
			numOfSwaps++;
			indexFromLeft++;
			indexFromRight--;
		} else {
			done = true;
		}
		numOfComparisons++;
	}

	std::swap(dataSet[pivotIndex], dataSet[indexFromLeft]);
	numOfSwaps++;
	pivotIndex = indexFromLeft;

	return pivotIndex;
}

void SortAlg::sortFirstMiddleLast(std::vector<int>& dataSet, int first, int mid, int last, int &numOfComparisons, double &numOfSwaps) {
	if(dataSet[first] > dataSet[mid]) {
		std::swap(dataSet[first], dataSet[mid]);
		numOfSwaps++;
	}
	numOfComparisons++;

	if(dataSet[mid] > dataSet[last]) {
		std::swap(dataSet[mid], dataSet[last]);
		numOfSwaps++;
	}
	numOfComparisons++;

	if(dataSet[first] > dataSet[mid]) {
		std::swap(dataSet[first], dataSet[mid]);
		numOfSwaps++;
	} 
	numOfComparisons++;
}

void SortAlg::avg(int numOfRuns) {
	double avgTime = 0.0;
	int avgComp = 0;
	double avgSwaps = 0.0;

	for(std::vector<double>::iterator i = this->sortTimes.begin(); i != sortTimes.end(); ++i) {
		avgTime += *i;
	}
	avgTime /= numOfRuns;

	for(std::vector<int>::iterator i = this->totalComparisons.begin(); i != totalComparisons.end(); ++i) {
		avgComp += *i;
	}

	avgComp /= numOfRuns;

	for(std::vector<double>::iterator i = this->totalSwaps.begin(); i != totalSwaps.end(); ++i) {
		avgSwaps += *i;
	}

	avgSwaps /= numOfRuns;

	std::cout << "Average CPU run time: " << avgTime << std::endl;
	std::cout << "Average comparisons: " << avgComp << std::endl;
	std::cout << "Average swaps: " << avgSwaps << std::endl;

	this->clearTotals();
}

void SortAlg::clearTotals() {
	this->sortTimes.clear();
	this->totalComparisons.clear();
	this->totalSwaps.clear();
}