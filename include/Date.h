#pragma once
#include <string>
#include <iostream>
#include <cmath>

class Date
{
private:
    short unsigned int day;
    short unsigned int month;
    unsigned int year;

public:
    Date();
    Date(short unsigned int day, short unsigned int month, unsigned int year);
    short unsigned int getDay();
    void setDay(short unsigned int day);
    short unsigned int getMonth();
    void setMonth(short unsigned int month);
    unsigned int getYear();
    void setYear(unsigned int year);
    // returns true if the date if a possible real date
    bool isValid();
    // returns a string form dd/mm/yyyy
    std::string getDate();
    static int getDateDifference(Date dateOne, Date dateTwo);
    static int getTotalDays(Date d);
    static int countLeapYears(Date d);
};
