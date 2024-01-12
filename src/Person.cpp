/*
    Person.cpp
    Author: M00886707 <sd1507@mdx.ac.uk>
    Created: 09/01/2023
    Updated: 12/01/2023
*/
#include "../include/Person.h"

std::string Person::getName()
{
    return name;
}

void Person::setName(std::string name)
{
    this->name = name;
}

std::string Person::getAdress()
{
    return adress;
}

void Person::setAdress(std::string adress)
{
    this->adress = adress;
}

std::string Person::getEmail()
{
    return email;
}

void Person::setEmail(std::string email)
{
    this->email = email;
}