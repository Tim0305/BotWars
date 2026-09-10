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

inline constexpr int YEAR = 2026;

Date parseDate(const string& date) {
    string month, time;
    int year, day, hour, minutes, seconds;
    char colon = ':';

    // Split the log using spaces
    stringstream input(date);
    input >> month >> day >> year >> time;

    // Split the time using :
    stringstream timeInput(time);
    timeInput >> hour >> colon >> minutes >> colon >> seconds;

    return Date(day, stringToMonth(month), year, hour, minutes, seconds);
}

Log parseLog(const string& log) {
    string month, time, ip, domain, message;
    int day;
    stringstream input(log);
    input >> month >> day >> time >> domain;
    getline(input >> std::ws, message);

    stringstream date;
    date << month << " " << day << " " << YEAR;

    return Log(parseDate(date.str()), ip, domain, message);
}

int main() {
    const int year = 2026;

    // Obtain start and end date
    int startDay, startMonth, endDay, endMonth;
    char dash;

    cout << "Enter the start date in DD-MM format: ";
    cin >> startDay >> dash >> startMonth;
    cout << "Enter the end date in DD-MM format: ";
    cin >> endDay >> dash >> endMonth;

    Date start(startDay, static_cast<Month>(startMonth), year, 0, 0, 0);
    Date end(endDay, static_cast<Month>(endMonth), year, 23, 59, 59);

    // Read the file
    ifstream file("bitacora.txt");
    vector<Log> logs;
    string line;

    while (getline(file, line)) {
        int monthNumber = 1;
        while (months[monthNumber] != month) monthNumber++;
        logs.emplace_back(Date(day, static_cast<Month>(monthNumber), year, hour, minute, second), ip, domain, message);
    }

    // Sort the vector
    insertionSort(logs);

    // Create an output file
    ofstream sortedFile("bitacora_ordenada.txt");
}