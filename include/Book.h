#ifndef BOOK_H
#define BOOK_H
#include "Member.h"
#include "Date.h"
#include <string>

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
    std::string getboookID();
    std::string getBookName();
    std::string getAuthorFirstName();
    std::string getauthorLastName();
    Date getDueDate();
    void setDueDate(Date dueDate);
    void returnBook();
    void borrowBook(Member borrower, Date dueDate);
};

#endif