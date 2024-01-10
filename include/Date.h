#ifndef DATE_H
#define DATE_H

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
    void setMonth( short unsigned int month);
    unsigned int getYear();
    void setYear(unsigned int year);
    bool isValid();
};

#endif