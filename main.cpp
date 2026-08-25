//Collaborators: Hany Wasef, Aleeza Irshad, and Thanh Phan
//08-18-2026
// Description: Module 1 - The Phases of Software Development 

#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
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

    Container dataset; // Create an instance of the Container class
    cout << "\tModule 1 by Hany, Aleeza, and Thanh" << "\n\n";
    cout << "\tWhat are Descriptive Statistics?" << "\n\n";
    cout << "\tDescriptive statistics summarize certain aspects of a data set (Sample or Population)" << "\n";
    cout << "\tusing numeric calculations." << "\n\n";
    cout << "\thttps://www.calculatorsoup.com/calculators/statistics/descriptivestatistics.php." << "\n\n";

    system("pause");

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

        // Options F-Z require a non-empty dataset with at least 2 values
        if (choice >= 'F' && choice <= 'Z')
        {
            if (dataset.getSize() == 0)
            {
                cout << "\n\tException Error: Dataset is empty.\n\n\n";
                system("pause");
                continue;
            }
            else if (dataset.getSize() < 2)
            {
                cout << "\n\tException Error: Require at least 2 data values.\n\n\n";
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
                    double value = inputDouble("\n\tSpecify an integer value to be inserted to the Dataset: ");

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
                    double value = inputDouble("\n\tSpecify an integer value to find and be deleted from the Dataset: ");

                    char option = inputChar("\n\tDelete *-all elements or 1-one element found with value " + to_string(static_cast<int>(value)) + "? ", string("*1"));

                    bool deleted;
                    // Call the deleteValue function with the appropriate parameters based on the user's choice
                    if (option == '*')
                    {
                        deleted = dataset.deleteValue(value, true);
                    }
                    else
                    {
                        deleted = dataset.deleteValue(value, false);
                    }

                    if (!deleted)
                    {
                        cout << "\n\tERROR: No element " << value << " has been found and deleted.\n\n";
                    }
                    else
                    {
                        cout << "\n\tElement(s) successfully deleted.\n\n";
                    }

                    system("pause");
                    break;
                }

                case 'B':
                {
                    int start = inputInteger("\n\tSpecify a starting integer value to be deleted from the Dataset: ");

                    int end = inputInteger("\n\tSpecify an ending integer value to be deleted from the Dataset: ");

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
                    dataset.deleteAll();

                    cout << "\n\tDataset has been purged of all elements.\n\n";

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

                cout << "\n\tMinimum" << setw(30) << "= " << right << static_cast<int>(minimum) << "\n\n\n";
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

                cout << "\n\tMaximum" << setw(30) << "= " << right << static_cast<int>(maximum) << "\n\n\n";
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

                cout << "\n\tRange" << setw(30) << "= " << right << static_cast<int>(range) << "\n\n\n";
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
            cout << "\n\tSize" << setw(30) << "= " << right << dataset.getSize() << "\n\n\n";

            system("pause");
        }
        break;
        case 'E':
        {
            cout << "\n\tSum" << setw(30) << "= " << right << static_cast<int>(dataset.calculateSum()) << "\n\n\n";

            system("pause");
        }
        break;
        case 'F':
            cout << "\tFind Mean" << "\n";
            break;
        case 'G':
            break;
        case 'H':
            break;
        case 'I':
            break;
        case 'J':
        {
            try
            {
                double variance = dataset.calculateVariance();

                cout << "\n\tVariance" << setw(30) << "= " << right << fixed << setprecision(7) << variance << "\n";
            }
            catch (const char* message)
            {
                cout << message << "\n";
            }

            system("pause");
        }
        break;
        case 'K':
        {
            try
            {
                double midrange = dataset.calculateMidrange();

                cout << "\n\tMidrange" << setw(30) << "= " << right << fixed << setprecision(7) << midrange << "\n";
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

        }
        break;
        case 'M':
            break;
        case 'N':
            break;
        case 'O':
            break;
        case 'P':
            break;
        case 'Q':
            break;
        case 'R':
            break;
        case 'S':
            break;
        case 'T':
            break;
        case 'U':
            break;
        case 'V':
            break;
        case 'W':
        {
            try
            {
                double relativeStandardDeviation = dataset.calculateRelativeStandardDeviation();

                cout << "\n\tRelative Standard Deviation" << setw(30) << "= " << right << fixed << setprecision(7) << relativeStandardDeviation << "\n\n\n";
            }
            catch (const char* message)
            {
                cout << message << "\n\n\n";
            }

            system("pause");
        }
        break;
        case 'X':
        {
            try
            {
                dataset.displayFrequencyTable();
                cout << "\n\n";
            }
            catch (const char* message)
            {
                cout << message << "\n\n\n";
            }

            system("pause");
        }
        break;
        case 'Y':
        {
            try
            {
                dataset.displayAllStatistics();
                cout << "\n\n";
            }
            catch (const char* message)
            {
                cout << message << "\n\n\n";
            }

            system("pause");
        }
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
