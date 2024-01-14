#ifndef UTILS_H
#define UTILS_H
/*
    utils.h
    Author: M00886707 <sd1507@mdx.ac.uk>
    Created: 10/01/2023
    Updated: 15/01/2023
*/

#include <regex>
#include <string>
class Date;
class Member;
class Book;
class Librarian;

// Variables used throughout the program

extern Date currentDate;
extern std::vector<Member> members;
extern std::vector<Book> books;
extern bool isLastInputLine;

// Messages that will be displayed to the librarian

extern const std::string GET_MEMBER_NAME;
extern const std::string GET_MEMBER_ADDRESS;
extern const std::string GET_MEMBER_EMAIL;
extern const std::string GET_LIBRARIAN_NAME;
extern const std::string GET_LIBRARIAN_DUE_DATE;

extern const std::string MENU_INFO;
extern const std::string MENU_ADD_MEMBER;
extern const std::string MENU_ISSUE_BOOK;
extern const std::string MENU_RETURN_BOOK;
extern const std::string MENU_CALCULATE_FINE;
extern const std::string MENU_DISPLAY_ALL_BOOKS;
extern const std::string MENU_CALCULATE_FINE;
extern const std::string MENU_MAKE_CHOICE;
extern const std::string MENU_EXIT;
extern const std::string MENU_MEMBER_NAME;
extern const std::string MENU_MEMBER_ID;
extern const std::string MENU_MEMBER_ADDED;
extern const std::string MENU_BOOK_ID;
extern const std::string MENU_ISSUE_ISSUE;
extern const std::string MENU_RETURN;
extern const std::string MENU_RETURN_ISSUE;
extern const std::string MENU_NO_BOOKS;
extern const std::string MENU_MEMBER_ADDRESS;
extern const std::string MENU_MEMBER_EMAIL;
extern const std::string MENU_NO_BOOK;
extern const std::string MENU_BOOK_RETURNED;
extern const std::string MENU_BOOK_ISSUED;
extern const std::string MENU_ALREADY_ISSUED;
extern const std::string CONFIG_CHANGE_DATE;
extern const std::string MENU_CURRENT_DATE;
extern const std::string CONFIG_START;
extern const std::string CONFIG_ERROR_CSV;
extern const std::string CONFIG_ERROR_ROOT;
extern const std::string MENU_MEMBER_ISSUE;
extern const std::string ERROR_UNKNOWN;
extern const std::string ERROR_INTEGER;
extern const std::string ERROR_PATTERN;
extern const std::string ERROR_DATE;
extern const std::string ERROR_EOF;
extern const std::string ERROR_INPUT_FAILED;
extern const std::string ERROR_DATE_DAY;
extern const std::string ERROR_DATE_MONTH;
extern const std::string ERROR_DATE_YEAR;
extern const std::string ERROR_DATE_INVALID;
extern const std::string ERROR_PAST_DATE;

extern const std::vector<std::string> MENU;



// Regex for user validation

extern const std::regex REGEX_EMAIL;
extern const std::regex REGEX_ANY_STRING;
extern const std::regex REGEX_FULL_NAME;



// Functions for user input

// Returns an integer in an interval given by the user after a message prompt
extern int getUserInt(std::string message, int min, int max);

// Returns an integer in an interval given by the user after a vector / menu message prompt
extern int getUserInt(std::vector<std::string> message, int min, int max);

// Returns a string checked by a regex pattern given by the user after message prompt
extern std::string getUserString(std::string message, std::regex pattern);

// Returns a valid, possible, date in form of a Date object given by the user after message prompt
extern Date getUserDate(std::string message);

// Helper functions for classes

// Returns true if the member is currently loaning the book
bool hasBorrowedThisBook(Member member, Book book);

extern Date getCurrentDate();

// Funcitons related to the menu and main program loop

// Executes the main menu loop
extern void runMenu();

// Prints the options stored in a vector that guide the user
extern void printMenuOptions(std::vector<std::string> menu);

extern void issueBook(int bookID, long unsigned int memberID, Librarian librarian);

extern void getBooksBorrowed(long unsigned int memberID, Librarian librarian);

extern void returnBook(int bookID, long unsigned int memberID, Librarian librarian);

void calcFine(long unsigned int memberID, Librarian librarian);

// Returns the path of the cvs file
extern std::string findCsvFile();

// Creates book objects using the values in the csv file and pushes them in the books vector
std::vector<Book> readBooksFromCsv(const std::string &filePath);

extern void displayMemberDetails();

#endif