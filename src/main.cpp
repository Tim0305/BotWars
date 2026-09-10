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
    const int year = 2026;

    // Obtain start and end date
    int startDay, startMonth, startHour, startMinute, startSecond;
    int endDay, endMonth, endHour, endMinute, endSecond;
    char dash, colon;

    cout << "Enter the start date and time in DD-MM HH:MM:SS format: ";
    cin >> startDay >> dash >> startMonth >> startHour >> colon >> startMinute >> colon >> startSecond;
    cout << "Enter the end date and time in DD-MM HH:MM:SS format: ";
    cin >> endDay >> dash >> endMonth >> endHour >> colon >> endMinute >> colon >> endSecond;

    Date start(startDay, static_cast<Month>(startMonth), year, startHour, startMinute, startSecond);
    Date end(endDay, static_cast<Month>(endMonth), year, endHour, endMinute, endSecond);

    // Read the file
    ifstream file("bitacora.txt");
    vector<Log> logs;
    string line;

    while (getline(file, line)) {
        string month, time, ip, domain, message;
        int day, hour, minute, second;
        char colon = ':';

        // Split the log using spaces
        stringstream input(line);
        input >> month >> day >> time >> ip >> domain;

        // Split the time using :
        stringstream timeInput(time);
        timeInput >> hour >> colon >> minute >> colon >> second;

        int monthNumber = 1;
        while (months[monthNumber] != month) monthNumber++;
        logs.emplace_back(Date(day, static_cast<Month>(monthNumber), year, hour, minute, second), ip, domain, message);
    }

    insertionSort(logs);

    ofstream sortedFile("bitacora_ordenada.txt");
}