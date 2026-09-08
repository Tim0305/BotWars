#pragma once

#include <string>

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
    Dec = 12
};

class Date {
private:
    int day;
    Month month;
    int year;
    int hour;
    int minutes;
    int seconds;

public:
    Date(int, Month, int, int, int, int);
    int getDay();
    Month getMonth();
    int getYear();
    bool operator>(Date Date);
    bool operator<(Date Date);
    bool operator>=(Date Date);
    bool operator<=(Date Date);
    bool operator==(Date Date);
};