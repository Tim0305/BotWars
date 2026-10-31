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
#include "Splay.hpp"

using namespace std;

int showMenu();
void loadLogs(vector<Log>& logs, const string& filename);
void sortLogs(vector<Log>& logs);
char getSortingOption();
void saveLogsIntoFile();
void searchByDate(vector<Log>& logs);
void searchByIp(vector<Log>& logs);
Date getUserDate();
IP4 getUserIp4();

/**
 * @brief main function that sorts and filters the logs stored in a specified text file
 * @return int
 */
int main() {
    bool appIsRunning = true;

    // Get the filename
    string bitacoraFilename;
    cout << "Bitacora filename ('bitacora.txt'): ";
    getline(cin, bitacoraFilename);

    if (bitacoraFilename.empty())
        bitacoraFilename = "bitacora.txt";

    // Load logs
    vector<Log> logs;
    try {
        loadLogs(logs, bitacoraFilename);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    //  Menu
    while (appIsRunning) {
        int option = showMenu();
        switch (option) {
            case 0:
                cout << "Quitting..." << endl;
                appIsRunning = false;
                break;
            case 1:
                // Sort the vector
                sortLogs(logs);
                break;
            case 2: {
                // Search by date
                searchByDate(logs);
                break;
            }
            case 3: {
                // Search by ip address
                searchByIp(logs);
                break;
            }
            case 4: {
                // Monitor mode
            }
        }
    }

    return 0;
}

int showMenu() {
    int option;
    bool isValid = false;

    do {
        cout << endl;
        cout << "[1] Sort bitacora" << endl;
        cout << "[2] Search by date" << endl;
        cout << "[3] Search by ip address" << endl;
        cout << "[4] Monitor" << endl;
        cout << "[0] Exit" << endl;
        cout << "> ";
        cin >> option;

        if (option < 0 || option > 4)
            cout << endl << "Invalid option. Try again" << endl;
        else
            isValid = true;
    } while (!isValid);

    return option;
}

char getSortingOption() {
    bool isValid = false;
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
        else
            isValid = true;
    } while (!isValid);

    return sortingOption;
}

void loadLogs(vector<Log>& logs, const string& filename) {
    ifstream file(filename);

    // Opening file
    if (!file.is_open())
        throw runtime_error("Error: could not open '" + filename + "'");

    // Reading file
    string line;
    while (getline(file, line)) {
        Log log = Log::fromString(line);
        logs.push_back(log);
    }
    file.close();
}

void sortLogs(vector<Log>& logs) {
    char sortingOption = getSortingOption();

    switch (sortingOption) {
        case 'a':
            Log::setCompareMethod(CompareMethod::DATE_METHOD);
            break;
        case 'b':
            Log::setCompareMethod(CompareMethod::IP_METHOD);
            break;
    }

    mergeSort(logs);
    cout << "Sorted " << logs.size() << " elements" << endl;

    // Save the file
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
            try {
                saveLogsIntoFile(logs, sortedFilename);
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
            break;
        }
        case 'n':
            break;
        default:
            cout << endl << "Invalid option. Returning home..." << endl;
            break;
    }
}

void saveLogsIntoFile(vector<Log>& logs, const string& filename) {
    ofstream sortedFile(filename);

    if (sortedFile.is_open()) {
        for (const Log& log : logs) {
            sortedFile << log.toString() << endl;
        }
        sortedFile.close();
    } else
        throw runtime_error("Error: could not create txt file");
}

Date getUserDate() {
    string dateStr;
    cout << "Enter the date and time (Month Day HH:MM:SS format): ";
    getline(cin, dateStr);
    return Date::fromString(dateStr);
}

IP4 getUserIp4() {
    string ipStr;
    cout << "Enter the ip (192.168.1.2 format): ";
    getline(cin, ipStr);
    return IP4::fromString(ipStr);
}

void searchByDate(vector<Log>& logs) {
    try {
        // Obtain start and end date
        cout << "==== Start ====" << endl;
        cin.ignore();
        Date startDate = getUserDate();

        cout << endl << "==== End ====" << endl;
        Date endDate = getUserDate();

        // Filter and save the logs into a file
        vector<Log> filteredLogs;
        string filteredFilename = "filtered_logs_date.txt";
        int filteredLogsCounter = 0;

        for (const Log& log : logs) {
            string logInfo = log.toString();
            Date logDate = log.getDate();

            if (logDate >= startDate && logDate <= endDate) {
                cout << logInfo << endl;
                filteredLogs.push_back(log);
                filteredLogsCounter++;
            }
        }

        cout << "Filtered " << filteredLogsCounter << " elements" << endl;
        cout << "Saving filtered logs into '" << filteredFilename << "'" << endl;
        saveLogsIntoFile(filteredLogs, filteredFilename);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void searchByIp(vector<Log>& logs) {
    try {
        // Obtain start and end ip
        cout << "==== Start ====" << endl;
        cin.ignore();
        IP4 startIp = getUserIp4();

        cout << endl << "==== End ====" << endl;
        IP4 endIp = getUserIp4();

        // Filter and save the logs into a file
        vector<Log> filteredLogs;
        string filteredFilename = "filtered_logs_ip.txt";
        int filteredLogsCounter = 0;

        for (const Log& log : logs) {
            string logInfo = log.toString();
            IP4 ip = log.getIp();

            // Filter the logs
            if (ip >= startIp && ip <= endIp) {
                cout << logInfo << endl;
                filteredLogs.push_back(log);
                filteredLogsCounter++;
            }
        }

        cout << "Filtered " << filteredLogsCounter << " elements" << endl;
        cout << "Saving filtered logs into '" << filteredFilename << "'" << endl;
        saveLogsIntoFile(filteredLogs, filteredFilename);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}
