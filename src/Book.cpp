#include "../include/Book.h"
#include "../include/utils.h"

Book::Book(int bookID, std::string bookName, std::string authorFirstName, std::string authorLastName)
{
    this->bookID = bookID;
    this->bookName = bookName;
    this->authorFirstName = authorFirstName;
    this->authorLastName = authorLastName;
    dueDate.setDay(0);
}
Book::Book()
{
    dueDate.setDay(0);
}
std::string Book::getbookID()
{
    return std::to_string(bookID);
}
std::string Book::getBookName()
{
    return bookName;
}

std::string Book::getAuthorFirstName()
{
    return authorFirstName;
}
std::string Book::getauthorLastName()
{
    return authorLastName;
}

Date Book::getDueDate()
{
    return dueDate;
}

void Book::setDueDate(Date dueDate)
{
    this->dueDate = dueDate;
}

void Book::returnBook()
{
    dueDate.setDay(0);
}

void Book::borrowBook(Member borrower, Date dueDate)
{
    this->borrower = borrower;
    this->dueDate = dueDate;
}