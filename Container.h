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
	void deleteAll();
	int getSize() const;
	double* getData() const;
	//void readFromFile(const string& filename);  // I changed this to return an int to indicate the number of values read from the file
	void display() const;
	void sortData();

	bool deleteValue(double value, bool deleteAll = false);

	bool deleteRange(double start, double end);

	int readFromFile(const string& filename);

	//function for calculating the mean of the dataset
	double calculateMean() const;

	//function for calculating the median of the dataset
	double calculateMedian() const;

	//function for calculating the mode of the dataset
	string calculateMode() const;

	double calculateStandardDeviation() const; //function for calculating the standard deviation of the dataset

	double calculateSkewness() const; //function for calculating the skewness of the dataset

	double calculateKurtosis() const; //function for calculating the kurtosis of the dataset

	double calculateKurtosisExcess() const; //function for calculating the kurtosis excess of the dataset


};




