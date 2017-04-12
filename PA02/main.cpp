//  Created by Shehryar Khattak for CS302 Spring 2016 class.

#include <iostream>
#include <fstream>
#include <vector>

int kSmall(int, std::vector<int>, int, int);
void logFileOut(int, std::vector<int>);

int main(){

    //Declerations (insert as needed)
    int kSmall_pos;	        //For User Input
    int kSmall_val=0;       //Populate using your algorithm implementation
    int pivot;              //Pivot position in vector
    int readFileElement = 0; //File will read an int into this variable
    std::ifstream file; // ifstream object to be used to read from file
    std::vector<int> kSmall_vector;   //Vector to be used to store data file

    //User Input DO NOT MODIFY
    std::cout<<"Please enter required kth smallest value:";
    std::cin>>kSmall_pos;


    //File Read code (insert) - This code should be able to parse the data in a text file similar to the provided one and store values in a vector for processing.
    file.open("data.txt"); //Opens file with determined name data.txt
    while(!file.eof()) {
        file >> readFileElement;
        kSmall_vector.push_back(readFileElement);
    }
    file.close();

    //Checks if kSmall_pos is out of range, if true, then return error
    if(kSmall_pos > kSmall_vector.size() || kSmall_pos < 0) {
        std::cout << "Error: kth smallest value is out of range" << std::endl;
        return -1;
    }

    //Deleting old log
    remove("log.txt");

    //kmsall algorithm implementation or function call (insert) - implement using recursion as indicated
    kSmall_val = kSmall(kSmall_pos, kSmall_vector, 0, kSmall_vector.size());


    //Log file output (insert) - preferred in .txt format according to instructions posted on assignment page



    //Output DO NOT MODIFY
    std::cout<<"kth smallest value = "<<kSmall_val<<std::endl;
}

/** Chooses the kth smallest element in a vector.
   @pre Assumes first and last are vector's beginning and end and that kSmall_vector is populated
   @post If successful, logFileOut is called and either the function is called again or returns the kth smallest value
   @param kSmall_pos  An integer that represents k
   @param kSmall_vector  A vector that holds integer values to be parsed through
   @param first  An integer that is the first element to be looked at in the vector
   @param last  An integer that is the last element to be looked at in the vector
   @return A integer that is the kth smallest element in the vector. */
int kSmall(int kSmall_pos, std::vector<int> kSmall_vector, int first, int last) {
    //Chosen pivot value and pivot index
    int pivotIndex = first;
    int pivot = kSmall_vector[pivotIndex];
    std::vector<int> kLessThanPivot; //Vector that stores values less than pivot
    std::vector<int> kGreaterThanPivot;//Vector that stores values greater than pivot
    int afterPivot = 0; //Gets position after pivot is inserted into new partitioned vector
    int counter = 0; //Loop counter 

    //Partitioning the vector
    for(counter = 0; counter < kSmall_vector.size(); counter++) {
        if(kSmall_vector[counter] < pivot) {
            kLessThanPivot.push_back(kSmall_vector[counter]);
        } else if(kSmall_vector[counter] > pivot) {
            kGreaterThanPivot.push_back(kSmall_vector[counter]);
        }
    }

    //Building partitioned vector
    //Inserting kLessThanPivot into kSmall_vector
    for(int counter = 0; counter < kLessThanPivot.size(); counter++) {
        kSmall_vector[counter] = kLessThanPivot[counter];
    }
    kSmall_vector[kLessThanPivot.size()] = pivot; //Inserting pivot value
    pivotIndex = kLessThanPivot.size();

    //Inserting kGreaterThanPivot into kSmall_vector
    afterPivot = kLessThanPivot.size()+1; //Gets position after pivot to insert kGreaterThanPivot
    for(int counter = afterPivot; counter < kSmall_vector.size(); counter++) {
        kSmall_vector[counter] = kGreaterThanPivot[counter-afterPivot];
    }

    logFileOut(pivot, kSmall_vector); //Creates or appends log file 

     if(kSmall_pos < pivotIndex - first + 1) {
        return kSmall(kSmall_pos, kSmall_vector, first, pivotIndex-1);
     } else if(kSmall_pos == pivotIndex - first + 1) {
        return pivot;
     } else {
        return kSmall(kSmall_pos - (pivotIndex - first + 1), kSmall_vector, pivotIndex + 1, last);
     }
}

/** Creates or appends a log file of kSmall in a specific format
    @pre Assumes that kSmall_vector is populated
    @post If successful, log file is created or appended with pivot value and the vector elements in order
    @param kSmall_pos  An integer that represents k
    @param kSmall_vector  A vector that holds values to be parsed through */
void logFileOut(int pivot, std::vector<int> kSmall_vector) {
    std::ofstream logFile("log.txt", std::ios_base::app); //ofstream object that is initialized with log file name and append
    int counter = 0; //Loop counter

    logFile << "Pivot Value: " << pivot << "\n[ ";
    for(counter = 0; counter < kSmall_vector.size(); counter++) {
        logFile << kSmall_vector[counter] << " ";
    }
    logFile << "]\n";
}