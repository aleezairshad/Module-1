#pragma once
#include <iostream>
#include <string>

using namespace std;

class Container
{
private:
	int* data;
	int size;
	bool isSample;
public:
	Container(); // Constructor
	~Container(); // Destructor
	void setIsSample(bool sample); // Set whether the dataset is a sample or a population
	bool getIsSample() const;  // Get whether the dataset is a sample or a population
	void insertValue(int value); // Insert a value into the dataset
	void insertRandomValues(int count); // Insert a specified number of random values into the dataset
	int deleteAll();  // Delete all values from the dataset
	int getSize() const; // Get the size of the dataset
	int* getData() const; // Get a pointer to the dynamic array containing the dataset
	void display() const; // Display the dataset in ascending order, 15 values per row
	void sortData();      // Sort the dataset in ascending order
	int deleteValue(int value, bool deleteAll = false); // Delete a specific value from the dataset, with an option to delete all occurrences
	bool deleteRange(int start, int end);  // Delete all values within a specified range from the dataset
	int readFromFile(const string& filename);  // Read values from a specified file and insert them into the dataset

	//option F-I AND S-V
	//function for calculating the mean of the dataset
	double calculateMean() const; //option F
	//function for calculating the median of the dataset 
	double calculateMedian() const; //option G
	//function for calculating the mode of the dataset
	string calculateMode() const;//option H
	double calculateStandardDeviation() const; //option I function for calculating the standard deviation of the dataset
	double calculateSkewness() const; // option S function for calculating the skewness of the dataset
	double calculateKurtosis() const; // option T function for calculating the kurtosis of the dataset
	double calculateKurtosisExcess() const; // option U function for calculating the kurtosis excess of the dataset
	double calculateCoefficientOfVariation() const; //option V function for calculating the coefficient of variation of the dataset


	//Thanh's part from J-R
	double calculateVariance() const; //option J
	double calculateMidrange() const; //option K
	void calculateQuartiles(double& q1, double& q2, double& q3) const; //option L
	double calculateInterquartileRange(double q1, double q3) const; //option M
	double calculateSumOfSquares() const; //option O
	double calculateMeanAbsoluteDeviation() const; //option P
	double calculateRootMeanSquare() const; //option Q
	double calculateStandardErrorOfMean() const; //option R

	//Aleeza's part A-E
	double calculateMinimum() const; //option A
	double calculateMaximum() const; //option B
	double calculateRange() const; //option C
	double calculateSum() const; //option E

	//Aleeza's part W-Z
	double calculateRelativeStandardDeviation() const; //option W
	string calculateOutliersString() const; 
	void displayFrequencyTable(ostream& out = cout) const; //option Y
	void displayAllStatistics(ostream& out = cout) const; //option Z
	bool outputAllStatisticsToFile(const string& filename) const; //option Z
};
