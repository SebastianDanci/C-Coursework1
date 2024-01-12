#ifndef LIBRARIAN_H
#define LIBRARIAN_H
/*
    Librarian.h
    Author: M00886707 <sd1507@mdx.ac.uk>
    Created: 09/01/2023
    Updated: 12/01/2023
*/

#include <string>
#include "person.h"

class Librarian : public Person
{
private:
    int staffid;
    int salary;

public:
    Librarian(int staffID, std::string name, std::string adress, std::string email, int salary);
    Librarian();
    void addMember();
    void issueBook(int memberID, int bookID);
    void returnBook(int memberID, int bookID);
    void displayBorrowedBooks(int memberID);
    void calcFine(int memberID);
    int getStaffID();
    void setStaffID(int staffID);
    int getSalary();
    void setSalary(int salary);
};

#endif