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

void Librarian::addMember()
{
    Member newMember(members.size() + 1, getUserString(GET_MEMBER_NAME, REGEX_NAME), getUserString(GET_MEMBER_ADDRESS, REGEX_ADDRESS), getUserString(GET_MEMBER_EMAIL, REGEX_EMAIL));
    members.push_back(newMember);
}
void Librarian::issueBook(int memberID, int bookID)
{
    // here i might need to check before i call the function if the book is already borrowed so that i dont delete it by accident
    Book book = books[bookID - 1];
    Member member = members[memberID - 1];

    member.setBooksBorrowed(book);

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
        std::cout<<"\n\nBook ID: "<<book.getboookID()<<", Book name: "<<book.getBookName()<<", Status: Borrowed, Due date: "<<book.getDueDate().getDate()<<std::endl;
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
        std::cout<<"\nFor Book ID: "<<book.getboookID()<<", Book name: "<<book.getBookName()<<". The fine is: "<<fine<<"£";
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


int Date::countLeapYears(Date d) {
    int years = d.getYear();
    if (d.getMonth() <= 2) {
        years--;
    }
    return years / 4 - years / 100 + years / 400;
}

int Date::getTotalDays(Date d) {
    int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    long totalDays = d.getYear() * 365 + countLeapYears(d);

    for (int i = 0; i < d.getMonth() - 1; i++) {
        totalDays += monthDays[i];
    }

    totalDays += d.getDay();

    return totalDays;
}

int Date::getDateDifference(Date dateOne, Date dateTwo) {
    int totalDaysOne = getTotalDays(dateOne);
    int totalDaysTwo = getTotalDays(dateTwo);

    return totalDaysTwo - totalDaysOne;
}
