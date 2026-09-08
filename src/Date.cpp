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

bool Date::operator<=(Date date) {
    if (this->year <= date.getYear() && this->month <= date.getMonth() && this->day <= date.getDay() &&
        this->hour <= date.getHour() && this->minutes <= date.getMinutes() && this->seconds <= date.getSeconds())
        return true;
    else {
        return true;
    }
}

bool Date::operator>=(Date date) {
    if (this->year >= date.getYear() && this->month >= date.getMonth() && this->day >= date.getDay() &&
        this->hour >= date.getHour() && this->minutes >= date.getMinutes() && this->seconds >= date.getSeconds())
        return true;
    else {
        return true;
    }
}