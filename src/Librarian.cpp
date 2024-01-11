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
    Book book = books[bookID - 1];
    Member member = members[memberID - 1];

    if(!hasBorrowedThisBook(member, book))member.setBooksBorrowed(book);

    book.borrowBook(member, getUserDate(GET_LIBRARIAN_DUE_DATE));


}
void Librarian::returnBook(int memberID, int bookID)
{
    Book book = books[bookID - 1];
    Member member = members[memberID - 1];
    book.returnBook();
    member.setBooksBorrowed(book);
}
void Librarian::displayBorrowedBooks(int memberID)
{
    Member member = members[memberID - 1];
    for(Book book : member.getBooksBorrowed())
    {
        std::cout<<"\n\nBook ID: "<<book.getbookID()<<", Book name: "<<book.getBookName()<<", Status: Borrowed, Due date: "<<book.getDueDate().getDate()<<std::endl;
    }
}

void Librarian::calcFine(int memberID)
{
    int totalFine=0;
    Member member = members[memberID - 1];
    for(Book book : member.getBooksBorrowed())
    {
        int fine = 0;
        int difference = Date::getDateDifference(book.getDueDate(),currentDate);
        if(difference < 0) fine = difference * -1;
        std::cout<<"\nFor Book ID: "<<book.getbookID()<<", Book name: "<<book.getBookName()<<". The fine is: "<<fine<<"£";
        totalFine += fine;
    }
    std::cout<<"\n\nThe total fine is: "<<totalFine<<"£";
}

int Librarian::getStaffID()
{
    return this->staffid;
}

void Librarian::setStaffID(int staffID)
{
    this->staffid = staffID;
}

int Librarian::getSalary()
{
    return this->salary;
}

void Librarian::setSalary(int salary)
{
    this->salary = salary;
}


