/*
    Book.cpp
    Author: M00886707 <sd1507@mdx.ac.uk>
    Created: 11/01/2023
    Updated: 12/01/2023
*/
#include "../include/Book.h"
#include "../include/utils.h"

// Constructor for Book class with parameters
Book::Book(int bookID, std::string bookName, std::string authorFirstName, std::string authorLastName)
{
    // Initialize the book with given parameters and set a default due date
    this->bookID = bookID;
    this->bookName = bookName;
    this->authorFirstName = authorFirstName;
    this->authorLastName = authorLastName;
    dueDate.setDay(0); // Default due date is set to an invalid value to signify no due date
}

// Default constructor for Book class
Book::Book()
{
    // Set default due date as an invalid value to signify no due date
    dueDate.setDay(0);
}

// Getter method for book ID
std::string Book::getbookID()
{
    // Convert numeric book ID to string and return
    return std::to_string(bookID);
}

// Getter method for book name
std::string Book::getBookName()
{
    // Return the name of the book
    return bookName;
}

// Getter method for author's first name
std::string Book::getAuthorFirstName()
{
    // Return the first name of the book's author
    return authorFirstName;
}

// Getter method for author's last name
std::string Book::getauthorLastName()
{
    // Return the last name of the book's author
    return authorLastName;
}

// Getter method for book's due date
Date Book::getDueDate()
{
    // Return the due date of the book
    return dueDate;
}

// Setter method for the due date
void Book::setDueDate(Date dueDate)
{
    // Set the due date of the book
    this->dueDate = dueDate;
}

// Method to handle the return of a book
void Book::returnBook()
{
    // Reset the due date to signify that the book is no longer borrowed
    dueDate.setDay(0);
}

// Method to handle the borrowing of a book
void Book::borrowBook(Member borrower, Date dueDate)
{
    // Set the borrower and due date when a book is borrowed
    this->borrower = borrower;
    this->dueDate = dueDate;
}