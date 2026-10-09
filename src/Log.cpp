/**
 * @file Log.cpp
 * @author Team 1
 * @brief Source file that implements the class Log and all its methods
 * @date 2026-09-10
 */
#include "Log.hpp"

#include <sstream>

#include "Date.hpp"

// Init the compare method
CompareMethod Log::compareMethod = CompareMethod::DATE_METHOD;

/**
 * @brief Gets the date of the log entry.
 *
 * @pre The Log object must be initialized.
 * @post Returns the internal Date object.
 * @return Date The timestamp of the log.
 */
Date Log::getDate() const { return this->date; }

/**
 * @brief Gets the IP address of the log entry.
 *
 * @pre The Log object must be initialized.
 * @post Returns the IP object.
 * @return instance of IP4 The IP address.
 */
IP4 Log::getIp() const { return this->ip; }

int Log::getPort() const { return this->port; }

/**
 * @brief Gets the domain of the log entry.
 *
 * @pre The Log object must be initialized.
 * @post Returns the domain string.
 * @return string The domain name.
 */
string Log::getDomain() const { return this->domain; }

/**
 * @brief Gets the message of the log entry.
 *
 * @pre The Log object must be initialized.
 * @post Returns the log message content.
 * @return string The message string.
 */
string Log::getMessage() const { return this->message; }

/**
 * @brief Overloads the less-than operator to compare two Log objects based on the compareMethod attribute.
 *
 * @param log The right-hand side Log instance to compare against.
 *
 * @pre Both Log objects must have valid Date/IP4 attributes.
 * @return true If this log's date/ip is strictly earlier/less than the parameter's date/ip.
 * @return false Otherwise.
 */
bool Log::operator<(const Log& log) const {
    switch (compareMethod) {
        case CompareMethod::DATE_METHOD:
            return this->date < log.date;
        case CompareMethod::IP_METHOD:
            return this->ip < log.ip;
        default:
            throw runtime_error("No compareMethod was defined");
    }
}

/**
 * @brief Overloads the greater-than operator to compare two Log objects based on the compareMethod attribute.
 *
 * @param log The right-hand side Log instance to compare against.
 *
 * @pre Both Log objects must have valid Date/IP4 attributes.
 * @return true If this log's date/ip is strictly later/greater than the parameter's date/ip.
 * @return false Otherwise.
 */
bool Log::operator>(const Log& log) const {
    switch (compareMethod) {
        case CompareMethod::DATE_METHOD:
            return this->date > log.date;
        case CompareMethod::IP_METHOD:
            return this->ip > log.ip;
        default:
            throw runtime_error("No compareMethod was defined");
    }
}

/**
 * @brief Overloads the equality operator to compare two Log objects based on the compareMethod attribute.
 *
 * @param log The right-hand side Log instance to compare against.
 *
 * @pre Both Log objects must have valid Date/IP4 attributes.
 * @return true If both log entries occurred at the exact same Date or have the same ip address.
 * @return false Otherwise.
 */
bool Log::operator==(const Log& log) const {
    switch (compareMethod) {
        case CompareMethod::DATE_METHOD:
            return this->date == log.date;
        case CompareMethod::IP_METHOD:
            return this->ip == log.ip;
        default:
            throw runtime_error("No compareMethod was defined");
    }
}

/**
 * @brief Overloads the greater-than-or-equal-to operator based on the compareMethod attribute.
 *
 * @param log The right-hand side Log instance to compare against.
 *
 * @pre Both Log objects must have valid Date/IP4 attributes.
 * @return true If this log's date is later than or equal to the parameter's date or this log's ip address is greater
 * than or equal to the parameter's ip.
 * @return false Otherwise.
 */
bool Log::operator>=(const Log& log) const {
    switch (compareMethod) {
        case CompareMethod::DATE_METHOD:
            return this->date >= log.date;
        case CompareMethod::IP_METHOD:
            return this->ip >= log.ip;
        default:
            throw runtime_error("No compareMethod was defined");
    }
}

/**
 * @brief Overloads the less-than-or-equal-to operator based on the compareMethod attribute.
 *
 * @param log The right-hand side Log instance to compare against.
 *
 * @pre Both Log objects must have valid Date/IP4 attributes.
 * @return true If this log's date is earlier than or equal to the parameter's date or this log's ip address is less
 * than or equal to the parameter's ip.
 * @return false Otherwise.
 */
bool Log::operator<=(const Log& log) const {
    switch (compareMethod) {
        case CompareMethod::DATE_METHOD:
            return this->date <= log.date;
        case CompareMethod::IP_METHOD:
            return this->ip <= log.ip;
        default:
            throw runtime_error("No compareMethod was defined");
    }
}

void Log::setCompareMethod(const CompareMethod& compareMethod) { Log::compareMethod = compareMethod; }

/**
 * @brief Converts the Log instance attributes into a formatted string representation.
 *
 * @pre The Log instance must contain valid member variables.
 * @post Generates a string combining date, IP, port, domain, and message.
 * @return string A single formatted string containing all log information.
 */
string Log::toString() const {
    stringstream ss;
    ss << date.toString() << " ";
    ss << ip.toString() << ":";
    ss << port << " ";
    ss << domain << " ";
    ss << message;
    return ss.str();
}

/**
 * @brief Parses a string representation of a log and creates a Log object instance.
 * Format: Month Day HH:MM:SS IP:Port DomainName Message
 *
 * @param strLog The raw string containing log information to be parsed.
 *
 * @pre The string 'strLog' must conform to the expected log text format.
 * @post Constructs and returns a new Log object with parsed attributes.
 * @return Log A populated Log instance extracted from the string.
 */
Log Log::fromString(const string& strLog) {
    string month, day, time, ip, domain, message;

    // Split each part using spaces
    stringstream ss(strLog);
    ss >> month >> day >> time >> ip >> domain;

    // Get all the message
    getline(ss >> std::ws, message);

    // Transform the date using the format: Month Day HH:MM:SS
    string dateStr = month + " " + day + " " + time;

    // Get the ip and port;
    // Clean and set the stringstream buffer
    ss.clear();
    ss.str(ip);
    vector<string> tokens;
    string token;

    while (getline(ss, token, ':')) tokens.push_back(token);

    if (tokens.size() != 2)
        throw invalid_argument("Invalid IP:Port");

    return Log(Date::fromString(dateStr), IP4::fromString(tokens[0]), stoi(tokens[1]), domain, message);
}