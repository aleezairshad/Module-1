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
    const int MAX_RAND = 101; // Maximum random value (exclusive)
    for (int i = 0; i < count; ++i)
    {
        // Generate a random value between 0 and 100
        int randomInt = rand() % MAX_RAND; // Random integer between 0 and 100
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
    const int MAX_VAL = 15; // Maximum number of values per row

    for (int i = 0; i < size; ++i)
    {
        // Indent the beginning of each row
        if (i % MAX_VAL == 0)
        {
            cout << "\t";
        }

        // Display value with guaranteed separation
        cout << setw(3) << static_cast<int>(data[i]) << " ";

        // New line after every 15 values
        if ((i + 1) % MAX_VAL == 0)
        {
            cout << "\n";
        }
    }

    // New line if the final row has fewer than 15 values
    if (size % MAX_VAL != 0)
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
    const int TWO = 2; // Define a constant for the value 2
    const double TWO_FRAC = 2.0; // Define a constant for the value 2.0
    if (size == 0)
    {
        cout << "\n\tException Error: Dataset is empty.\n";
        return 0.0; // Return 0 or handle the error as appropriate
    }

    if (size % TWO == 0)
    {
        // If the size is even, return the average of the two middle values
        int midIndex = size / TWO;
        return (data[midIndex - 1] + data[midIndex]) / TWO_FRAC;
    }
    else
    {
        // If the size is odd, return the middle value
        int midIndex = size / TWO;
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

// Precondition: The dataset is not empty.
// Postcondition: Returns the coefficient of variation of the dataset. If the mean is zero, returns NAN to avoid division by zero.
// The coefficient of variation is calculated as the standard deviation divided by the mean.
double Container::calculateCoefficientOfVariation() const
{
    double mean = calculateMean();
    double stdDev = calculateStandardDeviation();
    //validate that mean is not zero to avoid division by zero
    if (mean == 0.0)
    {
        return NAN; // Return NaN (Not a Number) if mean is zero
    }
    return stdDev / mean;
}


//Aleeza's part A-E
// Precondition: The dataset is sorted in ascending order.
// Postcondition: Returns the smallest value. Throws if the dataset is empty.
double Container::calculateMinimum() const
{
	if (getSize() == 0)
	{
		throw "\n\tException Error: Dataset is empty.";
	}

	return data[0];
}

// Precondition: The dataset is sorted in ascending order.
// Postcondition: Returns the largest value. Throws if the dataset is empty.
double Container::calculateMaximum() const
{
	if (getSize() == 0)
	{
		throw "\n\tException Error: Dataset is empty.";
	}

	return data[getSize() - 1];
}

// Precondition: The dataset is sorted in ascending order.
// Postcondition: Returns maximum minus minimum. Throws if the dataset is empty.
double Container::calculateRange() const
{
	if (getSize() == 0)
	{
		throw "\n\tException Error: Dataset is empty.";
	}

	return data[getSize() - 1] - data[0];
}

// Precondition: None
// Postcondition: Returns the sum of all values. Returns 0 if the dataset is empty.
double Container::calculateSum() const
{
	double sum = 0.0;

	for (int i = 0; i < size; ++i)
	{
		sum += data[i];
	}

	return sum;
}

//Thanh's part J-R
double Container::calculateVariance() const //not yet checked for if the total item = 1, the sample formula will cause crash (can't divide by 0 because 1-1 = 0)
{
    if (getSize() == 0)
    {
        throw "\n\tException Error: Dataset is empty.";
    }

    if (getIsSample() && getSize() == 1) //Just in case the array has 1 only 1 value, the formula will divided by 0 (not good!!)
    {
        throw "\n\tException Error: Sample variance requires at least 2 values.";
    }
    bool sample = getIsSample();
    double sumOfSquaredDeviations = 0;
    double mean = 0;
    int totalItems = getSize();

    mean = calculateMean();

    for (int i = 0; i < totalItems; i++)
    {
        sumOfSquaredDeviations += pow((mean - data[i]), 2);
    }

    if (sample)
    {
        return sumOfSquaredDeviations / (totalItems - 1);
    }
    else
    {
        return sumOfSquaredDeviations / (totalItems);
    }
}

double Container::calculateMidrange() const // empty array will crash
{
    if (getSize() == 0)
    {
        throw "\n\tException Error: Dataset is empty.";
    }

    return (data[getSize() - 1] + data[0]) / 2.0;
}
void Container::calculateQuartiles(double& q1, double& q2, double& q3) const
{
    if (size == 0)
    {
        throw "\n\tException Error: Dataset is empty.";
    }


    int totalSize = getSize();

    int middleIndex = totalSize / 2;

    if (totalSize % 2 == 0)
    {
        q2 = (data[middleIndex - 1] + data[middleIndex]) / 2.0;

        int halfSize = totalSize / 2; //divide the total size in half to calculate quartile 1 and 3 (lower and upper half)

        if (halfSize % 2 == 0)
        {
            int middleIndexQ1 = halfSize / 2;

            q1 = (data[middleIndexQ1 - 1] + data[middleIndexQ1]) / 2.0;

            int middleIndexQ3 = middleIndex + middleIndexQ1;

            q3 = (data[middleIndexQ3 - 1] + data[middleIndexQ3]) / 2.0;
        }
        else
        {
            int middleIndexQ1 = halfSize / 2;

            q1 = data[middleIndexQ1];

            int middleIndexQ3 = middleIndexQ1 + middleIndex;

            q3 = data[middleIndexQ3];
        }

    }
    else
    {
        q2 = data[middleIndex];

        int halfSize = totalSize / 2;

        if (halfSize % 2 == 0)
        {
            int middleIndexQ1 = halfSize / 2;

            q1 = (data[middleIndexQ1 - 1] + data[middleIndexQ1]) / 2.0;

            int middleIndexQ3 = middleIndex + middleIndexQ1;

            q3 = (data[middleIndexQ3] + data[middleIndexQ3 + 1]) / 2.0;
        }
        else
        {
            int middleIndexQ1 = halfSize / 2;

            q1 = data[middleIndexQ1];

            int middleIndexQ3 = middleIndexQ1 + middleIndex;

            q3 = data[middleIndexQ3 + 1];
        }

    }
}
double Container::calculateInterquartileRange(double q1, double q3) const
{
    return q3 - q1;
}
void Container::calculateOutliers(double q1, double q3, double interquartileRange) const
{
    double lowerFence = q1 - (1.5 * interquartileRange);
    double upperFence = q3 + (1.5 * interquartileRange);

    for (int i = 0; i < getSize(); i++)
    {
        if (data[i] < lowerFence || data[i] > upperFence)
        {
            cout << "OutlierFound at index..." << i;
        }
    }
}
double Container::calculateSumOfSquares() const
{
    double mean = calculateMean();
    double sumOfSquares = 0.0;

    for (int i = 0; i < getSize(); i++)
    {
        sumOfSquares += pow((data[i] - mean), 2);
    }

    return sumOfSquares;
}
double Container::calculateMeanAbsoluteDeviation() const
{
    double mean = calculateMean();
    double totalDeviation = 0.0;

    for (int i = 0; i < getSize(); i++)
    {
        totalDeviation += abs(data[i] - mean);
    }

    return totalDeviation / getSize();
}
double Container::calculateRootMeanSquare() const
{
    double sumOfSquare = 0.0;

    for (int i = 0; i < getSize(); i++)
    {
        sumOfSquare += pow(data[i], 2);
    }

    double meanOfSquares = sumOfSquare / getSize();

    return sqrt(meanOfSquares);
}
double Container::calculateStandardErrorOfMean() const
{
    double stdDeviation = calculateStandardDeviation();

    double rootedSize = sqrt(getSize());

    return stdDeviation / rootedSize;
}

//Aleeza's part W-Z
// Precondition: The dataset is not empty.
// Postcondition: Returns relative standard deviation as a percent (CV * 100). Throws if empty or undefined.
double Container::calculateRelativeStandardDeviation() const
{
	if (getSize() == 0)
	{
		throw "\n\tException Error: Dataset is empty.";
	}

	double coefficientOfVariation = calculateCoefficientOfVariation();

	if (isnan(coefficientOfVariation))
	{
		throw "\n\tException Error: Relative standard deviation is undefined.";
	}

	return coefficientOfVariation * 100.0;
}

// Precondition: The dataset is sorted and not empty.
// Postcondition: Returns unique outlier values as a string, or "none" if there are no outliers.
string Container::calculateOutliersString() const
{
	double q1 = 0.0;
	double q2 = 0.0;
	double q3 = 0.0;

	calculateQuartiles(q1, q2, q3);

	double interquartileRange = calculateInterquartileRange(q1, q3);
	double lowerFence = q1 - (1.5 * interquartileRange);
	double upperFence = q3 + (1.5 * interquartileRange);

	string outliers = "";
	bool foundOutlier = false;
	bool hasLastOutlier = false;
	double lastOutlier = 0.0;

	for (int i = 0; i < size; ++i)
	{
		if (data[i] < lowerFence || data[i] > upperFence)
		{
			if (!hasLastOutlier || data[i] != lastOutlier)
			{
				if (!outliers.empty())
				{
					outliers += " ";
				}

				outliers += to_string(static_cast<int>(data[i]));
				lastOutlier = data[i];
				hasLastOutlier = true;
				foundOutlier = true;
			}
		}
	}

	if (!foundOutlier)
	{
		return "none";
	}

	return outliers;
}

// Precondition: The dataset is sorted and not empty.
// Postcondition: Writes a frequency table (value, count, percent) to out. Throws if empty.
void Container::displayFrequencyTable(ostream& out) const
{
	if (size == 0)
	{
		throw "\n\tException Error: Dataset is empty.";
	}

	out << "\n\tFrequency Table\n\n";
	out << "\tValue Frequency Frequency %\n";

	for (int i = 0; i < size;)
	{
		double value = data[i];
		int frequency = 1;

		while (i + frequency < size && data[i + frequency] == value)
		{
			++frequency;
		}

		double frequencyPercent = (static_cast<double>(frequency) / size) * 100.0;

		out << "\t" << setw(5) << right << static_cast<int>(value)
			<< setw(10) << right << frequency
			<< setw(12) << right << fixed << setprecision(2) << frequencyPercent << "\n";

		i += frequency;
	}
}

// Precondition: The dataset is not empty.
// Postcondition: Writes all statistical results and the frequency table to out. Throws if empty.
void Container::displayAllStatistics(ostream& out) const
{
	if (size == 0)
	{
		throw "\n\tException Error: Dataset is empty.";
	}

	double q1 = 0.0;
	double q2 = 0.0;
	double q3 = 0.0;

	calculateQuartiles(q1, q2, q3);

	double interquartileRange = calculateInterquartileRange(q1, q3);
	string modes = calculateMode();

	if (!modes.empty() && modes[0] == ' ')
	{
		modes = modes.substr(1);
	}

	out << "\n";
	out << "\t" << left << setw(28) << "Minimum" << "= " << right << static_cast<int>(data[0]) << "\n";
	out << "\t" << left << setw(28) << "Maximum" << "= " << right << static_cast<int>(data[size - 1]) << "\n";
	out << "\t" << left << setw(28) << "Range" << "= " << right << static_cast<int>(data[size - 1] - data[0]) << "\n";
	out << "\t" << left << setw(28) << "Size" << "= " << right << size << "\n";
	out << "\t" << left << setw(28) << "Sum" << "= " << right << static_cast<int>(calculateSum()) << "\n";
	out << "\t" << left << setw(28) << "Mean" << "= " << right << fixed << setprecision(2) << calculateMean() << "\n";
	out << "\t" << left << setw(28) << "Median" << "= " << right << fixed << setprecision(2) << calculateMedian() << "\n";
	out << "\t" << left << setw(28) << "Mode(s)" << "= " << modes << "\n";
	out << "\t" << left << setw(28) << "Standard Deviation" << "= " << right << fixed << setprecision(7) << calculateStandardDeviation() << "\n";
	out << "\t" << left << setw(28) << "Variance" << "= " << right << fixed << setprecision(7) << calculateVariance() << "\n";
	out << "\t" << left << setw(28) << "Midrange" << "= " << right << fixed << setprecision(7) << calculateMidrange() << "\n";
	out << "\t" << left << setw(28) << "Quartiles" << "Quartiles:\n";
	out << "\t" << setw(28) << " " << "Q1 --> " << right << fixed << setprecision(1) << q1 << "\n";
	out << "\t" << setw(28) << " " << "Q2 --> " << right << fixed << setprecision(1) << q2 << "\n";
	out << "\t" << setw(28) << " " << "Q3 --> " << right << fixed << setprecision(1) << q3 << "\n";
	out << "\t" << left << setw(28) << "Interquartile Range" << "= " << right << fixed << setprecision(1) << interquartileRange << "\n";
	out << "\t" << left << setw(28) << "Outliers" << "= " << calculateOutliersString() << "\n";
	out << "\t" << left << setw(28) << "Sum of Squares" << "= " << right << fixed << setprecision(2) << calculateSumOfSquares() << "\n";
	out << "\t" << left << setw(28) << "Mean Absolute Deviation" << "= " << right << fixed << setprecision(2) << calculateMeanAbsoluteDeviation() << "\n";
	out << "\t" << left << setw(28) << "Root Mean Square" << "= " << right << fixed << setprecision(7) << calculateRootMeanSquare() << "\n";
	out << "\t" << left << setw(28) << "Standard Error of the Mean" << "= " << right << fixed << setprecision(7) << calculateStandardErrorOfMean() << "\n";
	out << "\t" << left << setw(28) << "Skewness" << "= " << right << fixed << setprecision(7) << calculateSkewness() << "\n";
	out << "\t" << left << setw(28) << "Kurtosis" << "= " << right << fixed << setprecision(7) << calculateKurtosis() << "\n";
	out << "\t" << left << setw(28) << "Kurtosis Excess" << "= " << right << fixed << setprecision(7) << calculateKurtosisExcess() << "\n";
	out << "\t" << left << setw(28) << "Coefficient of Variation" << "= " << right << fixed << setprecision(7) << calculateCoefficientOfVariation() << "\n";
	out << "\t" << left << setw(28) << "Relative Standard Deviation" << "= " << right << fixed << setprecision(7) << calculateRelativeStandardDeviation() << "\n";

	displayFrequencyTable(out);
}

// Precondition: filename is a valid text file name. The dataset is not empty.
// Postcondition: Writes all statistical results to the file. Returns true if the file was created.
bool Container::outputAllStatisticsToFile(const string& filename) const
{
	ofstream outputFile(filename);

	if (!outputFile)
	{
		return false;
	}

	displayAllStatistics(outputFile);
	outputFile.close();

	return true;
}
