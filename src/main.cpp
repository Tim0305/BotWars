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
    const int year = 0;
    const string months[] = {
        "", "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    ifstream file("bitacora.txt");
    vector<Log> logs;
    string line;

    while (getline(file, line)) {
        string month, time, ip, domain, message;
        int day, hour, minute, second;
        char colon;
        stringstream input(line);
        input >> month >> day >> time >> ip >> domain;
        getline(input, message);
        stringstream timeInput(time);
        timeInput >> hour >> colon >> minute >> colon >> second;

        int monthNumber = 1;
        while (months[monthNumber] != month) monthNumber++;
        logs.emplace_back(Date(day, static_cast<Month>(monthNumber), year, hour, minute, second), ip, domain, message);
    }

    insertionSort(logs);

    ofstream sortedFile("bitacora_ordenada.txt");

    int startDay, startMonth, endDay, endMonth;
    char dash;

    cout << "Enter the start date in DD-MM format: ";
    cin >> startDay >> dash >> startMonth;
    cout << "Enter the end date in DD-MM format: ";
    cin >> endDay >> dash >> endMonth;

    Date start(startDay, static_cast<Month>(startMonth), year, 0, 0, 0);
    Date end(endDay, static_cast<Month>(endMonth), year, 23, 59, 59);
}