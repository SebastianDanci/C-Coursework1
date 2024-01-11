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