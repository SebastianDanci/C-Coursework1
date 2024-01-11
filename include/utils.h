#pragma once

#include <regex>
#include <string>
class Date;
class Member;
class Book;

extern Date currentDate;
extern std::vector<Member> members;
extern std::vector<Book> books;

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
extern const std::vector<std::string> MENU;

// Regex for user validation
extern const std::regex REGEX_NAME;
extern const std::regex REGEX_ADDRESS;
extern const std::regex REGEX_EMAIL;

extern int getUserInt(std::string message, int min, int max);
extern std::string getUserString(std::string message, std::regex pattern);
extern Date getUserDate(std::string message);
bool hasBorrowedThisBook(Member member, Book book);

//funcitons related to the main and menu loop
extern void runMenu();
extern void printMenuOptions();

