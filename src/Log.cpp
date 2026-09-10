#include "Log.h"

#include <sstream>

#include "Date.h"

Date Log::getDate() const { return this->date; }

string Log::getIp() const { return this->ip; }

string Log::getDomain() const { return this->domain; }

string Log::getMessage() const { return this->message; }

bool Log::operator<(const Log& log2) const { return this->date < log2.date; }

bool Log::operator>(const Log& log2) const { return this->date > log2.date; }

bool Log::operator==(const Log& log2) const { return this->date == log2.date; }

bool Log::operator>=(const Log& log2) const { return this->date >= log2.date; }

bool Log::operator<=(const Log& log2) const { return this->date <= log2.date; }

string Log::toString() const {
    stringstream ss;
    ss << date.toString() << " ";
    ss << ip << " ";
    ss << domain << " ";
    ss << message;
    return ss.str();
}

Log Log::fromString(const string& strLog) {
    string month, time, ip, domain, message;
    int day = 0;

    // Split each part using spaces
    stringstream input(strLog);
    input >> month >> day >> time >> domain;
    getline(input >> std::ws, message);

    // Transform the date using the format Month Day Year HH:MM:SS
    stringstream date;
    date << month << " " << day << " " << 2026 << " " << time;

    return Log(Date::fromString(date.str()), ip, domain, message);
}