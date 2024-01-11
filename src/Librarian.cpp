#include "../include/Librarian.h"
#include "../include/Member.h"
#include "../include/Book.h"
#include "../include/utils.h"
#include "../include/Date.h"

Librarian::Librarian(int staffID, std::string name, std::string adress, std::string email, int salary)
{
    this->staffid = staffID;
    this->salary = salary;
    setName(name);
    setAdress(adress);
    setEmail(email);
}

Librarian::Librarian()
{
}
void Librarian::addMember()
{
    Member newMember(members.size() + 1, getUserString(GET_MEMBER_NAME, REGEX_ANY_STRING), getUserString(GET_MEMBER_ADDRESS, REGEX_ANY_STRING), getUserString(GET_MEMBER_EMAIL, REGEX_EMAIL));
    members.push_back(newMember);
}

void Librarian::issueBook(int memberID, int bookID)
{

    if (books[bookID - 1].getDueDate().getDay() == 0)
    {
        Date date = getUserDate(GET_LIBRARIAN_DUE_DATE);
        books[bookID - 1].borrowBook(members[memberID - 1], date);
        members[memberID - 1].setBooksBorrowed(books[bookID - 1]);
    }
    else
        std::cout << "\n The book has already been issued";
}

void Librarian::returnBook(int memberID, int bookID)
{
    books[bookID - 1].returnBook();
    members[memberID - 1].setBooksBorrowed(books[bookID - 1]);
}

void Librarian::displayBorrowedBooks(int memberID)
{
    std::cout << "\n Member has borrowed: " << members[memberID - 1].getBooksBorrowed().size() << " books:";

    if (members.size() > 0)
        for (Book book : members[memberID - 1].getBooksBorrowed())
        {
            std::cout << "\n\nBook ID: " << book.getbookID() << ", Book name: " << book.getBookName() << ", Status: Borrowed, Due date: " << book.getDueDate().getDate() << std::endl;
        }
    else
    {
        std::cout << std::endl
                  << MENU_MEMBER_ISSUE;
    }
}

void Librarian::calcFine(int memberID)
{
    int totalFine = 0;
    for (Book book : members[memberID - 1].getBooksBorrowed())
    {
        int fine = 0;
        int difference = Date::getDateDifference(book.getDueDate(), currentDate);
        std::cout << "the difference is" << difference;
        if (difference < 0)
            fine = difference * -1;
        std::cout << "\nFor Book ID: " << book.getbookID() << ", Book name: " << book.getBookName() << ". The fine is: " << fine << "£";
        totalFine += fine;
    }
    std::cout << "\n\nThe total fine is: " << totalFine << "£";
}

int Librarian::getStaffID()
{
    return staffid;
}

void Librarian::setStaffID(int staffID)
{
    this->staffid = staffID;
}

int Librarian::getSalary()
{
    return salary;
}

void Librarian::setSalary(int salary)
{
    this->salary = salary;
}
