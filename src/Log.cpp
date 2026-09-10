#include "Log.h"

#include <sstream>

Date Log::getDate() const { return this->date; }

string Log::getIp() const { return this->ip; }

string Log::getDomain() const { return this->domain; }

string Log::getMessage() const { return this->message; }

bool Log::operator<(const Log& log2) const { return this->date < log2.date; }

bool Log::operator>(const Log& log2) const { return this->date > log2.date; }

bool Log::operator==(const Log& log2) const { return this->date == log2.date; }

bool Log::operator>=(const Log& log2) const { return this->date >= log2.date; }

bool Log::operator<=(const Log& log2) const { return this->date <= log2.date; }

string Log::toString() {
    stringstream ss;
    ss << date.toString() << " ";
    ss << ip << " ";
    ss << domain << " ";
    ss << message;
    return ss.str();
}