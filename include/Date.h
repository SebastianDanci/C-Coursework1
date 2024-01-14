#ifndef DATE_H
#define DATE_H
/*
    Date.h
    Author: M00886707 <sd1507@mdx.ac.uk>
    Created: 09/01/2023
    Updated: 15/01/2023
*/

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
    // returns the difference between dateOne and dateTwo
    static int getDateDifference(Date dateOne, Date dateTwo);
    // returns the total number of days since day 0 month 0 year 0
    static int getTotalDays(Date d);
    // helper function for getTotalDays
    static int countLeapYears(Date d);
    // adds a number of days to a date
    static Date addDays(int numDays, Date date);
};

#endif