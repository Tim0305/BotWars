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
    Date getDate();
    string getIp();
    string getDomain();
    string getMessage();
    bool operator>(Log);
    bool operator<(Log);
    bool operator==(Log);
    bool operator>=(Log);
    bool operator<=(Log);
};