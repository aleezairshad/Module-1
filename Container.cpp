#include "Container.h"
#include <cstdlib> 
#include <iomanip> 
#include <fstream>
#include <cmath>


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
        cout << setw(3) << static_cast<int>(data[i]) << " ";

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

// Precondition: The dataset is not empty.
// Postcondition: Returns the mean (average) of the dataset.
double Container::calculateMean() const
{
    if (size == 0)
    {
        cout << "\n\tException Error: Dataset is empty.\n";
        return 0.0; // Return 0 or handle the error as appropriate
    }
    double sum = 0.0;
    for (int i = 0; i < size; ++i)
    {
        sum += data[i];
    }
    return sum / size;
}


// Precondition: The dataset is sorted in ascending order and is not empty.
// Postcondition: Returns the median of the dataset.
double Container::calculateMedian() const
{
    if (size == 0)
    {
        cout << "\n\tException Error: Dataset is empty.\n";
        return 0.0; // Return 0 or handle the error as appropriate
    }

    if (size % 2 == 0)
    {
        // If the size is even, return the average of the two middle values
        int midIndex = size / 2;
        return (data[midIndex - 1] + data[midIndex]) / 2.0;
    }
    else
    {
        // If the size is odd, return the middle value
        int midIndex = size / 2;
        return data[midIndex];
    }
}

// Precondition: The dataset is sorted in ascending order and is not empty.
// Postcondition: Returns the mode of the dataset. If there are multiple modes, returns the smallest one.
string Container::calculateMode() const
{
    if (size == 0)
    {
        cout << "\n\tException Error: Dataset is empty.\n";
        return ""; // Return an empty string or handle the error as appropriate
    }
    int maxCount = 1;
    int currentCount = 1;
    string modes = "";
    bool hasMultipleModes = false;
    for (int i = 1; i < size; ++i)
    {
        if (data[i] == data[i - 1])
        {
            ++currentCount;
        }
        else
        {
            if (currentCount > maxCount)
            {
                maxCount = currentCount;
                modes = to_string(static_cast<int>(data[i - 1]));
                hasMultipleModes = false;
            }
            else if (currentCount == maxCount)
            {
                modes += " " + to_string(static_cast<int>(data[i - 1]));
                hasMultipleModes = true;
            }
            currentCount = 1;
        }
    }
    // Check the last value
    if (currentCount > maxCount)
    {
        modes = to_string(static_cast<int>(data[size - 1]));
        hasMultipleModes = false;
    }
    else if (currentCount == maxCount)
    {
        modes += " " + to_string(static_cast<int>(data[size - 1]));
        hasMultipleModes = true;
    }
    return modes;
}

// Precondition: The dataset is not empty.
// Postcondition: Returns the standard deviation of the dataset. If the dataset is a sample, uses n-1 in the denominator; if it's a population, uses n.
double Container::calculateStandardDeviation() const
{
    double mean = calculateMean();
    double sumSquaredDifferences = 0.0;
    for (int i = 0; i < size; ++i)
    {
        double difference = data[i] - mean;
        sumSquaredDifferences += difference * difference;
    }
    double variance;
    if (isSample)
    {
        variance = sumSquaredDifferences / (size - 1); // Sample standard deviation
    }
    else
    {
        variance = sumSquaredDifferences / size; // Population standard deviation
    }
    return sqrt(variance);
}


// Precondition: The dataset is not empty.
// Postcondition: returns the skewness of the dataset. If the dataset is a sample, uses n(n-1)(n-2) in the denominator; if it's a population, uses n.
double Container::calculateSkewness() const
{
    //validate that size is greater than 2 for sample skewness calculation
    if (isSample && size < 3)
    {
        return NAN; // Return NaN (Not a Number) if sample size is less than 3
    }
    double mean = calculateMean();
    double stdDev = calculateStandardDeviation();
    double sumCubedDifferences = 0.0;

	//validate that stdDev is not zero to avoid division by zero
    if (stdDev == 0.0)
    {
		return NAN; // Return NaN (Not a Number) if standard deviation is zero
    }



    for (int i = 0; i < size; ++i)
    {
        double difference = data[i] - mean;
        sumCubedDifferences += difference * difference * difference;
    }
    double skewness;
    if (isSample)
    {
        //skewness = (size * (size - 1) * (size - 2)) * sumCubedDifferences / ((size - 1) * (size - 1) * (size - 1) * stdDev * stdDev * stdDev);
		skewness = (static_cast<double>(size) / ((size - 1) * (size - 2))) * (sumCubedDifferences / pow(stdDev, 3));
    }
    else
    {
       // skewness = sumCubedDifferences / (size * stdDev * stdDev * stdDev);
		skewness = (sumCubedDifferences / (size * pow(stdDev, 3)));
    }
    return skewness;
}

// Precondition: The dataset is not empty.
// Postcondition: Returns the kurtosis of the dataset. For a sample, uses the adjusted sample kurtosis formula.
// For a population, uses the population kurtosis formula. Returns NAN if the sample contains fewer than 4 values or if the standard deviation is zero.
double Container::calculateKurtosis() const
{
    //validate that size is greater than 3 for sample kurtosis calculation
    if (isSample && size < 4)
    {
        return NAN; // Return NaN (Not a Number) if sample size is less than 4
    }
    double mean = calculateMean();
    double stdDev = calculateStandardDeviation();
    double sumFourthDifferences = 0.0;
    //validate that stdDev is not zero to avoid division by zero
    if (stdDev == 0.0)
    {
        return NAN; // Return NaN (Not a Number) if standard deviation is zero
    }

    for (int i = 0; i < size; ++i)
    {
        double difference = data[i] - mean;
        //sumFourthDifferences += difference * difference * difference * difference;
		sumFourthDifferences += pow(difference, 4);
    }
    double kurtosis;
    if (isSample)
    {
   
		kurtosis = ((static_cast<double>(size) * (size + 1) / ((size - 1) * (size - 2) * (size - 3))) * (sumFourthDifferences / pow(stdDev, 4)));
    }
    else
    {
        kurtosis = sumFourthDifferences / (size * pow(stdDev, 4));
    }
    return kurtosis;
}

// Precondition: The dataset is not empty.
// Precondition: The dataset contains enough values. Postcondition: Returns the kurtosis excess of the dataset. Returns NAN if the sample size is less than 4
// or if the standard deviation is zero.
double Container::calculateKurtosisExcess() const
{
	//validate sample size for kurtosis excess calculation
    if (isSample && size < 4)
    {
        return NAN; // Return NaN (Not a Number) if sample size is less than 4
    }

	double mean = calculateMean();
    double stdDev = calculateStandardDeviation();
	double sumFourthDifferences = 0.0;

	//validate that stdDev is not zero to avoid division by zero
    if (stdDev == 0.0)
    {
        return NAN; // Return NaN (Not a Number) if standard deviation is zero
    }
    for (int i = 0; i < size; ++i)
    {
        double difference = data[i] - mean;
        sumFourthDifferences += pow(difference, 4);
	}
    double kurtosisExcess;
    if (isSample)
    {
        kurtosisExcess = (static_cast<double>(size) * (size + 1) / ((size - 1) * (size - 2) * (size - 3))) * (sumFourthDifferences / pow(stdDev, 4)) - 
            (3.0 * (size - 1) * (size - 1) / ((size - 2) * (size - 3)));
    }
    else
    {
        kurtosisExcess = (sumFourthDifferences / (size * pow(stdDev, 4))) - 3.0;
    }
	return kurtosisExcess;

    

}