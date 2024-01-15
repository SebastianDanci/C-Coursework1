/*
    test.cpp
    Author: M00886707 <sd1507@mdx.ac.uk>
    Created: 12/01/2023
    Updated: 15/01/2023
*/

#define CATCH_CONFIG_MAIN
#include "../include/catch.hpp"
#include "../include/Book.h"
#include "../include/Librarian.h"
#include "../include/utils.h"
#include "../include/Date.h"
#include "../include/Member.h"

TEST_CASE("Book class tests", "[Book]")
{
    Book book(1, "The Catcher in the Rye", "J.D.", "Salinger");

    SECTION("Testing book name retrieval")
    {
        REQUIRE(book.getBookName() == "The Catcher in the Rye");
    }

    SECTION("Testing author's first name retrieval")
    {
        REQUIRE(book.getAuthorFirstName() == "J.D.");
    }
}

TEST_CASE("Test hasBorrowedThisBook function", "[Utils]")
{
    Member member(1, "John Doe", "123 Street", "john@example.com");
    Book book(1, "Sample Book", "Author", "Surname");

    SECTION("Member has not borrowed the book")
    {
        REQUIRE(hasBorrowedThisBook(member, book) == false);
    }

    SECTION("Member has borrowed the book")
    {
        member.setBooksBorrowed(book); 
        REQUIRE(hasBorrowedThisBook(member, book) == true);
    }
}

TEST_CASE("Test findCsvFile function", "[Utils]")
{
    SECTION("CSV file is found")
    {

        REQUIRE_FALSE(findCsvFile().empty());
    }
}

TEST_CASE("Test readBooksFromCsv function", "[Utils]")
{
    SECTION("CSV file contains valid book data")
    {
        auto books = readBooksFromCsv(findCsvFile());
        REQUIRE_FALSE(books.empty()); 
    }

    SECTION("CSV file is empty or invalid")
    {
        std::string invalidCsvPath = "../include/file.csv";
        auto books = readBooksFromCsv(invalidCsvPath);
        REQUIRE(books.empty()); 
    }
}

TEST_CASE("Date::getDateDifference tests", "[Date]")
{
    SECTION("Difference between the same dates")
    {
        Date date1(1, 1, 2020);
        Date date2(1, 1, 2020);
        REQUIRE(Date::getDateDifference(date1, date2) == 0);
    }

    SECTION("Difference between two different dates")
    {
        Date date1(1, 1, 2020);
        Date date2(2, 1, 2020);
        REQUIRE(Date::getDateDifference(date1, date2) == -1);
    }
}

TEST_CASE("Date::isValid tests", "[Date]")
{
    SECTION("Valid date")
    {
        Date validDate(15, 6, 2021);
        REQUIRE(validDate.isValid() == true);
    }

    SECTION("Invalid date")
    {
        Date invalidDate(31, 2, 2021); 
        REQUIRE(invalidDate.isValid() == false);
    }
}

TEST_CASE("Member::setBooksBorrowed tests", "[Member]")
{
    Member member;
    Book book1(1, "Book1", "Author1", "Surname1");
    Book book2(2, "Book2", "Author2", "Surname2");

    SECTION("Add a book to borrowed list")
    {
        member.setBooksBorrowed(book1);
        REQUIRE(member.getBooksBorrowed().size() == 1);
    }

    SECTION("Add multiple books to borrowed list")
    {
        member.setBooksBorrowed(book1);
        member.setBooksBorrowed(book2);
        REQUIRE(member.getBooksBorrowed().size() == 2);
    }
}

TEST_CASE("Book due date setting and getting", "[Book]") {
    Book book(1, "Test Book", "Author", "Lastname");
    Date dueDate(20, 7, 2021);

    SECTION("Set due date") {
        book.setDueDate(dueDate);
        REQUIRE(book.getDueDate().getDate() == "20/07/2021");
    }

    SECTION("Reset due date") {
        Date newDueDate(25, 7, 2021);
        book.setDueDate(newDueDate);
        REQUIRE(book.getDueDate().getDate() == "25/07/2021");
    }
}

TEST_CASE("Date::addDays method", "[Date]") {
    Date baseDate(15, 6, 2021);

    SECTION("Add zero days") {
        Date newDate = Date::addDays(0, baseDate);
        REQUIRE(newDate.getDate() == baseDate.getDate());
    }

    SECTION("Add positive number of days") {
        Date newDate = Date::addDays(10, baseDate);
        REQUIRE(newDate.getDate() == "25/06/2021");
    }
}

TEST_CASE("Book borrowing process", "[Book]") {
    Member member(1, "Jane Doe", "456 Lane", "jane@example.com");
    Book book(2, "1984", "George", "Orwell");
    Date dueDate(1, 1, 2023);

    SECTION("Book is initially not borrowed") {
        REQUIRE(book.getDueDate().getDate() == "00/00/0000");
    }

    SECTION("Book is borrowed") {
        book.borrowBook(member, dueDate);
        REQUIRE(book.getDueDate().getDate() == "01/01/2023");
    }
}

TEST_CASE("Book return process", "[Book]") {
    Member member(1, "Jane Doe", "456 Lane", "jane@example.com");
    Book book(2, "1984", "George", "Orwell");
    Date dueDate(1, 1, 2023);
    book.borrowBook(member, dueDate);

    SECTION("Book is borrowed") {
        REQUIRE(book.getDueDate().getDate() == "01/01/2023");
    }

    SECTION("Book is returned") {
        book.returnBook();
        REQUIRE(book.getDueDate().getDate() == "00/01/2023");
    }
}

TEST_CASE("Date total days calculation", "[Date]") {
    Date date1(1, 1, 2000);

    SECTION("Start of millennium") {
        REQUIRE(Date::getTotalDays(date1) > 0);
    }

    SECTION("Current date") {
        Date currentDate = getCurrentDate();
        REQUIRE(Date::getTotalDays(currentDate) > Date::getTotalDays(date1));
    }
}
