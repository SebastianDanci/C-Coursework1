#pragma once

#include <regex>
#include <string>
class Date;
class Member;
class Book;

extern Date currentDate;
extern std::vector<Member> members;
extern std::vector<Book> books;
extern std::string sourceFile;
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


extern const std::vector<std::string> MENU;

extern const std::string CONFIG_CHANGE_FILE;
extern const std::string CONFIG_PROMPT_NEW_CSV;
extern const std::string CONFIG_CHANGE_DATE;
extern const std::string CONFIG_PROCEED;
extern const std::string CONFIG_START;


extern const std::vector<std::string> CONFIG;

// Regex for user validation
extern const std::regex REGEX_EMAIL;
extern const std::regex REGEX_ANY_STRING;

//functions for user input
extern int getUserInt(std::string message, int min, int max);
extern int getUserInt(std::vector<std::string> message, int min, int max);
extern std::string getUserString(std::string message, std::regex pattern);
extern Date getUserDate(std::string message);

//helper functions for classes
bool hasBorrowedThisBook(Member member, Book book);

//funcitons related to the menu and main program loop
extern void runMenu();
extern int runConfigs();
extern void createBook();
extern void printMenuOptions(std::vector<std::string> menu);
extern void changeCsv();

