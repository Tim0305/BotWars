#include "Date.h"

Date::Date(int day, Month month, int year, int hour, int minutes, int seconds) 
    : day(day), month(month), year(year), hour(hour), minutes(minutes), seconds(seconds) {}

int Date::getDay() const { return this->day; }

Month Date::getMonth() const { return this->month; }

int Date::getYear() const { return this->year; }

int Date::getHour() const { return this->hour; }

int Date::getMinutes() const { return this->minutes; }

int Date::getSeconds() const { return this->seconds; }

bool Date::operator<(const Date& date) const {
    if (year != date.year) return year < date.year;
    if (month != date.month) return month < date.month;
    if (day != date.day) return day < date.day;
    if (hour != date.hour) return hour < date.hour;
    if (minutes != date.minutes) return minutes < date.minutes;
    return seconds < date.seconds;
}

bool Date::operator>(const Date& date) const {
    return date < *this;
}


bool Date::operator==(const Date& date) const{
    return !(*this < date) && !(date > *this);
}

bool Date::operator<=(const Date& date) const {
    return !(date < *this);
}

bool Date::operator>=(const Date& date) const {
    return !(*this < date );
}