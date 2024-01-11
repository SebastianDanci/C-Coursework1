#pragma once

#include <string>
#include <Date.h>
#include <Member.h>
class Member;
class Date;

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
