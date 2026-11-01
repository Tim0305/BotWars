/**
 * @file Date.hpp
 * @brief Header file defining the Date class, Month enum, and date utility functions.
 * @author Team 1
 * @date 2026-09-10
 */
#pragma once

#include <string>
using namespace std;

/**
 * @enum Month
 * @brief Maps months to values 1-12, with Unknown = 0 for unrecognized input.
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

/**
 * @brief Converts a month to its English abbreviation.
 * @return string The abbreviation, or "Unknown" if the month is invalid.
 */
string monthToString(const Month&);

/**
 * @brief Converts an English month abbreviation to a Month value.
 * @return Month The matching month, or Unknown if the text does not match.
 */
Month stringToMonth(const string&);

/**
 * @class Date
 * @brief Class that handles date and time operations, validation, comparison, and string parsing.
 *
 * @details Stores month, day and time without a year or time zone. February has 28 days.
 * The default constructor uses day 0 and month Unknown.
 *
 * @property day An integer that represents the day of the date
 * @property month Month type that represents the month of the date
 * @property hour An integer that represents the hour of the date
 * @property minutes An integer that represents the minutes of the hour
 * @property seconds An integer that represents the seconds of the minute
 */
class Date {
private:
    int day;
    Month month;
    int hour;
    int minutes;
    int seconds;

    /**
     * @brief Checks the date and time values.
     * @return true If all values are valid.
     * @return false Otherwise.
     */
    bool isValid() const;

public:
    /**
     * @brief Creates a Date with day 0, month Unknown and time 00:00:00.
     */
    Date();

    /**
     * @brief Creates a Date with the given day, month, hour, minutes and seconds.
     * @pre The values must form a valid date and time.
     * @throws std::invalid_argument If the values are invalid.
     */
    Date(int, Month, int, int, int);

    /**
     * @brief Gets the day of the date.
     * @return int The stored day.
     */
    int getDay() const;

    /**
     * @brief Gets the month of the date.
     * @return Month The stored month.
     */
    Month getMonth() const;

    /**
     * @brief Gets the hour of the date.
     * @return int The stored hour.
     */
    int getHour() const;

    /**
     * @brief Gets the minutes of the date.
     * @return int The stored minutes.
     */
    int getMinutes() const;

    /**
     * @brief Gets the seconds of the date.
     * @return int The stored seconds.
     */
    int getSeconds() const;

    /**
     * @brief Compares two dates.
     * @param date Date to compare with.
     * @return true If this date occurs after the given date.
     * @return false Otherwise.
     */
    bool operator>(const Date& date) const;

    /**
     * @brief Compares two dates.
     * @param date Date to compare with.
     * @return true If this date occurs before the given date.
     * @return false Otherwise.
     */
    bool operator<(const Date& date) const;

    /**
     * @brief Compares two dates.
     * @param date Date to compare with.
     * @return true If this date occurs on or after the given date.
     * @return false Otherwise.
     */
    bool operator>=(const Date& date) const;

    /**
     * @brief Compares two dates.
     * @param date Date to compare with.
     * @return true If this date occurs on or before the given date.
     * @return false Otherwise.
     */
    bool operator<=(const Date& date) const;

    /**
     * @brief Compares two dates.
     * @param date Date to compare with.
     * @return true If this date occurs at the same time as the given date.
     * @return false Otherwise.
     */
    bool operator==(const Date& date) const;

    /**
     * @brief Converts the date to text.
     * @return string The date in Month Day HH:MM:SS format.
     */
    string toString() const;

    /**
     * @brief Creates a Date from a string.
     * @param strDate Date in Month Day HH:MM:SS format.
     * @return Date The date read from the string.
     * @throws std::invalid_argument If the date or time values are invalid.
     */
    static Date fromString(const string& strDate);
};