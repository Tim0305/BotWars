/**
 * @file Log.h
 * @brief Class that represents a system log entry containing a date, IP address, domain, and message.
 * @author Team 1
 * @date 2026-09-10
 */
#pragma once

#include <string>

#include "Date.h"

using namespace std;

/**
 * @class Log
 * @brief Represents an individual log record.
 *
 * @property Log timestamp, source IP, domain, and associated error or status message.
 * Provides comparison operators for sorting based on its date attribute.
 * @property date An instance of the Date class that indicates when the log occurred
 * @property ip A string containing the source ip address that registered the log
 * @property domain A string containing the host domain name the attempt was directed to
 * @property message A string containing the action or result of the user attempt
 */
class Log {
private:
    Date date;
    string ip;
    string domain;
    string message;

public:
    Log(Date date, string ip, string domain, string message) : date(date), ip(ip), domain(domain), message(message) {};
    Date getDate() const;
    string getIp() const;
    string getDomain() const;
    string getMessage() const;
    bool operator>(const Log& log) const;
    bool operator<(const Log& log) const;
    bool operator==(const Log& log) const;
    bool operator>=(const Log& log) const;
    bool operator<=(const Log& log) const;
    string toString() const;
    static Log fromString(const string& strLog);
};