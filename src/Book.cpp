#include "../include/Book.h"
#include "../include/utils.h"


Book::Book(int bookID, std::string bookName, std::string authorFirstName, std::string authorLastName)
{
    this->bookID = bookID;
    this->bookName = bookName;
    this->authorFirstName = authorFirstName;
    this->authorLastName = authorLastName;
}
Book::Book()
{
    
}
std::string Book::getbookID()
{
    return std::to_string(bookID);
}
std::string Book::getBookName()
{
    return this->bookName;
}

std::string Book::getAuthorFirstName()
{
    return this->authorFirstName;
}
std::string Book::getauthorLastName()
{
    return this->authorLastName;
}

Date Book::getDueDate()
{
    return this->dueDate;
}

void Book::setDueDate(Date dueDate)
{
    this->dueDate = dueDate;
}

void Book::returnBook()
{
    Member newMember;
    Date newDate;
    this->borrower = newMember;
    this->dueDate = newDate;
}

void Book::borrowBook(Member borrower, Date dueDate)
{
    bool canBorrow =true;
    for(Book book : this->borrower.getBooksBorrowed())
    {
        if (this->getbookID() == book.getbookID()) canBorrow=false;
    }
    if(canBorrow)
    {
    this->borrower = borrower;
    setDueDate(dueDate);
    }
    else
    {
        std::cout<<"Book with ID:"<<this->bookID<< " and name: "<<this->bookName<<" has already been borrowed.";
    }
}