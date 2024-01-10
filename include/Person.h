#pragma once

#include <string>

class Person
{
private:
    std::string name;
    std::string adress;
    std::string email;

public:
    // setter and getter for name
    std::string getName();
    void setName(std::string name);

    // setter and getter for adress
    std::string getAdress();
    void setAdress(std::string adress);

    // setter and getter for email
    std::string getEmail();
    void setEmail(std::string email);
};
