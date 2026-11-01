/**
 * @file main.cpp
 * @author Team 1
 * @brief Main file that sorts logs, searches ranges and runs the IP monitor and its tests.
 * @date 2026-10-30
 */

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "Date.hpp"
#include "IPRecord.hpp"
#include "Log.hpp"
#include "Monitor.hpp"
#include "SortingAlgorithms.hpp"
#include "Splay.hpp"

using namespace std;
using namespace std::chrono;

/**
 * @brief Shows the main menu and reads the selected option.
 * @return int An option between 0 and 5.
 */
int showMenu();

/**
 * @brief Reads a file and adds its logs to the vector.
 * @param logs Vector where the logs are added.
 * @param filename Name of the file to read.
 * @post Keeps the logs in the same order as the file.
 * @throws std::runtime_error If the file cannot be opened.
 * @throws std::invalid_argument If a log contains invalid values.
 * @throws std::out_of_range If a port number is too large for an int.
 */
void loadLogs(vector<Log>& logs, const string& filename);

/**
 * @brief Sorts the logs by date or IP and asks whether to save them.
 * @param logs Vector of logs to sort.
 * @post The vector is sorted in ascending order using the selected field.
 * The selected field is also used for later Log comparisons.
 */
void sortLogs(vector<Log>& logs);

/**
 * @brief Asks the user how to sort the logs.
 * @return char 'a' to sort by date or 'b' to sort by IP.
 */
char getSortingOption();

/**
 * @brief Saves the logs into a text file, one log per line.
 * @param logs Vector of logs to save; it is not changed.
 * @param filename Name of the output file.
 * @post Replaces any previous contents of the file.
 * @throws std::runtime_error If the file cannot be created.
 */
void saveLogsIntoFile(vector<Log>& logs, const string& filename);

/**
 * @brief Finds logs between two dates entered by the user, including both dates.
 * @param logs Vector of logs to search; it is not changed.
 * @post Prints the results and saves them in filtered_logs_date.txt.
 * The logs do not need to be sorted. Any previous file contents are replaced.
 */
void searchByDate(vector<Log>& logs);

/**
 * @brief Finds logs between two IP addresses, including both addresses.
 * @param logs Vector of logs to search; it is not changed.
 * @post Prints the results and saves them in filtered_logs_ip.txt.
 * The logs do not need to be sorted. Any previous file contents are replaced.
 */
void searchByIp(vector<Log>& logs);

/**
 * @brief Asks the user for a date in Month Day HH:MM:SS format.
 * @return Date The date entered by the user.
 * @throws std::invalid_argument If the date values are invalid.
 */
Date getUserDate();

/**
 * @brief Asks the user for an IP address in a.b.c.d format.
 * @return IP4 The address entered by the user.
 * @throws std::invalid_argument If the address is invalid.
 */
IP4 getUserIp4();

/**
 * @brief Counts accesses by IP and shows reports and IP range searches.
 * @param logs Vector of logs to read.
 * @pre The vector must not be empty and must be sorted by date.
 * @post Prints the reports and replaces the contents of output.txt.
 * @details Reports include all accesses read so far, including earlier months.
 * An access is successful when the first word of its message is "Accepted".
 * The final block search uses the block of the most accessed IP.
 */
void monitor(const vector<Log>& logs);

/**
 * @brief Prints the report with all accesses read so far and writes it to the output file.
 * @param splayTree Tree with all IP records read so far.
 * @param month Month shown in the report title.
 * @param outputFile Open file where the report is written.
 * @details Includes accesses from earlier months, not just the named month.
 */
void printWriteMonthSummary(const SplayTree<IPRecord>& splayTree, const Month month,
                            ofstream& outputFile);

/**
 * @brief Prints the top 15 IPs and writes them to the output file.
 * @param splayTree Tree with the IP records.
 * @param outputFile Open file where the report is written.
 */
void printWriteTop15IpRecords(const SplayTree<IPRecord>& splayTree, ofstream& outputFile);

/**
 * @brief Prints the IP range report and writes it to the output file.
 * @param splayTree Tree with the IP records.
 * @param startIp First IP in the range, included in the search.
 * @param endIp Last IP in the range, included in the search.
 * @param outputFile Open file where the report is written.
 */
void printWriteIpRangeQuery(const SplayTree<IPRecord>& splayTree, const IP4& startIp,
                            const IP4& endIp, ofstream& outputFile);

/**
 * @brief Prints the block of the most accessed IP and writes it to the output file.
 * @param splayTree Tree with the IP records.
 * @param outputFile Open file where the report is written.
 * @pre The tree must contain at least one record.
 */
void printWriteTopIpBlockQuery(const SplayTree<IPRecord>& splayTree, ofstream& outputFile);

/**
 * @brief Asks for the insertion order and number of records, then runs the test.
 * @pre The number of records entered by the user must be zero or greater.
 */
void monitorTest();

/**
 * @brief Asks the user which insertion order to test.
 * @return char 'a' for ascending, 'b' for descending or 'c' for shuffled order.
 */
char monitorTestMenu();

/**
 * @brief Inserts IP records in ascending order to measure the time taken.
 * @param N Number of records to insert; it must be zero or greater.
 * @post Prints the insertion time in microseconds and the tree height.
 * The measured time includes creating the records.
 */
void ascendingOrder(int N);

/**
 * @brief Inserts IP records in descending order to measure the time taken.
 * @param N Number of records to insert; it must be zero or greater.
 * @post Prints the insertion time in microseconds and the tree height.
 * The measured time includes creating the records.
 */
void descendingOrder(int N);

/**
 * @brief Inserts IP records in shuffled order to measure the time taken.
 * @param N Number of records to insert; it must be zero or greater.
 * @post Prints the insertion time in microseconds and the tree height.
 * The measured time does not include creating or shuffling the records.
 */
void shuffled(int N);

/**
 * @brief Loads the log file and shows the application menu.
 * @return int 0 when the program finishes, or 1 if the file cannot be loaded.
 */
int main() {
    bool appIsRunning = true;

    cout << "Monitor -> use file 'bitacora_ordenada_date.txt'" << endl;

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
                monitor(logs);
                break;
            }
            case 5: {
                // Monitor test
                monitorTest();
                break;
            }
        }
    }

    return 0;
}

/**
 * @brief Shows the main menu and reads the selected option.
 * @return int An option between 0 and 5.
 */
int showMenu() {
    int option;
    bool isValid = false;

    do {
        cout << endl;
        cout << "[1] Sort bitacora" << endl;
        cout << "[2] Search by date" << endl;
        cout << "[3] Search by ip address" << endl;
        cout << "[4] Monitor" << endl;
        cout << "[5] Monitor Test" << endl;
        cout << "[0] Exit" << endl;
        cout << "> ";
        cin >> option;

        if (option < 0 || option > 5)
            cout << endl << "Invalid option. Try again" << endl;
        else
            isValid = true;
    } while (!isValid);

    return option;
}

/**
 * @brief Asks the user how to sort the logs.
 * @return char 'a' to sort by date or 'b' to sort by IP.
 */
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

/**
 * @brief Reads a file and adds its logs to the vector.
 * @param logs Vector where the logs are added.
 * @param filename Name of the file to read.
 * @post Keeps the logs in the same order as the file.
 * @throws std::runtime_error If the file cannot be opened.
 * @throws std::invalid_argument If a log contains invalid values.
 * @throws std::out_of_range If a port number is too large for an int.
 */
void loadLogs(vector<Log>& logs, const string& filename) {
    ifstream file(filename);

    // Opening file
    if (!file.is_open())
        throw runtime_error("Could not open '" + filename + "'");

    // Reading file
    string line;
    while (getline(file, line)) {
        Log log = Log::fromString(line);
        logs.push_back(log);
    }
    file.close();
}

/**
 * @brief Sorts the logs by date or IP and asks whether to save them.
 * @param logs Vector of logs to sort.
 * @post The vector is sorted in ascending order using the selected field.
 * The selected field is also used for later Log comparisons.
 */
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

/**
 * @brief Saves the logs into a text file, one log per line.
 * @param logs Vector of logs to save; it is not changed.
 * @param filename Name of the output file.
 * @post Replaces any previous contents of the file.
 * @throws std::runtime_error If the file cannot be created.
 */
void saveLogsIntoFile(vector<Log>& logs, const string& filename) {
    ofstream sortedFile(filename);

    if (sortedFile.is_open()) {
        for (const Log& log : logs) {
            sortedFile << log.toString() << endl;
        }
        sortedFile.close();
    } else
        throw runtime_error("Could not create txt file");
}

/**
 * @brief Asks the user for a date in Month Day HH:MM:SS format.
 * @return Date The date entered by the user.
 * @throws std::invalid_argument If the date values are invalid.
 */
Date getUserDate() {
    string dateStr;
    cout << "Enter the date and time (Month Day HH:MM:SS format): ";
    getline(cin, dateStr);
    return Date::fromString(dateStr);
}

/**
 * @brief Asks the user for an IP address in a.b.c.d format.
 * @return IP4 The address entered by the user.
 * @throws std::invalid_argument If the address is invalid.
 */
IP4 getUserIp4() {
    string ipStr;
    cout << "Enter the ip (192.168.1.2 format): ";
    getline(cin, ipStr);
    return IP4::fromString(ipStr);
}

/**
 * @brief Finds logs between two dates entered by the user, including both dates.
 * @param logs Vector of logs to search; it is not changed.
 * @post Prints the results and saves them in filtered_logs_date.txt.
 * The logs do not need to be sorted. Any previous file contents are replaced.
 */
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

/**
 * @brief Finds logs between two IP addresses, including both addresses.
 * @param logs Vector of logs to search; it is not changed.
 * @post Prints the results and saves them in filtered_logs_ip.txt.
 * The logs do not need to be sorted. Any previous file contents are replaced.
 */
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

/**
 * @brief Prints the report with all accesses read so far and writes it to the output file.
 * @param splayTree Tree with all IP records read so far.
 * @param month Month shown in the report title.
 * @param outputFile Open file where the report is written.
 * @details Includes accesses from earlier months, not just the named month.
 */
void printWriteMonthSummary(const SplayTree<IPRecord>& splayTree, const Month month,
                            ofstream& outputFile) {
    string summary = monthSummary(splayTree, month);
    cout << summary;
    outputFile << summary;
}

/**
 * @brief Prints the top 15 IPs and writes them to the output file.
 * @param splayTree Tree with the IP records.
 * @param outputFile Open file where the report is written.
 */
void printWriteTop15IpRecords(const SplayTree<IPRecord>& splayTree, ofstream& outputFile) {
    string top15Str = top15IpRecords(splayTree);
    cout << top15Str;
    outputFile << top15Str;
}

/**
 * @brief Prints the IP range report and writes it to the output file.
 * @param splayTree Tree with the IP records.
 * @param startIp First IP in the range, included in the search.
 * @param endIp Last IP in the range, included in the search.
 * @param outputFile Open file where the report is written.
 */
void printWriteIpRangeQuery(const SplayTree<IPRecord>& splayTree, const IP4& startIp,
                            const IP4& endIp, ofstream& outputFile) {
    string result = queryByIpRange(splayTree, startIp, endIp);
    cout << result;
    outputFile << result;
}

/**
 * @brief Prints the block of the most accessed IP and writes it to the output file.
 * @param splayTree Tree with the IP records.
 * @param outputFile Open file where the report is written.
 * @pre The tree must contain at least one record.
 */
void printWriteTopIpBlockQuery(const SplayTree<IPRecord>& splayTree, ofstream& outputFile) {
    string result = queryMostAccessedIpBlock(splayTree);
    cout << result;
    outputFile << result;
}

/**
 * @brief Counts accesses by IP and shows reports and IP range searches.
 * @param logs Vector of logs to read; it is not changed.
 * @pre The vector must not be empty and must be sorted by date.
 * @post Prints the reports and replaces the contents of output.txt.
 * @details Reports include all accesses read so far, including earlier months.
 * An access is successful when the first word of its message is "Accepted".
 * The final block search uses the block of the most accessed IP.
 */
void monitor(const vector<Log>& logs) {
    SplayTree<IPRecord> splayTree;
    Log prevRecord;
    bool isFirstLog = true;
    ofstream outputFile("output.txt");

    if (!outputFile.is_open()) {
        cerr << "Error: could not open output.txt" << endl;
        return;
    }

    // Read each log one at a time
    for (const Log& log : logs) {
        stringstream ss(log.getMessage());
        string firstWord;
        ss >> firstWord;

        if (!isFirstLog && prevRecord.getDate().getMonth() - log.getDate().getMonth() != 0) {
            // New month
            printWriteMonthSummary(splayTree, prevRecord.getDate().getMonth(), outputFile);
        }

        bool isSuccessful = firstWord == "Accepted";
        IPRecord record(log.getIp(), isSuccessful);
        if (!splayTree.insert(record)) {
            // Update total accesses and, when applicable, successful accesses
            splayTree.getRootValue().registerAccess(isSuccessful);
        }

        prevRecord = log;
        isFirstLog = false;
    }

    // Print the last report with all accesses read so far
    printWriteMonthSummary(splayTree, prevRecord.getDate().getMonth(), outputFile);

    // Print top 15 IP records
    printWriteTop15IpRecords(splayTree, outputFile);

    // Queries by IP range
    try {
        cin.ignore();
        cout << endl << "Query by IP range" << endl;
        cout << "==== Start ====" << endl;
        IP4 startIp = getUserIp4();

        cout << endl << "==== End ====" << endl;
        IP4 endIp = getUserIp4();
        printWriteIpRangeQuery(splayTree, startIp, endIp, outputFile);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    // Query the block of the most accessed IP
    printWriteTopIpBlockQuery(splayTree, outputFile);
    outputFile.close();
}

/**
 * @brief Asks the user which insertion order to test.
 * @return char 'a' for ascending, 'b' for descending or 'c' for shuffled order.
 */
char monitorTestMenu() {
    char option;
    bool isValid = false;

    do {
        cout << endl;
        cout << "\t[a] Ascending order" << endl;
        cout << "\t[b] Descending order" << endl;
        cout << "\t[c] Shuffled" << endl;
        cout << "> ";
        cin >> option;

        if (option < 'a' || option > 'c')
            cout << endl << "Invalid option. Try again" << endl;
        else
            isValid = true;
    } while (!isValid);

    return option;
}

/**
 * @brief Inserts IP records in ascending order to measure the time taken.
 * @param N Number of records to insert; it must be zero or greater.
 * @post Prints the insertion time in microseconds and the tree height.
 * The measured time includes creating the records.
 */
void ascendingOrder(int N) {
    SplayTree<IPRecord> splayTree;

    cout << "==== Ascending order ====" << endl;
    auto start = high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        // Each net part has to be within 0 and 255
        int d = i & 0xFF;
        int c = (i >> 8) & 0xFF;
        int b = (i >> 16) & 0xFF;
        int a = (i >> 24) & 0xFF;

        splayTree.insert(IPRecord(IP4(a, b, c, d), true));
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Splay Tree height: " << splayTree.height() << endl;
    cout << ">> Time (Ascending): " << duration.count() << " us" << endl;
}

/**
 * @brief Inserts IP records in descending order to measure the time taken.
 * @param N Number of records to insert; it must be zero or greater.
 * @post Prints the insertion time in microseconds and the tree height.
 * The measured time includes creating the records.
 */
void descendingOrder(int N) {
    SplayTree<IPRecord> splayTree;

    cout << "==== Descending order ====" << endl;
    auto start = high_resolution_clock::now();

    for (int i = N - 1; i >= 0; --i) {
        // Each net part has to be within 0 and 255
        int d = i & 0xFF;
        int c = (i >> 8) & 0xFF;
        int b = (i >> 16) & 0xFF;
        int a = (i >> 24) & 0xFF;

        splayTree.insert(IPRecord(IP4(a, b, c, d), true));
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Splay Tree height: " << splayTree.height() << endl;
    cout << ">> Time (Descending): " << duration.count() << " us" << endl;
}

/**
 * @brief Inserts IP records in shuffled order to measure the time taken.
 * @param N Number of records to insert; it must be zero or greater.
 * @post Prints the insertion time in microseconds and the tree height.
 * The measured time does not include creating or shuffling the records.
 */
void shuffled(int N) {
    SplayTree<IPRecord> splayTree;
    vector<IPRecord> records;
    records.reserve(N);

    for (int i = 0; i < N; ++i) {
        // Each net part has to be within 0 and 255
        int d = i & 0xFF;
        int c = (i >> 8) & 0xFF;
        int b = (i >> 16) & 0xFF;
        int a = (i >> 24) & 0xFF;
        records.push_back(IPRecord(IP4(a, b, c, d), true));
    }

    // Shuffle
    auto rng = default_random_engine(42);
    shuffle(records.begin(), records.end(), rng);

    cout << "--- Shuffled ---" << "\n";

    auto start = high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        splayTree.insert(records[i]);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Splay Tree height: " << splayTree.height() << endl;
    cout << ">> Time (Shuffled): " << duration.count() << " us" << endl;
}

/**
 * @brief Asks for the insertion order and number of records, then runs the test.
 * @pre The number of records entered by the user must be zero or greater.
 */
void monitorTest() {
    char option = monitorTestMenu();
    int N;
    cout << "Number of registers: ";
    cin >> N;

    switch (option) {
        case 'a': {
            ascendingOrder(N);
            break;
        }
        case 'b': {
            descendingOrder(N);
            break;
        }
        case 'c': {
            shuffled(N);
            break;
        }
    }
}
