#ifndef PERSON_H
#define PERSON_H
/*
    Person.h
    Author: M00886707 <sd1507@mdx.ac.uk>
    Created: 09/01/2023
    Updated: 12/01/2023
*/

#include <string>

class Person
{
private:
    std::string name;
    std::string adress;
    std::string email;

public:
    std::string getName();
    void setName(std::string name);

    std::string getAdress();
    void setAdress(std::string adress);

    std::string getEmail();
    void setEmail(std::string email);
};

#endif