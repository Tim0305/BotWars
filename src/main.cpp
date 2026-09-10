/**
 * @file main.cpp
 * @author Team 1
 * @brief Main file that executes all the filtering and sorting methods to sort the "bitacora.txt" file
 * @date 2026-09-10
 */

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Date.h"
#include "Log.h"
#include "SortingAlgorithms.hpp"

using namespace std;

/**
 * @brief main function that sorts and filters the logs in "bitacora.txt" file
 *
 * @return int
 */
int main() {
    // Read the file
    ifstream file("bitacora.txt");
    if (!file.is_open()) {
        cerr << "Error: could not open bitacora.txt" << endl;
        return 1;
    }

    vector<Log> logs;
    string line;

    while (getline(file, line)) {
        Log log = Log::fromString(line);
        logs.push_back(log);
    }
    file.close();

    // Obtain start and end date
    string startDateStr;
    cout << "Enter the start date and time (Month Day HH:MM:SS format): ";
    getline(cin, startDateStr);

    string endDateStr;
    cout << "Enter the end date and time (Month Day HH:MM:SS format): ";
    getline(cin, endDateStr);

    Date startDate(1, Jan, 0, 0, 0, 0);
    Date endDate(1, Jan, 0, 0, 0, 0);
    try {
        startDate = Date::fromString(startDateStr);
        endDate = Date::fromString(endDateStr);
    } catch (const invalid_argument& error) {
        cerr << "Error: invalid date: " << error.what() << endl;
        return 1;
    }

    // Sort the vector
    insertionSort(logs);
    cout << endl << "Logs" << endl;

    // Create an output file
    ofstream sortedFile("bitacora_ordenada.txt");
    if (!sortedFile.is_open()) {
        cerr << "Error: could not create txt" << endl;
        return 1;
    }

    for (const Log& log : logs) {
        string logInfo = log.toString();
        Date logDate = log.getDate();
        sortedFile << logInfo << '\n';

        // Filter the logs
        if (logDate >= startDate && logDate <= endDate)
            cout << logInfo << endl;
    }

    return 0;
}