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

int main() {
    // Obtain start and end date
    string startDateStr;
    cout << "Enter the start date and time (Month Day Year HH:MM:SS format): ";
    getline(cin, startDateStr);
    Date startDate = Date::fromString(startDateStr);

    string endDateStr;
    cout << "Enter the end date and time (Month Day Year HH:MM:SS format): ";
    getline(cin, endDateStr);
    Date endDate = Date::fromString(endDateStr);

    // Read the file
    ifstream file("bitacora.txt");
    vector<Log> logs;
    string line;

    while (getline(file, line)) {
        Log log = Log::fromString(line);
        if (log.getDate() >= startDate && log.getDate() <= endDate)
            logs.push_back(log);
    }

    // Sort the vector
    insertionSort(logs);

    // Create an output file
    ofstream sortedFile("bitacora_ordenada.txt");
    if (sortedFile.is_open()) {
        for (const Log& log : logs) {
            sortedFile << log.toString() << '\n';
        }
        sortedFile.close();
    }
    return 0;
}