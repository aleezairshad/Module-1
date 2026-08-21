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

	/*Standard Deviation

Standard deviation is a measure of dispersion of data values from the mean. The formula for standard deviation is the square root of the sum of squared differences from the mean divided by the size of the data set.

For a Population
?=?ni=1(xi??)2n?????????????

For a Sample
*/
	double calculateStandardDeviation() const;
};




