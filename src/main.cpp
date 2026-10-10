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

void printFilteredLogsByIP4(const vector<Log>& logs, const IP4& startIp, const IP4& endIp) {}

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

            if (option < 0 || option > 3)
                cout << endl << "Invalid option. Try again" << endl;
        } while (option < 0 || option > 3);

        switch (option) {
            case 0:
                cout << "Quitting..." << endl;
                appIsRunning = false;
                break;
            case 1: {
                // Sort the vector
                char sortingOption = ' ';
                do {
                    cout << endl;
                    cout << "\t[a] By Date" << endl;
                    cout << "\t[b] By IP" << endl;
                    cout << "> ";
                    cin >> sortingOption;
                    sortingOption = tolower(sortingOption);

                    if (sortingOption < 'a' || sortingOption > 'b')
                        cout << endl << "Invalid option. Try again" << endl;
                } while (sortingOption < 'a' || sortingOption > 'b');

                switch (sortingOption) {
                    case 'a':
                        Log::setCompareMethod(CompareMethod::DATE_METHOD);
                        break;
                    case 'b':
                        Log::setCompareMethod(CompareMethod::IP_METHOD);
                        break;
                }

                cout << "Sorting..." << endl;
                mergeSort(logs);

                char saveFile = ' ';
                cout << "Save the result into a file (y/n)? ";
                cin >> saveFile;
                saveFile = tolower(saveFile);

                switch (saveFile) {
                    case 'y': {
                        string sortedFilename;
                        cout << "Filename ('bitacora_ordenada.txt'): ";
                        cin.ignore();
                        getline(cin, sortedFilename);

                        if (sortedFilename.empty())
                            sortedFilename = "bitacora_ordenada.txt";

                        // Create an output file
                        cout << "Creating file..." << endl;
                        ofstream sortedFile(sortedFilename);
                        if (sortedFile.is_open()) {
                            for (const Log& log : logs) {
                                sortedFile << log.toString() << endl;
                            }
                            sortedFile.close();
                        } else
                            cerr << "Error: could not create txt file" << endl;

                        break;
                    }
                    case 'n':
                        break;
                    default:
                        cout << endl << "Invalid option. Returning home..." << endl;
                        break;
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

                try {
                    Date startDate = Date::fromString(startDateStr);
                    Date endDate = Date::fromString(endDateStr);

                    // Filter and save the logs into a file
                    string filteredFilename = "filtered_logs_date.txt";
                    ofstream filteredFile(filteredFilename);
                    cout << "Saving filtered logs into '" << filteredFilename << "'" << endl;
                    if (filteredFile.is_open()) {
                        cout << endl;
                        for (const Log& log : logs) {
                            string logInfo = log.toString();
                            Date logDate = log.getDate();

                            if (logDate >= startDate && logDate <= endDate) {
                                cout << logInfo << endl;
                                filteredFile << logInfo << endl;
                            }
                        }
                        filteredFile.close();
                    } else
                        cerr << "Error: could not create txt file" << endl;

                } catch (const invalid_argument& error) {
                    cerr << "Error: " << error.what() << endl;
                }

                break;
            }
            case 3: {
                // Obtain start and end ip
                string startIpStr;
                cout << "Enter the start ip (192.168.1.2 format): ";
                cin.ignore();
                getline(cin, startIpStr);

                string endIpStr;
                cout << "Enter the end ip (192.168.1.2 format): ";
                getline(cin, endIpStr);

                try {
                    IP4 startIp = IP4::fromString(startIpStr);
                    IP4 endIp = IP4::fromString(endIpStr);

                    // Filter and save the logs into a file
                    string filteredFilename = "filtered_logs_ip.txt";
                    ofstream filteredFile(filteredFilename);
                    cout << "Saving filtered logs into '" << filteredFilename << "'" << endl;
                    if (filteredFile.is_open()) {
                        cout << endl;
                        for (const Log& log : logs) {
                            string logInfo = log.toString();
                            IP4 ip = log.getIp();

                            // Filter the logs
                            if (ip >= startIp && ip <= endIp) {
                                cout << logInfo << endl;
                                filteredFile << logInfo << endl;
                            }
                        }
                        filteredFile.close();
                    } else
                        cerr << "Error: could not create txt file" << endl;

                } catch (const invalid_argument& error) {
                    cerr << "Error: " << error.what() << endl;
                }
                break;
            }
        }
    }

    return 0;
}