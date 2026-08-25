#pragma once
#include <iostream>
#include <ostream>
#include <string>

using namespace std;

/*
* Class check list:
* private:
*	double* data
*	int size
*	bool isSample
* public:
*	constructor
*	destructor
*	setIsSample (1)
*	getIsSample (1)
*	insertValue (2)
*	insertRandomValue (2)
*	readFromFile (2)
*	deleteValue (3)
*	deleteRange (3)
*	deleteAll (3)
*	getSize (sub-func for dynamic array shrink and expand)
*	getData (to display current index in array)
*	display (for menu)
*	sortData (ascending order)
*/


class Container
{
private:
	double* data;
	int size;
	bool isSample;
public:
	//Hany's part
	Container();
	~Container();
	void setIsSample(bool sample);
	bool getIsSample() const;
	void insertValue(double value);
	void insertRandomValues(int count);
	//void deleteValue(double value);
	bool deleteValue(double value, bool deleteAll = false); //update 1 made by Hany
	//void deleteRange(double start, double end);
	bool deleteRange(double start, double end); //update 1 made by Hany
	void deleteAll();
	int getSize() const;
	double* getData() const;
	int readFromFile(const string& filename);
	void display() const;
	void sortData();

	//update 1 made by Hany
	double calculateMean() const;
	double calculateMedian() const;
	string calculateMode() const;
	double calculateStandardDeviation() const; //function for calculating the standard deviation of the dataset
	double calculateSkewness() const; //function for calculating the skewness of the dataset
	double calculateKurtosis() const; //function for calculating the kurtosis of the dataset
	double calculateKurtosisExcess() const; //function for calculating the kurtosis excess of the dataset
	double calculateCoefficientOfVariation() const;

	//Aleeza's part A-E
	double calculateMinimum() const;
	double calculateMaximum() const;
	double calculateRange() const;
	double calculateSum() const;

	//Aleeza's part W-Z
	double calculateRelativeStandardDeviation() const;
	string calculateOutliersString() const;
	void displayFrequencyTable(ostream& out = cout) const;
	void displayAllStatistics(ostream& out = cout) const;
	bool outputAllStatisticsToFile(const string& filename) const;

	//Thanh's part from J-R
	double calculateVariance() const;
	double calculateMidrange() const;
	void calculateQuartiles(double& q1, double& q2, double& q3) const;
	double calculateInterquartileRange(double q1, double q3) const;
	void calculateOutliers(double q1, double q3, double interquartileRange) const;
	double calculateSumOfSquares() const;
	double calculateMeanAbsoluteDeviation() const;
	double calculateRootMeanSquare() const;
	double calculateStandardErrorOfMean() const;

};

