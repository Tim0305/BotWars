/**
 * @file Date.cpp
 * @author Team 1
 * @brief Implementation of Date class and date utility functions
 * @date 2026-09-10
 */

#include "Date.h"

#include <sstream>
#include <stdexcept>

/**
 * @brief Converts a Month enum value to its corresponding string representation.
 *
 * @param month A constant reference to the Month enum value.
 *
 * @pre The Month enum value should ideally be within the defined range [Jan..Dec].
 * @post Converts the enum to its standard string name (e.g., Jan -> "Jan").
 * @return string The string representation of the month, or "Unknown" if invalid.
 */
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

/**
 * @brief Parses a string and converts it to its corresponding Month enum value.
 *
 * @param strMonth A constant reference to the string containing the month name/abbreviation.
 *
 * @pre The string should contain a recognizable month format.
 * @post Maps the text to its matching Month enum.
 * @return Month The corresponding Month enum value, or Unknown if no match is found.
 */
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

/**
 * @brief Construct a new Date object using the default parameter
 *
 */
Date::Date() {
    this->day = 0;
    this->month = Month::Unknown;
    this->hour = 0;
    this->minutes = 0;
    this->seconds = 0;
}

/**
 * @brief Parameterized constructor for the Date class.
 *
 * @param day Day of the month.
 * @param month Month enum value.
 * @param hour Hour value (0-23).
 * @param minutes Minutes value (0-59).
 * @param seconds Seconds value (0-59).
 *
 * @pre Input values must form a valid date and time combination.
 * @post A new Date instance is initialized with the specified values.
 */
Date::Date(int day, Month month, int hour, int minutes, int seconds) {
    this->day = day;
    this->month = month;
    this->hour = hour;
    this->minutes = minutes;
    this->seconds = seconds;

    // Validate if date is correct
    if (!isValid()) {
        throw std::invalid_argument("Invalid date");
    }
}

/**
 * @brief Helper function that validates if the date and time attributes are within correct bounds.
 *
 * @pre Internal attributes (day, month, hour, minutes, seconds) must be set.
 * @post Evaluates logical constraints for days per month, and time ranges.
 * @return true If the date and time combination is valid.
 * @return false Otherwise.
 */
bool Date::isValid() const {
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

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

/**
 * @brief Gets the day of the date.
 *
 * @pre The Date instance must be initialized.
 * @post Returns the day value.
 * @return int Day of the month.
 */
int Date::getDay() const { return this->day; }

/**
 * @brief Gets the month of the date.
 *
 * @pre The Date instance must be initialized.
 * @post Returns the Month enum value.
 * @return Month The month of the year.
 */
Month Date::getMonth() const { return this->month; }

/**
 * @brief Gets the hour component of the time.
 *
 * @pre The Date instance must be initialized.
 * @post Returns the hour value.
 * @return int Hour value (0-23).
 */
int Date::getHour() const { return this->hour; }

/**
 * @brief Gets the minutes component of the time.
 *
 * @pre The Date instance must be initialized.
 * @post Returns the minutes value.
 * @return int Minutes value (0-59).
 */
int Date::getMinutes() const { return this->minutes; }

/**
 * @brief Gets the seconds component of the time.
 *
 * @pre The Date instance must be initialized.
 * @post Returns the seconds value.
 * @return int Seconds value (0-59).
 */
int Date::getSeconds() const { return this->seconds; }

/**
 * @brief Overloads the greater-than-or-equal-to operator to compare two Date objects.
 *
 * @param date The right-hand side Date instance to compare against.
 *
 * @pre Both Date objects must be valid.
 * @post Evaluates timestamp ordering.
 * @return true If this Date occurs on or after the given date.
 * @return false Otherwise.
 */
bool Date::operator<(const Date& date) const {
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

/**
 * @brief Overloads the less-than operator to chronologically compare two Date objects.
 *
 * @param date The right-hand side Date instance to compare against.
 *
 * @pre Both Date objects must be valid.
 * @post Evaluates timestamp ordering.
 * @return true If this Date occurs before the given date.
 * @return false Otherwise.
 */
bool Date::operator>(const Date& date) const { return date < *this; }

/**
 * @brief Converts the Date instance attributes into a formatted string.
 *
 * @pre The Date instance must contain valid member variables.
 * @post Generates a string representation of the date and time.
 * @return string Formatted date-time string.
 */
bool Date::operator==(const Date& date) const { return !(*this < date) && !(date > *this); }

/**
 * @brief Overloads the equality operator to compare two Date objects.
 *
 * @param date The right-hand side Date instance to compare against.
 *
 * @pre Both Date objects must be valid.
 * @post Checks if both timestamps are identical.
 * @return true If both Date instances represent the exact same timestamp.
 * @return false Otherwise.
 */
bool Date::operator<=(const Date& date) const { return !(date < *this); }

/**
 * @brief Overloads the less-than-or-equal-to operator to compare two Date objects.
 *
 * @param date The right-hand side Date instance to compare against.
 *
 * @pre Both Date objects must be valid.
 * @post Evaluates timestamp ordering.
 * @return true If this Date occurs on or before the given date.
 * @return false Otherwise.
 */
bool Date::operator>=(const Date& date) const { return !(*this < date); }

/**
 * @brief Converts the Date instance attributes into a formatted string.
 *
 * @pre The Date instance must contain valid member variables.
 * @post Generates a string representation of the date and time.
 * @return string Formatted date-time string.
 */
string Date::toString() const {
    stringstream ss;
    ss << monthToString(month) << " ";
    ss << day << " ";
    ss << hour << ":";
    ss << minutes << ":";
    ss << seconds;
    return ss.str();
}

/**
 * @brief Parses a string representation of a date and constructs a Date object.
 * Format: Month Day HH:MM:SS
 *
 * @param strDate Raw date string to be parsed.
 *
 * @pre The string 'strDate' must follow the expected date string format.
 * @post Extracts and validates date/time fields to create a Date instance.
 * @return Date A populated Date object extracted from the string.
 */
Date Date::fromString(const string& strDate) {
    string month, time;
    int day = 0, hour = 0, minutes = 0, seconds = 0;
    char colon = ':';

    // Split the date using spaces
    stringstream input(strDate);
    input >> month >> day >> time;

    // Split the time using :
    stringstream timeInput(time);
    timeInput >> hour >> colon >> minutes >> colon >> seconds;

    return Date(day, stringToMonth(month), hour, minutes, seconds);
}