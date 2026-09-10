/**
 * @file Log.cpp
 * @author Team 1
 * @brief Source file that implements the class Log and all its methods
 * @date 2026-09-10
 */
#include "Log.h"

#include <sstream>

#include "Date.h"

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
 * @post Returns the IP string.
 * @return string The IP address.
 */
string Log::getIp() const { return this->ip; }

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
 * @brief Overloads the less-than operator to compare two Log objects based on their Date.
 *
 * @param log The right-hand side Log instance to compare against.
 *
 * @pre Both Log objects must have valid Date attributes.
 * @post Performs chronological evaluation between this log and the given log.
 * @return true If this log's date is strictly less (earlier) than the parameter's date.
 * @return false Otherwise.
 */
bool Log::operator<(const Log& log2) const { return this->date < log2.date; }

/**
 * @brief Overloads the greater-than operator to compare two Log objects based on their Date.
 *
 * @param log The right-hand side Log instance to compare against.
 *
 * @pre Both Log objects must have valid Date attributes.
 * @post Performs chronological evaluation between this log and the given log.
 * @return true If this log's date is strictly greater (later) than the parameter's date.
 * @return false Otherwise.
 */
bool Log::operator>(const Log& log2) const { return this->date > log2.date; }

/**
 * @brief Overloads the equality operator to compare two Log objects based on their Date.
 *
 * @param log The right-hand side Log instance to compare against.
 *
 * @pre Both Log objects must have valid Date attributes.
 * @post Checks if both log dates match.
 * @return true If both log entries occurred at the exact same Date.
 * @return false Otherwise.
 */
bool Log::operator==(const Log& log2) const { return this->date == log2.date; }

/**
 * @brief Overloads the greater-than-or-equal-to operator based on Date.
 *
 * @param log The right-hand side Log instance to compare against.
 *
 * @pre Both Log objects must have valid Date attributes.
 * @post Performs chronological evaluation between this log and the given log.
 * @return true If this log's date is later than or equal to the parameter's date.
 * @return false Otherwise.
 */
bool Log::operator>=(const Log& log2) const { return this->date >= log2.date; }

/**
 * @brief Overloads the less-than-or-equal-to operator based on Date.
 *
 * @param log The right-hand side Log instance to compare against.
 *
 * @pre Both Log objects must have valid Date attributes.
 * @post Performs chronological evaluation between this log and the given log.
 * @return true If this log's date is earlier than or equal to the parameter's date.
 * @return false Otherwise.
 */
bool Log::operator<=(const Log& log2) const { return this->date <= log2.date; }

/**
 * @brief Converts the Log instance attributes into a formatted string representation.
 *
 * @pre The Log instance must contain valid member variables.
 * @post Generates a string combining date, IP, domain, and message.
 * @return string A single formatted string containing all log information.
 */
string Log::toString() const {
    stringstream ss;
    ss << date.toString() << " ";
    ss << ip << " ";
    ss << domain << " ";
    ss << message;
    return ss.str();
}

/**
 * @brief Parses a string representation of a log and creates a Log object instance.
 * Format: Month Day Year HH:MM:SS IP:Port DomainName Message
 *
 * @param strLog The raw string containing log information to be parsed.
 *
 * @pre The string 'strLog' must conform to the expected log text format.
 * @post Constructs and returns a new Log object with parsed attributes.
 * @return Log A populated Log instance extracted from the string.
 */
Log Log::fromString(const string& strLog) {
    string month, time, ip, domain, message;
    int day = 0;

    // Split each part using spaces
    stringstream input(strLog);
    input >> month >> day >> time >> domain;

    // Get all the message
    getline(input >> std::ws, message);

    // Transform the date using the format: Month Day Year HH:MM:SS
    stringstream date;
    date << month << " " << day << " " << 2026 << " " << time;

    return Log(Date::fromString(date.str()), ip, domain, message);
}