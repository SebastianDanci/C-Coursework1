/*
    Person.cpp
    Author: M00886707 <sd1507@mdx.ac.uk>
    Created: 09/01/2023
    Updated: 12/01/2023
*/
#include "../include/Person.h"

// Retrieves the name of the person
std::string Person::getName()
{
    // Return the private member variable 'name'
    return name;
}

// Sets the name of the person
void Person::setName(std::string name)
{
    // Assign the 'name' argument to the 'name' member variable
    this->name = name;
}

// Retrieves the address of the person
std::string Person::getAdress()
{
    // Return the private member variable 'adress'
    return adress;
}

// Sets the address of the person
void Person::setAdress(std::string adress)
{
    // Assign the 'adress' argument to the 'adress' member variable
    this->adress = adress;
}

// Retrieves the email of the person
std::string Person::getEmail()
{
    // Return the private member variable 'email'
    return email;
}

// Sets the email of the person
void Person::setEmail(std::string email)
{
    // Assign the 'email' argument to the 'email' member variable
    this->email = email;
}