#pragma once

#include <string>

#include "Date.h"

using namespace std;

/**
 * @file Log.h
 * @brief Class that represents a system log entry containing a date, IP address, domain, and message.
 * @author Team 1
 * @date 2026-09-10
 */

 /**
 * @class Log
 * @brief Represents an individual log record.
 * 
 * @property Log timestamp, source IP, domain, and associated error or status message.
 * Provides comparison operators for sorting based on its date attribute.
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