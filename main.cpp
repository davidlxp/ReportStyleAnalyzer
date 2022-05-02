/*********************************************************************/
/* Programmer: Xinpeng Liu                                           */
/* Date: March 28, 2022                                              */
/* Purpose: Section for testing the ReportAnalyzer program           */
/*********************************************************************/


#include <iostream>
#include <vector>
#include "ReportAnalyzer.h"

int printMenu();
void runProgram();
string readInputAddress();
string readOutputAddress();

int main()
{
    cout << "\nWelcome to the File Analyzer!";
    cout << "\nIf you provide me a text file, I could provide you feedback and style warning." << endl;
    cout << "\n";

    string inputAddress = readInputAddress();
    string outputAddress = readOutputAddress();

    inputAddress = "../" + inputAddress;
    outputAddress = "../" + outputAddress;

    ReportAnalyzer A;
    A.analyzeReport(inputAddress, outputAddress);
    cout << "Please see '" << outputAddress << "' for analysis result " << endl;

    return 0;
}

string readInputAddress()
{
    cout << "Please Provide Input File Path (eg. sample2.txt): ";
    string inputFileAddress;
    getline(cin, inputFileAddress);

    return inputFileAddress;
}

string readOutputAddress()
{
    cout << "Please Provide File Path For Storing Analysis Result (eg. analysis.txt): ";
    string outputFileAddress;
    getline(cin, outputFileAddress);

    return outputFileAddress;
}