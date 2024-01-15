/*
    Librarian.cpp
    Author: M00886707 <sd1507@mdx.ac.uk>
    Created: 11/01/2023
    Updated: 15/01/2023
*/
#include "../include/Librarian.h"
#include "../include/Member.h"
#include "../include/Book.h"
#include "../include/utils.h"
#include "../include/Date.h"

// Constructor for Librarian with details including staff ID and salary
Librarian::Librarian(int staffID, std::string name, std::string address, std::string email, int salary)
{
    // Set staff details using both direct assignment and member function calls for name, address, and email
    this->staffid = staffID;
    this->salary = salary;
    setName(name);
    setAdress(address);
    setEmail(email);
}

// Default constructor for Librarian class
Librarian::Librarian()
{
    // Construct an empty Librarian object
}

// Function to add a new member to the library
void Librarian::addMember()
{
    // Create a new member with input details and add to the member list
    Member newMember(members.size() + 1, getUserString(GET_MEMBER_NAME, REGEX_FULL_NAME), getUserString(GET_MEMBER_ADDRESS, REGEX_ANY_STRING), getUserString(GET_MEMBER_EMAIL, REGEX_EMAIL));
    members.push_back(newMember);
    std::cout << MENU_MEMBER_ADDED << ", " << MENU_MEMBER_NAME << members[members.size() - 1].getName() << ", " << MENU_MEMBER_ID << members[members.size() - 1].getMemberID();
}

// Function to issue a book to a member
void Librarian::issueBook(int memberID, int bookID)
{
    short int returnAfterDayCount = 3;
    // Check if the book is not already issued
    if (books[bookID - 1].getDueDate().getDay() == 0)
    {
        books[bookID - 1].borrowBook(members[memberID - 1], Date::addDays(returnAfterDayCount, currentDate));
        members[memberID - 1].setBooksBorrowed(books[bookID - 1]);
        std::cout << std::endl
                  << std::endl
                  << MENU_BOOK_ISSUED;
    }
    else
    {
        std::cout <<std::endl<<std::endl<< MENU_ALREADY_ISSUED;
    }
}

// Function to process the return of a book from a member
void Librarian::returnBook(int memberID, int bookID)
{
    // Mark the book as returned and update the member's borrowed books list
    books[bookID - 1].returnBook();
    members[memberID - 1].setBooksBorrowed(books[bookID - 1]);
}

// Function to display all books borrowed by a specific member
void Librarian::displayBorrowedBooks(int memberID)
{
    // Display the number of books borrowed by the member
    std::cout << "\nMember has borrowed: " << members[memberID - 1].getBooksBorrowed().size() << " books:";

    // If there are members, display each borrowed book's details
    if (members.size() > 0)
        for (Book book : members[memberID - 1].getBooksBorrowed())
        {
            std::cout << std::endl<<std::endl<<MENU_BOOK_ID << book.getbookID() << ", Book name: " << book.getBookName() << ", Status: Borrowed, Due date: " << book.getDueDate().getDate() << std::endl;
        }
    else
    {
        std::cout << std::endl
                  << MENU_MEMBER_ISSUE;
    }
}

// Function to calculate the total fine for a member based on overdue books
void Librarian::calcFine(int memberID)
{
    int totalFine = 0;
    // Iterate over each borrowed book to calculate fines
    for (Book book : members[memberID - 1].getBooksBorrowed())
    {
        int fine = 0;
        // Calculate the difference in days from the due date
        int difference = Date::getDateDifference(book.getDueDate(), currentDate);
        // If the book is overdue, calculate the fine
        if (difference < 0)
            fine = difference * -1; // Fine is the negative of the difference in days
        std::cout << "\nFor"<<MENU_BOOK_ID<< book.getbookID() << ", Book name: " << book.getBookName() << ". The fine is: " << fine << "£";
        totalFine += fine; // Accumulate the total fine
    }
    std::cout << "\n\nThe total fine is: " << totalFine << "£"; // Display the total fine
}

// Getter for the staff ID
int Librarian::getStaffID()
{
    // Return the staff ID
    return staffid;
}

// Setter for the staff ID
void Librarian::setStaffID(int staffID)
{
    // Set the staff ID
    this->staffid = staffID;
}

// Getter for the salary
int Librarian::getSalary()
{
    // Return the salary
    return salary;
}

// Setter for the salary
void Librarian::setSalary(int salary)
{
    // Set the salary
    this->salary = salary;
}