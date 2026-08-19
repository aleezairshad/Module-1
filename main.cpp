// Name: Hany, Aleeza, and Tuniphn
// Description: Modul1 - The Phases of Software Development 

#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include "input.h"

using namespace std;

// Function Prototypes
char menuOption();
char menuOption1();
char menuOption2();
char menuOption3();


int main()
{
	double* dataset = nullptr; // Pointer to the dataset (dynamic array)
	int datasetSize = 0; // Size of the dataset

	bool isSample = true; // Flag to indicate if the dataset is a sample or population

    cout << "\tWhat are Descriptive Statistics?" << "\n\n";
    cout << "\tDescriptive statistics summarize certain aspects of a data set (Sample or Population)" << "\n";
    cout << "\tusing numeric calculations." << "\n\n";
    cout << "\thttps://www.calculatorsoup.com/calculators/statistics/descriptivestatistics.php." << "\n\n";

    system("pause");

    bool running = true;
    while (running)
    {
		system("cls"); // Clear the console screen (Windows-specific)

		cout << "\n\tAddress of Dynamic array: " << static_cast<void*>(dataset) << "\n";

        cout << "\tDataset: (" << (isSample ? "Sample" : "Population") << ")\n\n";

        if (datasetSize < 2)
        {
            cout << "\tERROR: Data Set requires at least 2 values.\n\n";
        }
        else
            {
            cout << "\tDataset Size: " << datasetSize << "\n";
            cout << "\tDataset Values: ";
            for (int i = 0; i < datasetSize; ++i)
            {
                cout << dataset[i] << " ";
            }
            cout << "\n\n";
		}
    

        char choice = menuOption();

		if (choice >= 'A' && choice <= 'Z') // Check if the choice is a letter
		{
            if (datasetSize == 0)
            {
                cout << "\n\tException Error: Dataset is empty.\n\n";
                system("pause");
                continue; // Skip the rest of the loop and go back to the menu
            }
            else if (datasetSize < 2)
            {
                cout << "\n\tException Error: Require at least 2 data values.\n\n";
                system("pause");
                continue; // Skip the rest of the loop and go back to the menu
			}
		}

        switch (choice)
        {
        case '0':
			//return EXIT_SUCCESS; // Exit the program
			running = false; // Set running to false to exit the loop

            break;
        case '1':
        {
            char configChoice = menuOption1();
            switch (configChoice)
            {
            case 'A':
                isSample = true;
                cout << "\n\tDataset configured as Sample.\n\n";
                system("pause");
                break;
            case 'B':
                isSample = false;
                cout << "\n\tDataset configured as Population.\n\n";
                system("pause");
                break;
            case 'R':
				cout << "\n\tNo change to Dataset.\n\n";
                system("pause");
                break;

            }
        }

            
            break;
        case '2':
            {
                char insertChoice = menuOption2();
                switch (insertChoice)
                {
				case 'A':
                    break;
				case 'B':
                    break;
				case 'C':
                    break;
				case 'R':
                    cout << "\n\n";
					system("pause");
                    break;
                }
		}
            
            break;
        case '3':
            {
                char deleteChoice = menuOption3();
                switch (deleteChoice)
				{
                    case 'A':
						break;
					case 'B':
                        break;
					case 'C':
                        break;
					case 'R':
						cout << "\n\n";
                        system("pause");
                        break;
                }
		}
            

            break;
        case 'A':
            
            break;
        case 'B':
   
            break;
        case 'C':

            break;
        case 'D':

            break;
        case 'E':
            cout << "\tFind Sum" << "\n";
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
			break;
		case 'K':
			break;
		case 'L':
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
			break;
		case 'X':
			break;
		case 'Y':
			break;
		case 'Z':
			break;
        default:
            cout << "\tInvalid option. Please try again." << "\n";
        }
    }

	delete[] dataset; // Free the dynamically allocated memory for the dataset
    

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
    return inputChar("\n\tOption: ", string("ABR"));
}


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

