#include "../include/Date.h"

Date::Date(short unsigned int day, short unsigned int month, unsigned int year)
{
    day = day;
    month = month;
    year = year;
}

Date::Date()
{
    day = 0;
    year = 0;
    month = 0;
}

short unsigned int Date::getDay()
{
    return day;
}

void Date::setDay(short unsigned int day)
{
    this->day = day;
}

short unsigned int Date::getMonth()
{
    return month;
}

void Date::setMonth(short unsigned int month)
{
    this->month = month;
}

unsigned int Date::getYear()
{
    return year;
}

void Date::setYear(unsigned int year)
{
    this->year = year;
}

bool Date::isValid()
{

    if (year < 1900 || year > 2100)
    {
        std::cout << "Invalid year. Please enter a year between 1900 and 2100." << std::endl;
        return false;
    }
    // Check month
    if (month < 1 || month > 12)
    {
        std::cout << "Invalid month. Please enter a month between 1 and 12." << std::endl;
        return false;
    }

    bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    int daysInMonth[] = {31, 28 + isLeap, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (day < 1 || day > daysInMonth[month - 1])
    {
        std::cout << "Invalid day. Please enter a valid day for the specified month." << std::endl;
        return false;
    }
    return true;
}

std::string Date::getDate()
{
    char dateStr[11];
    snprintf(dateStr, sizeof(dateStr), "%02d/%02d/%04d", day, month, year);
    return std::string(dateStr);
}

int Date::countLeapYears(Date d)
{
    int years = d.getYear();
    if (d.getMonth() <= 2)
    {
        years--;
    }
    return years / 4 - years / 100 + years / 400;
}

int Date::getTotalDays(Date d)
{
    int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    long totalDays = d.getYear() * 365 + countLeapYears(d);

    for (int i = 0; i < d.getMonth() - 1; i++)
    {
        totalDays += monthDays[i];
    }

    totalDays += d.getDay();

    return totalDays;
}

int Date::getDateDifference(Date dateOne, Date dateTwo)
{
    int totalDaysOne = getTotalDays(dateOne);
    int totalDaysTwo = getTotalDays(dateTwo);

    return totalDaysOne - totalDaysTwo;
}