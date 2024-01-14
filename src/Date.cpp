/*
    Date.cpp
    Author: M00886707 <sd1507@mdx.ac.uk>
    Created: 11/01/2023
    Updated: 15/01/2023
*/
#include "../include/Date.h"
#include "../include/utils.h"

// Parametrized constructor to initialize a Date object with a specific date
Date::Date(short unsigned int day, short unsigned int month, unsigned int year)
{
    // Direct assignment of parameters to the member variables
    this->day = day;
    this->month = month;
    this->year = year;
}

// Default constructor for Date class initializing to a default date
Date::Date()
{
    // Set an invalid default date (0,0,0) to indicate no specific date is set
    day = 0;
    month = 0;
    year = 0;
}

// Getter method for day
short unsigned int Date::getDay()
{
    // Return the day of the date
    return day;
}

// Setter method for day
void Date::setDay(short unsigned int day)
{
    // Assign the day to the date
    this->day = day;
}

// Getter method for month
short unsigned int Date::getMonth()
{
    // Return the month of the date
    return month;
}

// Setter method for month
void Date::setMonth(short unsigned int month)
{
    // Assign the month to the date
    this->month = month;
}

// Getter method for year
unsigned int Date::getYear()
{
    // Return the year of the date
    return year;
}

// Setter method for year
void Date::setYear(unsigned int year)
{
    // Assign the year to the date
    this->year = year;
}

// Method to validate the date
bool Date::isValid()
{
    // Validate year range
    if (year < 1900 || year > 2100)
    {
        std::cout << ERROR_DATE_YEAR << std::endl;
        return false;
    }
    
    // Validate the month
    if (month < 1 || month > 12)
    {
        std::cout << ERROR_DATE_MONTH << std::endl;
        return false;
    }

    // Check for leap year and set the days in February accordingly
    bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    int daysInMonth[] = {31, 28 + isLeap, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Validate the day based on the month
    if (day < 1 || day > daysInMonth[month - 1])
    {
        std::cout << ERROR_DATE_DAY << std::endl;
        return false;
    }
    
    return true;
}

// Method to get a string representation of the date
std::string Date::getDate()
{
    // Create a character array to store the date string
    char dateStr[11];
    snprintf(dateStr, sizeof(dateStr), "%02d/%02d/%04d", day, month, year);
    // Return the formatted date as a string
    return std::string(dateStr);
}

// Static method to count the number of leap years up to a given date
int Date::countLeapYears(Date d)
{
    int years = d.getYear();
    // If the current year is not ended yet, decrement the year count
    if (d.getMonth() <= 2)
    {
        years--;
    }
    // Calculate the number of leap years
    return years / 4 - years / 100 + years / 400;
}

// Static method to calculate the total number of days since 00/00/0000 to a given date
int Date::getTotalDays(Date d)
{
    // Array to store the number of days in each month
    int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Calculate the total days accounting for years and leap years
    long totalDays = d.getYear() * 365 + countLeapYears(d);

    // Add the days for the months in the current year
    for (int i = 0; i < d.getMonth() - 1; i++)
    {
        totalDays += monthDays[i];
    }

    // Add the current day of the month
    totalDays += d.getDay();

    // Return the total number of days
    return totalDays;
}

// Static method to get the difference in days between two dates
int Date::getDateDifference(Date dateOne, Date dateTwo)
{
    // Calculate the total days for each date
    int totalDaysOne = getTotalDays(dateOne);
    int totalDaysTwo = getTotalDays(dateTwo);

    // Return the difference in total days
    return totalDaysOne - totalDaysTwo;
}

Date Date::addDays(int numDays, Date date) {
    const int daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Adding the days
    date.day += numDays;

    // Handling the overflow of days into months and possibly years
    while (date.day > daysPerMonth[date.month - 1]) {
        // Check for leap year
        bool isLeap = (date.year % 4 == 0 && (date.year % 100 != 0 || date.year % 400 == 0));
        if(isLeap && date.month == 2) { // Special case for February in a leap year
            if(date.day <= 29) {
                break;
            }
            date.day -= 29;
        } else {
            date.day -= daysPerMonth[date.month - 1];
        }

        date.month++;

        if (date.month > 12) { // overflow to next year
            date.month = 1;
            date.year++;
        }
    }

    // Ensure the new date is valid
    if (!date.isValid()) {
        // Handle error for invalid date result
        std::cout <<ERROR_DATE_INVALID<< std::endl;
        // Potentially set the date to a known valid state or handle the error appropriately
    }

    return date;
}