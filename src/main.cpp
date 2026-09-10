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

    // Obtain start and end date
    string startDateStr, endDateStr;

    cout << "Enter the start date and time (MMM DD YYYY HH:MM:SS format): ";
    getline(cin, startDateStr);

    cout << "Enter the end date and time (MMM DD YYYY HH:MM:SS format): ";
    getline(cin, endDateStr);

    Date start = parseDate(startDateStr);
    Date end = parseDate(endDateStr);

    cout << start.toString() << " " << end.toString();

    // Read the file
    ifstream file("bitacora.txt");
    vector<Log> logs;
    string line;

    //while (getline(file, line)) {
    //    logs.emplace_back(parseLog(line));
    //}

    // Sort the vector
    insertionSort(logs);

    // Create an output file
    ofstream sortedFile("bitacora_ordenada.txt");
}