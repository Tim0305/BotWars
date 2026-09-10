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

constexpr int YEAR = 2026;

Date parseDate(const string& date) {
    string month, time;
    int year = 0, day = 0, hour = 0, minutes = 0, seconds = 0;
    char colon = ':';

    // Split the date using spaces
    stringstream input(date);
    input >> month >> day >> year >> time;

    // Split the time using :
    stringstream timeInput(time);
    timeInput >> hour >> colon >> minutes >> colon >> seconds;

    return Date(day, stringToMonth(month), year, hour, minutes, seconds);
}

Log parseLog(const string& log) {
    string month, time, ip, domain, message;
    int day = 0;

    // Split each part using spaces
    stringstream input(log);
    input >> month >> day >> time >> domain;
    getline(input >> std::ws, message);

    // Transform the date using the format Month Day Year HH:MM:SS
    stringstream date;
    date << month << " " << day << " " << YEAR;

    return Log(parseDate(date.str()), ip, domain, message);
}

int main() {
    // Obtain start and end date
    string startDateStr;
    cout << "Enter the start date and time (Month Day Year HH:MM:SS format): ";
    getline(cin, startDateStr);
    Date startDate = parseDate(startDateStr);

    string endDateStr;
    cout << "Enter the end date and time (Month Day Year HH:MM:SS format): ";
    getline(cin, endDateStr);
    Date endDate = parseDate(endDateStr);

    // Read the file
    ifstream file("bitacora.txt");
    vector<Log> logs;
    string line;

    // while (getline(file, line)) {
    //     logs.emplace_back(parseLog(line));
    // }

    // Sort the vector
    insertionSort(logs);

    // Create an output file
    ofstream sortedFile("bitacora_ordenada.txt");
}