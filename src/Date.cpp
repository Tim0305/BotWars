#include "Date.h"

#include <sstream>

string monthToString(const Month& month) {
    switch (month) {
        case Month::Jan:
            return "Jan";
        case Month::Feb:
            return "Feb";
        case Month::Mar:
            return "Mar";
        case Month::Apr:
            return "Apr";
        case Month::May:
            return "May";
        case Month::Jun:
            return "Jun";
        case Month::Jul:
            return "Jul";
        case Month::Aug:
            return "Aug";
        case Month::Sep:
            return "Sep";
        case Month::Oct:
            return "Oct";
        case Month::Nov:
            return "Nov";
        case Month::Dec:
            return "Dec";
        default:
            return "Unknown";
    }
}

Month stringToMonth(const string& str) {
    if (str == "Jan")
        return Month::Jan;
    if (str == "Feb")
        return Month::Feb;
    if (str == "Mar")
        return Month::Mar;
    if (str == "Apr")
        return Month::Apr;
    if (str == "May")
        return Month::May;
    if (str == "Jun")
        return Month::Jun;
    if (str == "Jul")
        return Month::Jul;
    if (str == "Aug")
        return Month::Aug;
    if (str == "Sep")
        return Month::Sep;
    if (str == "Oct")
        return Month::Oct;
    if (str == "Nov")
        return Month::Nov;
    if (str == "Dec")
        return Month::Dec;

    return Month::Unknown;  // Valor por defecto si el string no coincide
}

Date::Date(int day, Month month, int year, int hour, int minutes, int seconds)
    : day(day), month(month), year(year), hour(hour), minutes(minutes), seconds(seconds) {}

int Date::getDay() const { return this->day; }

Month Date::getMonth() const { return this->month; }

int Date::getYear() const { return this->year; }

int Date::getHour() const { return this->hour; }

int Date::getMinutes() const { return this->minutes; }

int Date::getSeconds() const { return this->seconds; }

bool Date::operator<(const Date& date) const {
    if (year != date.year)
        return year < date.year;
    if (month != date.month)
        return month < date.month;
    if (day != date.day)
        return day < date.day;
    if (hour != date.hour)
        return hour < date.hour;
    if (minutes != date.minutes)
        return minutes < date.minutes;
    return seconds < date.seconds;
}

bool Date::operator>(const Date& date) const { return date < *this; }

bool Date::operator==(const Date& date) const { return !(*this < date) && !(date > *this); }

bool Date::operator<=(const Date& date) const { return !(date < *this); }

bool Date::operator>=(const Date& date) const { return !(*this < date); }

string Date::toString() {
    stringstream ss;
    ss << monthToString(month) << " ";
    ss << day << " ";
    ss << hour << ":";
    ss << minutes << ":";
    ss << seconds;
    return ss.str();
}