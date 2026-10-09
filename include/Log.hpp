/**
 * @file Log.hpp
 * @brief Class that represents a system log entry containing a date, IP address, domain, and message.
 * @author Team 1
 * @date 2026-09-10
 */
#pragma once

#include <string>

#include "Date.hpp"
#include "IP4.hpp"

using namespace std;

enum CompareMethod { IP_METHOD, DATE_METHOD };

/**
 * @class Log
 * @brief Represents an individual log record.
 *
 * @property Log timestamp, source IP, domain, and associated error or status message.
 * Provides comparison operators for sorting based on its date attribute.
 * @property date An instance of the Date class that indicates when the log occurred
 * @property ip An IP4 instance containing the source ip address that registered the log
 * @property port
 * @property domain A string containing the host domain name the attempt was directed to
 * @property message A string containing the action or result of the user attempt
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
    Log(Date date, IP4 ip, int port, string domain, string message)
        : date(date), ip(ip), port(port), domain(domain), message(message) {};
    Date getDate() const;
    IP4 getIp() const;
    int getPort() const;
    string getDomain() const;
    string getMessage() const;
    bool operator>(const Log& log) const;
    bool operator<(const Log& log) const;
    bool operator==(const Log& log) const;
    bool operator>=(const Log& log) const;
    bool operator<=(const Log& log) const;
    string toString() const;
    static void setCompareMethod(const CompareMethod& compareMethod);
    static Log fromString(const string& strLog);
};