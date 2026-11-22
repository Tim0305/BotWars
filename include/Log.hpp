/**
 * @file Log.hpp
 * @brief Class that represents a system log entry containing a date, IP address, port, domain, and
 * message.
 * @author Team 1
 * @date 2026-10-09
 */

#pragma once

#include <string>

#include "Date.hpp"
#include "IP4.hpp"

using namespace std;

/**
 * @enum CompareMethod
 * @brief Selects the field used by Log operators.
 * IP_METHOD: Compares Log objects by their IP address.
 * DATE_METHOD: Compares Log objects by their timestamp.
 */
enum CompareMethod { IP_METHOD, DATE_METHOD };

/**
 * @class Log
 * @brief Represents an individual log record.
 *
 * @details Each record contains a timestamp, source IP, port, domain, and log message.
 * Comparison operators use the compareMethod setting to compare records by date or by IP address.
 * Logs are compared by date unless another method is selected. Equality checks only
 * the selected date or IP, not the port, domain or message.
 * @property date An instance of the Date class that indicates when the log occurred
 * @property ip An IP4 instance containing the source ip address that registered the log
 * @property port An int containing the port which registered the log
 * @property domain A string containing the host domain name the attempt was directed to
 * @property message A string containing the action or result of the user attempt
 * @property compareMethod Static comparison mode shared by all Logs.
 */
class Log {
private:
    Date date;
    IP4 ip;
    int port;
    string domain;
    string message;
    static CompareMethod compareMethod;

public:
    /**
     * @brief Constructs a Log object with default values.
     * Complexity: O(1).
     * @post Uses a default Date, IP 0.0.0.0, port 0 and empty domain and message.
     */
    Log() : date(Date()), ip(IP4(0, 0, 0, 0)), port(0), domain(""), message("") {};

    /**
     * @brief Constructs a log with the given values, without checking them.
     * Complexity: O(d + m), where d and m are the domain and message lengths.
     * @param date Timestamp to store.
     * @param ip Source address to store.
     * @param port Port value to store; no range check is performed.
     * @param domain Destination domain to store.
     * @param message Access message to store.
     */
    Log(Date date, IP4 ip, int port, string domain, string message)
        : date(date), ip(ip), port(port), domain(domain), message(message) {};

    /**
     * @brief Gets the date of the log.
     * Complexity: O(1).
     * @return Date The stored date.
     */
    Date getDate() const;

    /**
     * @brief Gets the IP address of the log.
     * Complexity: O(1).
     * @return IP4 The stored IP address.
     */
    IP4 getIp() const;

    /**
     * @brief Gets the port of the log.
     * Complexity: O(1).
     * @return int The stored port.
     */
    int getPort() const;

    /**
     * @brief Gets the domain of the log.
     * Complexity: O(d), where d is the domain length, because the string is copied.
     * @return string The stored domain.
     */
    string getDomain() const;

    /**
     * @brief Gets the message of the log.
     * Complexity: O(m), where m is the message length, because the string is copied.
     * @return string The stored message.
     */
    string getMessage() const;

    /**
     * @brief Compares logs using the selected date or IP field.
     * Complexity: O(1).
     * @param log Log to compare with.
     * @return true If the selected field is greater than the other log's field.
     * @return false Otherwise.
     */
    bool operator>(const Log& log) const;

    /**
     * @brief Compares logs using the selected date or IP field.
     * Complexity: O(1).
     * @param log Log to compare with.
     * @return true If the selected field is less than the other log's field.
     * @return false Otherwise.
     */
    bool operator<(const Log& log) const;

    /**
     * @brief Compares logs using the selected date or IP field.
     * Complexity: O(1).
     * @param log Log to compare with.
     * @return true If the selected field is equal to the other log's field.
     * @return false Otherwise.
     */
    bool operator==(const Log& log) const;

    /**
     * @brief Compares logs using the selected date or IP field.
     * Complexity: O(1).
     * @param log Log to compare with.
     * @return true If the selected field is greater than or equal to the other log's field.
     * @return false Otherwise.
     */
    bool operator>=(const Log& log) const;

    /**
     * @brief Compares logs using the selected date or IP field.
     * Complexity: O(1).
     * @param log Log to compare with.
     * @return true If the selected field is less than or equal to the other log's field.
     * @return false Otherwise.
     */
    bool operator<=(const Log& log) const;

    /**
     * @brief Converts the log to text.
     * Complexity: O(d + m), where d and m are the domain and message lengths.
     * @return string The date, IP, port, domain and message in one line.
     */
    string toString() const;

    /**
     * @brief Selects the field used to compare all Log objects.
     * Complexity: O(1).
     * @param compareMethod IP_METHOD to compare IPs or DATE_METHOD to compare dates.
     */
    static void setCompareMethod(const CompareMethod& compareMethod);

    /**
     * @brief Creates a Log from a string.
     * Complexity: O(n), where n is the input line length.
     * @param strLog Text in Month Day HH:MM:SS IP:Port Domain Message format.
     * @return Log The log read from the string.
     * @throws std::invalid_argument If the date, IP or port cannot be read as expected.
     * @throws std::out_of_range If the port number is too large for an int.
     */
    static Log fromString(const string& strLog);
};