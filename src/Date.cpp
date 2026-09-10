#include "Date.h"

#include <sstream>
#include <stdexcept>

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

    // Default value if the string has no coincidence
    return Month::Unknown;
}

Date::Date(int day, Month month, int year, int hour, int minutes, int seconds) {
    this->day = day;
    this->month = month;
    this->year = year;
    this->hour = hour;
    this->minutes = minutes;
    this->seconds = seconds;

    if (!isValid()) {
        throw std::invalid_argument("Invalid date");
    }
}

bool Date::isValid() const {
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[1] = 29;
    }

    if (month < Month::Jan || month > Month::Dec)
        return false;
    if (day < 1 || day > daysInMonth[month - 1])
        return false;
    if (hour < 0 || hour > 23)
        return false;
    if (minutes < 0 || minutes > 59)
        return false;
    if (seconds < 0 || seconds > 59)
        return false;

    return true;
}

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

Date Date::fromString(const string& strDate) {
    string month, time;
    int year = 0, day = 0, hour = 0, minutes = 0, seconds = 0;
    char colon = ':';

    // Split the date using spaces
    stringstream input(strDate);
    input >> month >> day >> year >> time;

    // Split the time using :
    stringstream timeInput(time);
    timeInput >> hour >> colon >> minutes >> colon >> seconds;

    return Date(day, stringToMonth(month), year, hour, minutes, seconds);
}