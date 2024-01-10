#pragma once

#include <regex>
#include <string>
class Date;
class Member;
class Book;

// Messages that will be displayed to the librarian
extern const std::string GET_MEMBER_NAME;
extern const std::string GET_MEMBER_ADDRESS;
extern const std::string GET_MEMBER_EMAIL;
extern const std::string GET_LIBRARIAN_NAME;
extern const std::string GET_LIBRARIAN_DUE_DATE;

// Regex for user validation
extern const std::regex REGEX_NAME;
extern const std::regex REGEX_ADDRESS;
extern const std::regex REGEX_EMAIL;

extern int getUserInt(std::string message, int min, int max);
extern std::string getUserString(std::string message, std::regex pattern);
extern Date getUserDate(std::string message);
bool hasBorrowedThisBook(Member member, Book book);
// date one - date two
extern int getDateDifference(Date dateOne, Date dateTwo);

