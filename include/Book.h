#ifndef BOOK_H
#define BOOK_H
/*
    Book.h
    Author: M00886707 <sd1507@mdx.ac.uk>
    Created: 09/01/2023
    Updated: 12/01/2023
*/

#include <string>
#include "Date.h"
#include "Member.h"

class Book
{
private:
    int bookID;
    std::string bookName;
    std::string authorFirstName;
    std::string authorLastName;
    std::string bookType;
    Date dueDate;
    Member borrower;

public:
    Book(int bookID, std::string bookName, std::string authorFirstName, std::string authorLastName);
    Book();
    std::string getbookID();
    std::string getBookName();
    std::string getAuthorFirstName();
    std::string getauthorLastName();
    Date getDueDate();
    void setDueDate(Date dueDate);
    void returnBook();
    void borrowBook(Member borrower, Date dueDate);
};

#endif