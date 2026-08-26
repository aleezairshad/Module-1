#pragma once

#include <iostream>
#include <string>

using namespace std;

class Container
{
private:
	double* data;
	int size;
	bool isSample;
public:
	Container();
	~Container();
	void setIsSample(bool sample);
	bool getIsSample() const;
	void insertValue(double value);
	void insertRandomValues(int count);
	//void deleteValue(double value);  // I changed this to return a bool to indicate whether the value was found and deleted
	//void deleteRange(double start, double end); // I changed this to return a bool to indicate whether the value was found and deleted
	int deleteAll();
	int getSize() const;
	double* getData() const;
	//void readFromFile(const string& filename);  // I changed this to return an int to indicate the number of values read from the file
	void display() const;
	void sortData();

	int deleteValue(double value, bool deleteAll = false);

	bool deleteRange(double start, double end);

	int readFromFile(const string& filename);

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
	void calculateOutliers(double q1, double q3, double interquartileRange) const; //option N
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
	string calculateOutliersString() const; //option X
	void displayFrequencyTable(ostream& out = cout) const; //option Y
	void displayAllStatistics(ostream& out = cout) const; //option Z
	bool outputAllStatisticsToFile(const string& filename) const; //option Z
};

