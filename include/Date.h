#pragma once

#include <string>
using namespace std;

enum Month {
    Jan = 1,
    Feb = 2,
    Mar = 3,
    Apr = 4,
    May = 5,
    Jun = 6,
    Jul = 7,
    Ago = 8,
    Sep = 9,
    Oct = 10,
    Nov = 11,
    Dec = 12,
    Unknown = 0
};

string monthToString(const Month&);

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
    string toString();
};