#include "../include/Person.h"

std::string Person::getName()
{
    return this->name;
}

void Person::setName(std::string name)
{
    this->name = name;
}

std::string Person::getAdress()
{
    return this->adress;
}

void Person::setAdress(std::string adress)
{
    this->adress=adress;
}

std::string Person::getEmail()
{
    return this->email;
}

void Person::setEmail(std::string email)
{
    this->email=email;
}