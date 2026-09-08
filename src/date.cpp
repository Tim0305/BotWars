#include "Date.h"

Date::Date(int day, Month month, int year, int hour, int minutes, int seconds) {
    this->day = day;
    this->month = month;
    this->year = year;
    this->hour = hour;
    this->minutes = minutes;
    this->seconds = seconds;
}

int Date::getDay() { return this->day; }

Month Date::getMonth() { return this->month; }

int Date::getYear() { return this->year; }

int Date::getHour() { return this->hour; }

int Date::getMinutes() { return this->minutes; }

int Date::getSeconds() { return this->seconds; }

bool operator>(Date d1, Date d2) {}

bool Date::operator<=(Date date) {
    if (this->year > date.getYear())
        return false;
    else if (this->month > date.getMonth())
        return false;
    else if (this->day > date.getDay())
        return false;
    else if (this->hour > date.getHour())
        return false;
    else if (this->minutes > date.getMinutes())
        return false;
    else if (this->seconds > date.getSeconds())
        return false;
    else {
        return true;
    }
}
