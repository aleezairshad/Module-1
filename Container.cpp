#include "Container.h"
#include <cstdlib> 
#include <iomanip> 
#include <fstream>


#include <algorithm> // For std::sort


Container::Container()
{
	data = nullptr;
	size = 0;
	isSample = true; // Default to sample data
}

Container::~Container()
{
	delete[] data;
	data = nullptr;
}

int Container::getSize() const
{
	return size;
}

bool Container::getIsSample() const
{
	return isSample;
}

void Container::setIsSample(bool sample)
{
	isSample = sample;
}

double* Container::getData() const
{
	return data;
}

// sorting the data in ascending order
void Container::sortData()
{
    sort(data, data + size);
}

//Precondition:
//   The dataset is sorted in ascending order.

// Postcondition:
//   value is added to the dynamic array.
//   size is increased by one.
//   The dataset is sorted in ascending order.

void Container::insertValue(double value)
{
    double* newData = new double[size + 1];

    for (int i = 0; i < size; ++i)
    {
        newData[i] = data[i];
    }

    newData[size] = value;

    delete[] data;

    data = newData;
    ++size;

    sortData();
}

void Container::insertRandomValues(int count)
{
    // Precondition:
    // The dataset is sorted in ascending order.
    //
    // Postcondition:
    // 'count' random values are inserted into the dataset.
    // The dataset remains sorted in ascending order.
    // The size of the dataset increases by 'count'.
    for (int i = 0; i < count; ++i)
    {
		// Generate a random value between 0 and 100
		int randomInt = rand() % 101; // Random integer between 0 and 100
		double randomValue = static_cast<double>(randomInt);
       // double randomValue = static_cast<double>(rand()) / RAND_MAX * 100.0; // Random value between 0 and 100
        insertValue(randomValue);
    }


}


void Container::deleteValue(double value)
{
    // Precondition:
    // The dataset is sorted in ascending order.
    //
    // Postcondition:
    // All occurrences of 'value' are removed from the dataset.
    // The dataset remains sorted in ascending order.
    // The size of the dataset decreases accordingly.
    int newSize = 0;
    for (int i = 0; i < size; ++i)
    {
        if (data[i] != value)
        {
            ++newSize;
        }
    }
    double* newData = new double[newSize];
    int index = 0;
    for (int i = 0; i < size; ++i)
    {
        if (data[i] != value)
        {
            newData[index++] = data[i];
        }
    }
    delete[] data;
    data = newData;
    size = newSize;
    sortData();
}

void Container::deleteRange(double start, double end)
{
    // Precondition:
    // The dataset is sorted in ascending order.
    //
    // Postcondition:
    // All values in the range [start, end] are removed from the dataset.
    // The dataset remains sorted in ascending order.
    // The size of the dataset decreases accordingly.
    int newSize = 0;
    for (int i = 0; i < size; ++i)
    {
        if (data[i] < start || data[i] > end)
        {
            ++newSize;
        }
    }
    double* newData = new double[newSize];
    int index = 0;
    for (int i = 0; i < size; ++i)
    {
        if (data[i] < start || data[i] > end)
        {
            newData[index++] = data[i];
        }
    }
    delete[] data;
    data = newData;
    size = newSize;
    sortData();
}

void Container::deleteAll()
{
    // Precondition:
    // The dataset is sorted in ascending order.
    //
    // Postcondition:
    // All values are removed from the dataset.
    // The dataset is empty, and size is set to 0.
    delete[] data;
    data = nullptr;
    size = 0;
}

void Container::display() const
{
    // Precondition:
    // The dataset contains zero or more values.
    //
    // Postcondition:
    // The dataset is displayed in ascending order,
    // 15 values per row.

    for (int i = 0; i < size; ++i)
    {
        // Start each row with indentation
        if (i % 15 == 0)
        {
            cout << "\t";
        }

        // Display each value in a field of width 4
        cout << setw(4) << data[i];

        // Start a new row after every 15 values
        if ((i + 1) % 15 == 0)
        {
            cout << "\n";
        }
    }

    // If the last row did not contain exactly 15 values,
    // move to the next line.
    if (size % 15 != 0)
    {
        cout << "\n";
    }
}



//void Container::readFromFile(const string& filename)
//{
//    // Precondition:
//    // The dataset is sorted in ascending order.
//    //
//    // Postcondition:
//    // Values from the specified file are read and inserted into the dataset.
//    // The dataset remains sorted in ascending order.
//    // The size of the dataset increases accordingly.
//    ifstream inputFile(filename);
//    if (!inputFile)
//    {
//        cout << "\n\tERROR: File, " << filename << ", cannot be found.\n";
//        return;
//    }
//    double value;
//    while (inputFile >> value)
//    {
//        insertValue(value);
//    }
//    inputFile.close();
//}

void Container::readFromFile(const string& filename)
{
    // Precondition:
    // filename contains the name of a text file.
    //
    // Postcondition:
    // Each row is read as one value and inserted into the dataset.
    // The dataset remains sorted in ascending order.

    ifstream inputFile(filename);

    if (!inputFile)
    {
        cout << "\n\tERROR: File, "
            << filename
            << ", cannot be found.\n";
        return;
    }

    string row;

    while (getline(inputFile, row))
    {
        if (!row.empty())
        {
            double value = stod(row);

            insertValue(value);
        }
    }

    inputFile.close();
}