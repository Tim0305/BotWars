/**
 * @file Date.h
 * @brief Header file defining the Date class, Month enum, and date utility functions.
 * @author Team 1
 * @date 2026-09-10
 */
#pragma once

#include <string>
using namespace std;

/**
 * @enum Month
 * @brief Represents the months of the year mapped to their numerical values (1-12).
 */
enum Month {
    Jan = 1,
    Feb = 2,
    Mar = 3,
    Apr = 4,
    May = 5,
    Jun = 6,
    Jul = 7,
    Aug = 8,
    Sep = 9,
    Oct = 10,
    Nov = 11,
    Dec = 12,
    Unknown = 0
};

string monthToString(const Month&);
Month stringToMonth(const string&);

/**
 * @class Date
 * @brief Class that handles date and time operations, validation, comparison, and string parsing.
 *
 * @property day An integer that represents the day of the date
 * @property month Month type that represents the month of the date
 * @property year An integer that represents the year of the date
 * @property hour An integer that represents the hour of the date
 * @property minutes An integer that represents the minutes of the hour
 * @property seconds An integer that represents the seconds of the hour
 */
class Date {
private:
    int day;
    Month month;
    int year;
    int hour;
    int minutes;
    int seconds;

    bool isValid() const;

public:
    Date(int, Month, int, int, int, int);
    int getDay() const;
    Month getMonth() const;
    int getYear() const;
    int getHour() const;
    int getMinutes() const;
    int getSeconds() const;
    bool operator>(const Date& date) const;
    bool operator<(const Date& date) const;
    bool operator>=(const Date& date) const;
    bool operator<=(const Date& date) const;
    bool operator==(const Date& date) const;
    string toString() const;
    static Date fromString(const string& strDate);
};