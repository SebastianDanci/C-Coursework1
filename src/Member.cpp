/*
    Member.cpp
    Author: M00886707 <sd1507@mdx.ac.uk>
    Created: 11/01/2023
    Updated: 12/01/2023
*/
#include "../include/Member.h"
#include "../include/Book.h"
#include "../include/utils.h"

// Constructor for creating a Member with personal information
Member::Member(int memberId, std::string name, std::string adress, std::string email)
{
    // Set the member's personal information using setters for name and address, and direct assignment for memberId
    setName(name);
    this->memberId = memberId;
    setAdress(adress);
    setEmail(email);
}

// Default constructor for Member class
Member::Member()
{
    // Construct an empty Member object
}

// Method to retrieve the Member's ID as a string
std::string Member::getMemberID()
{
    // Convert the memberId to string and return it
    return std::to_string(memberId);
}

// Method to retrieve the list of books borrowed by the Member
std::vector<Book> Member::getBooksBorrowed()
{
    // Return a copy of the vector containing all the books loaned to the member
    return booksLoaned;
}

// Method to update the books borrowed by the Member
void Member::setBooksBorrowed(Book book)
{
    // Check if the member has already borrowed the book
    if (!hasBorrowedThisBook(*this, book))
    {
        // If not already borrowed, add the book to the list of loaned books
        booksLoaned.push_back(book);
    }
    else
    {
        // If the book is already borrowed, remove it from the list
        booksLoaned.erase(booksLoaned.begin() + std::stoi(book.getbookID()) - 1);
    }
}