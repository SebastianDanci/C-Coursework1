#ifndef MEMBER_H
#define MEMBER_H
/*
    Member.h
    Author: M00886707 <sd1507@mdx.ac.uk>
    Created: 09/01/2023
    Updated: 12/01/2023
*/

#include <string>
#include <vector>
#include "Person.h"
class Book;

class Member : public Person
{
private:
    int memberId;
    std::vector<Book> booksLoaned;

public:
    // constructor for member class
    Member(int memberId, std::string name, std::string adress, std::string email);
    Member();
    std::string getMemberID();
    std::vector<Book> getBooksBorrowed();
    void setBooksBorrowed(Book book);
};

#endif