#ifndef UTILS_H
#define UTILS_H
/*
    utils.h
    Author: M00886707 <sd1507@mdx.ac.uk>
    Created: 10/01/2023
    Updated: 12/01/2023
*/

#include <regex>
#include <string>
class Date;
class Member;
class Book;

// variables used throughout the program

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
extern const std::string CONFIG_CHANGE_DATE;
extern const std::string CONFIG_START;
extern const std::string MENU_MEMBER_ISSUE;

extern const std::vector<std::string> MENU;

// Regex for user validation

extern const std::regex REGEX_EMAIL;
extern const std::regex REGEX_ANY_STRING;

// functions for user input

// returns an integer in an interval given by the user after a message prompt
extern int getUserInt(std::string message, int min, int max);
// returns an integer in an interval given by the user after a vector / menu message prompt
extern int getUserInt(std::vector<std::string> message, int min, int max);
// returns a string checked by a regex pattern given by the user after message prompt
extern std::string getUserString(std::string message, std::regex pattern);
// returns a valid, possible, date in form of a Date object given by the user after message prompt
extern Date getUserDate(std::string message);

// helper functions for classes

// returns true if the member is currently loaning the book
bool hasBorrowedThisBook(Member member, Book book);

// funcitons related to the menu and main program loop

// executes the main menu loop
extern void runMenu();
// prints the options stored in a vector that guide the user
extern void printMenuOptions(std::vector<std::string> menu);
// returns the path of the cvs file
extern std::string findCsvFile();
// creates book objects using the values in the csv file and pushes them in the books vector
std::vector<Book> readBooksFromCsv(const std::string &filePath);

#endif