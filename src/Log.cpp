/**
 * @file Log.cpp
 * @author Team 1
 * @brief Source file that implements the class Log and all its methods
 * @date 2026-10-09
 */

#include "Log.hpp"

#include <sstream>
#include <vector>

#include "Date.hpp"

/**
 * @brief Initializes comparison mode shared by all Log instances.
 * @details Date comparison is the default until setCompareMethod selects another mode.
 */
CompareMethod Log::compareMethod = CompareMethod::DATE_METHOD;

/**
 * @brief Gets the date of the log entry.
 * @pre The Log object must be initialized.
 * @post Returns a copy of the stored Date object.
 * @return Date The timestamp of the log.
 */
Date Log::getDate() const { return this->date; }

/**
 * @brief Gets the IP address of the log entry.
 * @pre The Log object must be initialized.
 * @post Returns a copy of the stored IP object.
 * @return IP4 A copy of the IP address.
 */
IP4 Log::getIp() const { return this->ip; }

/**
 * @brief Gets the port associated with the log entry.
 * @pre The Log object must be initialized.
 * @return int The port number.
 */
int Log::getPort() const { return this->port; }

/**
 * @brief Gets the domain of the log entry.
 * @pre The Log object must be initialized.
 * @post Returns the domain string.
 * @return string The domain name.
 */
string Log::getDomain() const { return this->domain; }

/**
 * @brief Gets the message of the log entry.
 * @pre The Log object must be initialized.
 * @post Returns the log message content.
 * @return string The message string.
 */
string Log::getMessage() const { return this->message; }

/**
 * @brief Overloads the less-than operator to compare two Log objects based on the compareMethod
 * attribute.
 *
 * @param log The right-hand side Log instance to compare against.
 *
 * @pre Both Log objects must have valid Date/IP4 attributes.
 * @throws std::runtime_error If the shared comparison mode is not IP_METHOD or DATE_METHOD.
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
 * @brief Overloads the greater-than operator to compare two Log objects based on the compareMethod
 * attribute.
 *
 * @param log The right-hand side Log instance to compare against.
 *
 * @pre Both Log objects must have valid Date/IP4 attributes.
 * @throws std::runtime_error If the shared comparison mode is not IP_METHOD or DATE_METHOD.
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
 * @brief Overloads the equality operator to compare two Log objects based on the compareMethod
 * attribute.
 *
 * @param log The right-hand side Log instance to compare against.
 *
 * @pre Both Log objects must have valid Date/IP4 attributes.
 * @throws std::runtime_error If the shared comparison mode is not IP_METHOD or DATE_METHOD.
 * @return true If the selected field matches (date in DATE_METHOD, IP in IP_METHOD).
 * The port, domain and message are not compared.
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
 * @throws std::runtime_error If the shared comparison mode is not IP_METHOD or DATE_METHOD.
 * @return true If the selected date or IP is greater than or equal to the corresponding field.
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
 * @throws std::runtime_error If the shared comparison mode is not IP_METHOD or DATE_METHOD.
 * @return true If the selected date or IP is less than or equal to the corresponding field.
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

/**
 * @brief Sets the comparison mode shared by all Log objects.
 * @param compareMethod Comparison field to use: IP_METHOD or DATE_METHOD.
 * @post All subsequent Log comparisons use the selected field.
 * @pre Use IP_METHOD or DATE_METHOD. Keep the same method while sorting or searching.
 */
void Log::setCompareMethod(const CompareMethod& compareMethod) {
    Log::compareMethod = compareMethod;
}

/**
 * @brief Converts the Log instance attributes into a formatted string representation.
 *
 * @pre The Log instance must contain valid member variables.
 * @post Generates a string combining date, IP, port, domain, and message.
 * @return string A line formatted as "Month Day HH:MM:SS a.b.c.d:Port Domain Message",
 * without a final line break.
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
 * @details The domain is one word; the rest of the line is the message.
 * The port range and missing domain or message are not checked. The date and port
 * readers may accept extra text, so the full input format is not checked.
 * @throws std::invalid_argument If the date, IP or port cannot be read as expected.
 * @throws std::out_of_range If the port number is too large for an int.
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

    return Log(Date::fromString(dateStr), IP4::fromString(tokens[0]), stoi(tokens[1]), domain,
               message);
}
