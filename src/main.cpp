/**
 * @file main.cpp
 * @author Team 1
 * @brief Main file that executes all the filtering and sorting methods to sort the "bitacora.txt" file
 * @date 2026-10-09
 */

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Date.hpp"
#include "Log.hpp"
#include "SortingAlgorithms.hpp"

using namespace std;

void printFilteredLogsByDate(const vector<Log>& logs, const Date& startDate, const Date& endDate) {
    cout << endl;
    for (const Log& log : logs) {
        Date logDate = log.getDate();

        // Filter the logs
        if (logDate >= startDate && logDate <= endDate)
            cout << log.toString() << endl;
    }
}

void printFilteredLogsByIP4(const vector<Log>& logs, const IP4& startIp, const IP4& endIp) {
    cout << endl;
    for (const Log& log : logs) {
        IP4 ip = log.getIp();

        // Filter the logs
        if (ip >= startIp && ip <= endIp)
            cout << log.toString() << endl;
    }
}

/**
 * @brief main function that sorts and filters the logs in "bitacora.txt" file
 *
 * @return int
 */
int main() {
    bool appIsRunning = true;

    string bitacoraFilename;
    cout << "Bitacora filename ('bitacora.txt'): ";
    getline(cin, bitacoraFilename);

    if (bitacoraFilename.empty())
        bitacoraFilename = "bitacora.txt";

    // Opening file
    cout << "Opening file '" << bitacoraFilename << "'" << endl;
    ifstream file(bitacoraFilename);
    if (!file.is_open()) {
        cerr << "Error: could not open '" << bitacoraFilename << "'" << endl;
        return 1;
    }
    cout << "File opened" << endl;

    // Reading file
    cout << "Reading file '" << bitacoraFilename << "'" << endl;
    vector<Log> logs;
    string line;
    while (getline(file, line)) {
        Log log = Log::fromString(line);
        logs.push_back(log);
    }
    file.close();
    cout << "File read" << endl;

    //  Menu
    while (appIsRunning) {
        int option = 0;
        do {
            cout << endl;
            cout << "[1] Sort '" << bitacoraFilename << "'" << endl;
            cout << "[2] Search by date" << endl;
            cout << "[3] Search by ip address" << endl;
            cout << "[0] Exit" << endl;
            cout << "> ";
            cin >> option;

            if (option <= 0 && option >= 3)
                cout << endl << "Invalid option. Try again" << endl;
        } while (option <= 0 && option >= 3);

        switch (option) {
            case 0:
                cout << "Quitting..." << endl;
                appIsRunning = false;
                break;
            case 1: {
                // Sort the vector
                cout << "Sorting..." << endl;
                mergeSort(logs);
                string sortedFilename = "bitacora_ordenada.txt";
                cout << "Saving result into '" << sortedFilename << "'" << endl;

                // Create an output file
                ofstream sortedFile(sortedFilename);
                if (!sortedFile.is_open())
                    cerr << "Error: could not create txt file" << endl;

                for (const Log& log : logs) {
                    sortedFile << log.toString() << endl;
                }

                break;
            }
            case 2: {
                // Obtain start and end date
                string startDateStr;
                cout << "Enter the start date and time (Month Day HH:MM:SS format): ";
                cin.ignore();
                getline(cin, startDateStr);

                string endDateStr;
                cout << "Enter the end date and time (Month Day HH:MM:SS format): ";
                getline(cin, endDateStr);

                Date startDate;
                Date endDate;

                try {
                    startDate = Date::fromString(startDateStr);
                    endDate = Date::fromString(endDateStr);
                    printFilteredLogsByDate(logs, startDate, endDate);
                } catch (const invalid_argument& error) {
                    cerr << "Error: " << error.what() << endl;
                }

                break;
            }
            case 3: {
                // Obtain start and end ip
                string startDateStr;
                cout << "Enter the start date and time (Month Day HH:MM:SS format): ";
                getline(cin, startDateStr);

                string endDateStr;
                cout << "Enter the end date and time (Month Day HH:MM:SS format): ";
                getline(cin, endDateStr);

                Date startDate;
                Date endDate;

                try {
                    startDate = Date::fromString(startDateStr);
                    endDate = Date::fromString(endDateStr);
                    printFilteredLogsByDate(logs, startDate, endDate);
                } catch (const invalid_argument& error) {
                    cerr << "Error: " << error.what() << endl;
                }
                break;
            }
        }
    }

    return 0;
}