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

// Precondition: None
// Postcondition: Returns the size of the dataset
int Container::getSize() const
{
	return size;
}


// Precondition: None
// Postcondition: Returns true if the dataset is a sample, false if it is a population
bool Container::getIsSample() const
{
	return isSample;
}

// Precondition: getIsSample() must be called before this function to determine the current state of the dataset
// Postcondition: Sets the dataset to be a sample or a population based on the input parameter
void Container::setIsSample(bool sample)
{
	isSample = sample;
}

// Precondition: None
// Postcondition: Returns a pointer to the dynamic array containing the dataset
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

// Precondition: count is a positive integer
// Postcondition: 'count' random values are inserted into the dataset, and the dataset remains sorted in ascending order
// Postcondition:
// 'count' random values are inserted into the dataset.
// The dataset remains sorted in ascending order.
// The size of the dataset increases by 'count'.
void Container::insertRandomValues(int count)
{
    for (int i = 0; i < count; ++i)
    {
		// Generate a random value between 0 and 100
		int randomInt = rand() % 101; // Random integer between 0 and 100
		double randomValue = static_cast<double>(randomInt);
        insertValue(randomValue);
    }
}


// Precondition: value is a double, deleteAll is a boolean
// Postcondition: If deleteAll is true, all occurrences of value are removed from the dataset.
bool Container::deleteValue(double value, bool deleteAll)
{
    int deleteCount = 0;
	// Count how many occurrences of the value to delete exist in the dataset
    for (int i = 0; i < size; ++i)
    {
        if (data[i] == value)
        {
            ++deleteCount;
            if (!deleteAll)
            {
                break;
            }
        }
    }
	// If no occurrences of the value were found, return false
    if (deleteCount == 0)
    {
        return false;
    }

    int newSize = size - deleteCount;
	// If the new size is zero, delete the data array and set it to nullptr
    if (newSize == 0)
    {
        delete[] data;
        data = nullptr;
        size = 0;
        return true;
    }

	double* newData = new double[newSize]; // Create a new array to hold the remaining values

    int index = 0;
    int deleted = 0;
	// Copy over the values that are not equal to the value to delete
    for (int i = 0; i < size; ++i)
    {
        if (data[i] == value)
        {
            if (deleteAll)
            {
                ++deleted;
                continue;
            }
            if (deleted == 0)
            {
                ++deleted;
                continue;
            }
        }
        if (index < newSize)
        {
            newData[index++] = data[i];
        }
    }

    delete[] data;
    data = newData;
    size = newSize;

    return true;
}

// Precondition: start and end are doubles, with start <= end
// Postcondition: All values in the dataset that are within the range [start, end] are removed from the dataset.
bool Container::deleteRange(double start, double end)
{
    int newSize = 0;
	// Count how many values are outside the specified range
    for (int i = 0; i < size; ++i)
    {
        if (data[i] < start || data[i] > end)
        {
            ++newSize;
        }
    }
	// If the new size is the same as the current size, no values were deleted
    if (newSize == size)
    {
        return false;
    }
	// If the new size is zero, delete the data array and set it to nullptr
    if (newSize == 0)
    {
        delete[] data;
        data = nullptr;
        size = 0;
        return true;
    }

	double* newData = new double[newSize]; // Create a new array to hold the remaining values

    int index = 0;
	// Copy over the values that are outside the specified range
    for (int i = 0; i < size; ++i)
    {
        if (data[i] < start || data[i] > end)
        {
            if (index < newSize)
            {
                newData[index++] = data[i];
            }
        }
    }

    delete[] data;
    data = newData;
    size = newSize;

    return true;
}

// Precondition:
// The dataset is sorted in ascending order.
//
// Postcondition:
// All values are removed from the dataset.
// The dataset is empty, and size is set to 0.
void Container::deleteAll()
{
    delete[] data;
    data = nullptr;
    size = 0;
}

// Precondition:
// The dataset is sorted in ascending order.
//
// Postcondition:
// Displays the dataset in ascending order,
// 15 values per row.
void Container::display() const
{

    for (int i = 0; i < size; ++i)
    {
        // Indent the beginning of each row
        if (i % 15 == 0)
        {
            cout << "\t";
        }

        // Display value with guaranteed separation
        cout << setw(3) << data[i] << " ";

        // New line after every 15 values
        if ((i + 1) % 15 == 0)
        {
            cout << "\n";
        }
    }

    // New line if the final row has fewer than 15 values
    if (size % 15 != 0)
    {
        cout << "\n";
    }
}

// Precondition:
// filename contains the name of a text file.
//
// Postcondition:
// Numeric values from the file are inserted into the dataset.
// The dataset remains sorted in ascending order.
// Returns the number of values successfully inserted.
// Returns 0 if the file cannot be opened.
int Container::readFromFile(const string& filename)
{

    ifstream inputFile(filename);
    if (!inputFile)
    {
        cout << "\n\tERROR: File, "
            << filename
            << ", cannot be found.\n";

        return 0;
    }

    int count = 0;
    double value;

    while (inputFile >> value)
    {
        insertValue(value);
        ++count;
    }

    inputFile.close();

    return count;
}

