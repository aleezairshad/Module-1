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
	void deleteValue(double value);
	void deleteRange(double start, double end);
	void deleteAll();
	int getSize() const;
	double* getData() const;
	void readFromFile(const string& filename);
	void display() const;
	void sortData();
};


