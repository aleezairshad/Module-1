// Name: Hany, Aleeza, and Tuniphn
// Date: 08-18-2026
// Description: Modul1 - The Phases of Software Development

#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include "input.h"
#include "Container.h"

using namespace std;

// Function Prototypes
char menuOption();
char menuOption1();
char menuOption2();
char menuOption3();


int main()
{
    srand(time(0));

    Container dataset; // Create an instance of the Container class
    srand(static_cast<unsigned int>(time(nullptr)));
    cout << "\tModul 1 by Hany, Aleeza, and Tuniphn" << "\n\n";
    cout << "\tWhat are Descriptive Statistics?" << "\n\n";
    cout << "\tDescriptive statistics summarize certain aspects of a data set (Sample or Population)" << "\n";
    cout << "\tusing numeric calculations." << "\n\n";
    cout << "\thttps://www.calculatorsoup.com/calculators/statistics/descriptivestatistics.php." << "\n\n";

    system("pause");

    double q1 = 0;
    double q2 = 0;
    double q3 = 0;
    double iqr = 0;

    bool running = true;
    while (running)
    {
        system("cls"); // Clear the console screen 

        cout << "\n\tAddress of Dynamic array: " << static_cast<void*>(dataset.getData()) << "\n";

        cout << "\tDataset: (" << (dataset.getIsSample() ? "Sample" : "Population") << ")\n\n";

        // Display the dataset values if there are at least 2 values
        if (dataset.getSize() < 2)
        {
            cout << "\tERROR: Data Set requires at least 2 values.\n\n";
        }
        else
        {
            dataset.display(); // Display the dataset values
            cout << "\n";

        }


        char choice = menuOption(); // Get the user's menu option selection

        // Check if the choice is an uppercase letter (A-Z) and if the dataset has at least 2 values
        if (choice >= 'A' && choice <= 'Z')
        {
            if (dataset.getSize() == 0)
            {
                cout << "\n\tException Error: Dataset is empty.\n\n";
                system("pause");
                continue;
            }
            else if (dataset.getSize() < 2)
            {
                cout << "\n\tException Error: Require at least 2 data values.\n\n";
                system("pause");
                continue;
            }
        }

        // Handle the user's menu option selection
        switch (choice)
        {
        case '0':
            running = false; // Set running to false to exit the loop

            break;
        case '1':
        {
            char configChoice = menuOption1(); // Get the user's configuration option selection
            switch (configChoice)
            {
            case 'A':
                dataset.setIsSample(true); // Set the dataset to be a sample
                cout << "\n\tDataset configured as Sample.\n\n";
                system("pause");
                break;
            case 'B':
                dataset.setIsSample(false); // Set the dataset to be a population
                cout << "\n\tDataset configured as Population.\n\n";
                system("pause");
                break;
            case 'R':
                cout << "\n\tNo change to Dataset.\n\n";
                system("pause");
                break;

            }
            break;
        }

        case '2':
        {
            bool insertMenuRunning = true; // Flag to control the insert menu loop
            // Loop until the user chooses to return from the insert menu
            while (insertMenuRunning)
            {
                char insertChoice = menuOption2();

                switch (insertChoice)
                {
                case 'A':
                {
                    int value = inputInteger("\n\tSpecify a value to be inserted to the Dataset: ");

                    dataset.insertValue(value); // Insert the specified value into the dataset

                    cout << "\n\t" << value << " has been inserted...\n\n";

                    system("pause");
                    break;
                }

                case 'B':
                {
                    int count = inputInteger("\n\tSpecify a number of values to be randomly generated into the Dataset: ", true);

                    dataset.insertRandomValues(count);  // Insert the specified number of random values into the dataset

                    cout << "\n\tCONFIRMATION: Inserted " << count << " random values into the Dataset.\n\n";
                    system("pause");
                    break;
                }

                case 'C':
                {
                    string filename = inputString("\n\tSpecify a data text file name to read: ", false);

                    int count = dataset.readFromFile(filename); // Read values from the specified file and insert them into the dataset

                    if (count > 0)
                    {
                        cout << "\n\tCONFIRMATION: " << count << " element(s) have been read and inserted to the Dataset.\n\n";
                    }

                    system("pause");
                    break;
                }

                case 'R':
                    insertMenuRunning = false;
                    cout << "\n\n";
                    system("pause");
                    break;
                }
            }

            break;
        }

        case '3':
        {
            bool deleteMenuRunning = true;

            while (deleteMenuRunning)
            {
                char deleteChoice = menuOption3(); // Get the user's delete menu option selection

                switch (deleteChoice)
                {
                case 'A':
                {
                    int value = inputInteger("\n\tSpecify a value to find and be deleted from the Dataset: ");

                    ostringstream valueText;
                    valueText << fixed << setprecision(2) << value;

                    char option = inputChar("\n\tDelete *-all elements or 1-one element found with value " + valueText.str() + "? ", string("*1"));

                    int deletedCount;
                    // Call the deleteValue function with the appropriate parameters based on the user's choice
                    if (option == '*')
                    {
                        deletedCount = dataset.deleteValue(value, true);
                    }
                    else
                    {
                        deletedCount = dataset.deleteValue(value, false);
                    }

                    if (deletedCount == 0)
                    {
                        cout << "\n\tERROR: No element " << value << " has been found and deleted.\n\n";
                    }
                    else
                    {
                        cout << "\n\t" << deletedCount << " element(s) successfully deleted.\n\n";
                    }

                    system("pause");
                    break;
                }

                case 'B':
                {
                    int start = inputInteger("\n\tSpecify a starting integer value to be deleted from the Dataset: ");

                    int end = inputInteger("\n\tSpecify an ending integer value to be deleted from the Dataset: ", start, true);

                    bool deleted = dataset.deleteRange(start, end);  // Call the deleteRange function to delete values within the specified range

                    if (!deleted)
                    {
                        cout << "\n\tERROR: No element in range (" << start << ".." << end << ") has been found and deleted.\n\n";
                    }

                    system("pause");
                    break;
                }

                case 'C':
                {
                    int purgedCount = dataset.deleteAll();

                    cout << "\n\t" << purgedCount << " element(s) successfully deleted. Dataset has been purged of all elements.\n\n";

                    system("pause");
                    break;
                }

                case 'R':
                    deleteMenuRunning = false;
                    cout << "\n\n";

                    system("pause");
                    break;
                }
            }

            break;
        }


        case 'A':
        {
            try
            {
                double minimum = dataset.calculateMinimum();

                cout << "\n\t" << left << setw(28) << "Minimum" << "= " << right << fixed << setprecision(2) << minimum << "\n\n\n";
            }
            catch (const char* message)
            {
                cout << message << "\n\n\n";
            }

            system("pause");
        }

        break;
        case 'B':
        {
            try
            {
                double maximum = dataset.calculateMaximum();
                cout << "\n\t" << left << setw(28) << "Maximum" << "= " << right << fixed << setprecision(2) << maximum << "\n\n\n";
            }
            catch (const char* message)
            {
                cout << message << "\n\n\n";
            }
            system("pause");
        }

        break;
        case 'C':
        {
            try
            {
                double range = dataset.calculateRange();
                cout << "\n\t" << left << setw(28) << "Range" << "= " << right << fixed << setprecision(2) << range << "\n\n\n";
            }
            catch (const char* message)
            {
                cout << message << "\n\n\n";
            }
            system("pause");
        }

        break;
        case 'D':
        {
            cout << "\n\t" << left << setw(28) << "Size" << "= " << right << dataset.getSize() << "\n\n\n";

            system("pause");
            break;
        }

        break;
        case 'E':
        {
            double sumValue = dataset.calculateSum(); // Calculate the sum of the dataset
            cout << "\n\tSum " << setw(25) << "= " << fixed << setprecision(2) << sumValue << "\n\n";
            system("pause");
        }

        break;
        case 'F':
        {

            double meanValue = dataset.calculateMean(); // Calculate the mean of the dataset

            cout << "\n\tMean " << fixed << setprecision(2) << setw(25) << "= " << meanValue << "\n\n";
            system("pause");

            break;
        }
        case 'G':
        {
            double medianValue = dataset.calculateMedian(); // Calculate the median of the dataset
            cout << "\n\tMedian " << fixed << setprecision(2) << setw(23) << "= " << medianValue << "\n\n";
            system("pause");

            break;
        }
        case 'H':
        {
            string modeValue = dataset.calculateMode(); // Calculate the mode of the dataset
            cout << "\n\tMode " << setw(25) << "= " << modeValue << "\n\n";

            system("pause");

            break;
        }
        case 'I':
        {
            // Calculate the standard deviation of the dataset
            cout << "\n\tStandard Deviation " << setw(12) << "= " << fixed << setprecision(2) << dataset.calculateStandardDeviation() << "\n\n";
            system("pause");

            break;
        }
        case 'J':
        {
            try
            {
                double variance = dataset.calculateVariance();

                cout << "\n\tVariance" << setw(30) << "= " << right << fixed << setprecision(2) << variance << "\n\n";
            }
            catch (const char* message)
            {
                cout << message << "\n";
            }

            system("pause");

            break;
        }
        case 'K':
        {
            try
            {
                double midrange = dataset.calculateMidrange();

                cout << "\n\tMidrange" << setw(30) << "= " << right << fixed << setprecision(2) << midrange << "\n\n";
            }
            catch (const char* message)
            {
                cout << message << "\n";
            }

            system("pause");
        }
        break;
        case 'L':
        {
            dataset.calculateQuartiles(q1, q2, q3);

            cout << fixed << setprecision(2);

            if (dataset.getSize() <= 3)
            {
                cout << "\n\tQuartiles" << setw(30) << right << "Quartiles:";
                cout << "\n\t" << setw(36) << right << "Q1 --> " << "unknown";
                cout << "\n\t" << setw(36) << right << "Q2 --> " << q2;
                cout << "\n\t" << setw(36) << right << "Q3 --> " << "unknown\n";
            }
            else
            {
                cout << "\n\tQuartiles" << setw(30) << right << "Quartiles:";
                cout << "\n\t" << setw(36) << right << "Q1 --> " << q1;
                cout << "\n\t" << setw(36) << right << "Q2 --> " << q2;
                cout << "\n\t" << setw(36) << right << "Q3 --> " << q3 << "\n";
            }

            system("pause");
            break;
        }
        case 'M':
        {
            if (dataset.getSize() < 4)
            {
                cout << "\n\tInterquartile Range" << setw(30) << "= " << right << "unknown\n\n";
            }
            else
            {
                dataset.calculateQuartiles(q1, q2, q3); // prevent data change affect the calculation (so I recalculate)

                iqr = dataset.calculateInterquartileRange(q1, q3);
                cout << "\n\tInterquartile Range" << setw(30) << "= " << right << fixed << setprecision(2) << iqr << "\n\n";
            }
            system("pause");
        }
        break;
        case 'N':
        {
            string outliers = dataset.calculateOutliersString();
            cout << "\n\tOutliers" << setw(30) << "= " << outliers << "\n\n";
            system("pause");
        }
        break;
        case 'O':
        {
            double sumOfSquares = dataset.calculateSumOfSquares();
            cout << "\n\tSum of Squares" << setw(30) << "= " << right << fixed << setprecision(2) << sumOfSquares << "\n\n";
            system("pause");
        }
        break;
        case 'P':
        {
            double meanAbsDeviation = dataset.calculateMeanAbsoluteDeviation();
            cout << "\n\tMean Absolute Deviation" << setw(30) << "= " << right << fixed << setprecision(2) << meanAbsDeviation << "\n\n";
            system("pause");
        }
        break;
        case 'Q':
        {
            double rootMeanSquare = dataset.calculateRootMeanSquare();
            cout << "\n\tRoot Mean Square" << setw(30) << "= " << right << fixed << setprecision(2) << rootMeanSquare << "\n\n";
            system("pause");
        }
        break;
        case 'R':
        {
            double stdErrorOfMean = dataset.calculateStandardErrorOfMean();
            cout << "\n\tStandard Error of the Mean" << setw(4) << "= " << right << fixed << setprecision(2) << stdErrorOfMean << "\n\n";
            system("pause");
        }
        break;
        case 'S':
        {
            double skewnessValue = dataset.calculateSkewness(); // Calculate the skewness of the dataset
            cout << "\n\tSkewness " << setw(21) << "= ";
            if (isnan(skewnessValue))
            {
                cout << "unknown\n\n";
            }
            else
            {
                cout << fixed << setprecision(2) << skewnessValue << "\n\n";
            }

            system("pause");
            break;
        }
        case 'T':
        {
            double kurtosisValue = dataset.calculateKurtosis(); // Calculate the kurtosis of the dataset
            cout << "\n\tKurtosis " << setw(22) << "= ";
            if (isnan(kurtosisValue))
            {
                cout << "unknown\n\n";
            }
            else
            {
                cout << fixed << setprecision(2) << kurtosisValue << "\n\n";
            }
            system("pause");
            break;
        }
        case 'U':
        {
            double kurtosisExcessValue = dataset.calculateKurtosisExcess(); // Calculate the kurtosis excess of the dataset
            cout << "\n\tKurtosis Excess " << setw(15) << "= ";
            if (isnan(kurtosisExcessValue))
            {
                cout << "unknown\n\n";
            }
            else
            {
                cout << fixed << setprecision(2) << kurtosisExcessValue << "\n\n";
            }
            system("pause");
            break;
        }
        case 'V':
        {
            double coeffVariation = dataset.calculateCoefficientOfVariation(); // Calculate the coefficient of variation of the dataset
            cout << "\n\tCoefficient of Variation " << setw(7) << "= ";
            if (isnan(coeffVariation))
            {
                cout << "unknown\n\n";
            }
            else
            {
                cout << fixed << setprecision(2) << coeffVariation << "\n\n";
            }
            system("pause");
            break;
        }
        case 'W':
        {
            try
            {
                double relativeStandardDeviation = dataset.calculateRelativeStandardDeviation();

                cout << "\n\t" << left << setw(28) << "Relative Standard Deviation" << "= " << right << fixed << setprecision(2) << relativeStandardDeviation << "\n\n\n";
            }
            catch (const char* message)
            {
                cout << message << "\n\n\n";
            }

            system("pause");
        }
        break;

        case 'X':
            dataset.displayFrequencyTable(); // Display the frequency table of the dataset
            system("pause");
            break;

        case 'Y':
            dataset.displayAllStatistics(); // Display all statistics of the dataset
            cout << "\n\n";
            system("pause");
            break;
        case 'Z':
        {
            string filename = inputString("\n\tSpecify a text file to save results: ", false);

            if (dataset.outputAllStatisticsToFile(filename))
            {
                cout << "\n\tCONFIRMATION: File, " << filename << ", has been generated.\n\n\n";
            }
            else
            {
                cout << "\n\tERROR: File, " << filename << ", could not be generated.\n\n\n";
            }

            system("pause");
        }
        break;
        default:
            cout << "\tInvalid option. Please try again." << "\n";
        }
    }

    return EXIT_SUCCESS;
}


//Precondition: None
//Postcondition: Returns a char value representing the user's menu option selection
char menuOption()
{
    cout << "\tDescriptive Statistics Calculator Main Menu\n";

    cout << "\t" << string(80, char(205));
    cout << "\n\t 0. Exit\n";
    cout << "\t 1. Configure Dataset to Sample or Population\n";
    cout << "\t 2. Insert sort value(s) to the Dataset\n";
    cout << "\t 3. Delete value(s) from the Dataset\n";

    cout << "\t" << string(80, char(196));

    cout << "\n\t A. Find Minimum" << setw(36) << "N. Find Outliers\n";
    cout << "\t B. Find Maximum " << setw(41) << "O. Find Sum of Squares\n";
    cout << "\t C. Find Range" << setw(53) << "P. Find Mean Absolute Deviation\n";
    cout << "\t D. Find Size" << setw(47) << "Q. Find Root Mean Square\n";
    cout << "\t E. Find Sum" << setw(54) << "R. Find Standard Error of Mean\n";
    cout << "\t F. Find Mean" << setw(39) << "S. Find Skewness\n";
    cout << "\t G. Find Median" << setw(37) << "T. Find Kurtosis\n";
    cout << "\t H. Find Mode(s)" << setw(43) << "U. Find Kurtosis Excess\n";
    cout << "\t I. Find Standard Deviation" << setw(41) << "V. Find Coefficient of Variation\n";
    cout << "\t J. Find Variance" << setw(54) << "W. Find Relative Standard Deviation\n";
    cout << "\t K. Find Midrange" << setw(45) << "X. Display Frequency Table\n";
    cout << "\t L. Find Quartiles" << setw(52) << "Y. Display ALL statistical results\n";
    cout << "\t M. Find Interquartile Range" << setw(54) << "Z. Output ALL statistical results to text file\n";

    cout << "\t" << string(80, char(205)) << "\n";

    char option = toupper(inputChar("\n\tOption: ", static_cast<string>("0123ABCDEFGHIJKLMNOPQRSTUVWXYZ")));

    return option;
}

//Precondition: None
//Postcondition: Returns a char value representing the user's menu option selection
char menuOption1()
{
    system("cls"); // Clear the console screen (Windows-specific)
    cout << "\tIn statistics, Population refers to the entire group of data\n";
    cout << "\tpoints that a study is interested in, while a Sample is a\n";
    cout << "\tsubset of that population that is actually used in the study.\n\n";

    cout << "\tConfigure Dataset Menu\n";
    cout << "\t" << string(80, char(205));
    cout << "\n\t\t A. sample\n";
    cout << "\t\t B. population\n";
    cout << "\t" << string(80, char(196));
    cout << "\n\t\t R. return\n";
    cout << "\t" << string(80, char(205)) << "\n";

    return inputChar("\n\tOption: ", string("ABR"));
}

//Precondition: None
//Postcondition: Returns a char value representing the user's menu option selection
char menuOption2()
{
    system("cls"); // Clear the console screen (Windows-specific)
    cout << "\tInsert (sort) Dataset Menu\n";
    cout << "\t" << string(80, char(205));
    cout << "\n\t\t A. insert a value\n";
    cout << "\t\t B. insert a specified number of random values\n";
    cout << "\t\t C. read data from file and insert values\n";
    cout << "\t" << string(80, char(196));
    cout << "\n\t\t R. return\n";
    cout << "\t" << string(80, char(205)) << "\n";
    return inputChar("\n\tOption: ", string("ABCR"));
}

//Precondition: None
//Postcondition: Returns a char value representing the user's menu option selection
char menuOption3()
{
    system("cls"); // Clear the console screen (Windows-specific)
    cout << "\tDelete Dataset Menu\n";
    cout << "\t" << string(80, char(205));
    cout << "\n\t\t A. delete a value\n";
    cout << "\t\t B. delete a range of values\n";
    cout << "\t\t C. delete all values\n";
    cout << "\t" << string(80, char(196));
    cout << "\n\t\t R. return\n";
    cout << "\t" << string(80, char(205)) << "\n";
    return inputChar("\n\tOption: ", string("ABCR"));
}



