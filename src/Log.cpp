#include "Log.h"

Date Log::getDate() { return this->date; }

string Log::getIp() { return this->ip; }

string Log::getDomain() { return this->domain; }

string Log::getMessage() { return this->message; }

bool Log::operator<(Log log2) { return this->date < log2.date; }

bool Log::operator>(Log log2) { return this->date > log2.date; }

bool Log::operator==(Log log2) { return this->date == log2.date; }

bool Log::operator>=(Log log2) { return this->date >= log2.date; }

bool Log::operator<=(Log log2) { return this->date <= log2.date; }
