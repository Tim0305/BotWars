#pragma once

#include <string>

#include "Date.h"

using namespace std;

class Log {
private:
    Date date;
    string ip;
    string domain;
    string message;

public:
    Log(Date date, string ip, string domain, string message) : date(date), ip(ip), domain(domain) {};
    Date getDate() const;
    string getIp() const;
    string getDomain() const;
    string getMessage() const;
    bool operator>(const Log& log) const;
    bool operator<(const Log& log) const;
    bool operator==(const Log& log) const;
    bool operator>=(const Log& log) const;
    bool operator<=(const Log& log) const;
    string toString();
};