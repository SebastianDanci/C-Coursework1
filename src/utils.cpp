/*
    utils.cpp
    Author: M00886707 <sd1507@mdx.ac.uk>
    Created: 11/01/2023
    Updated: 12/01/2023
*/
#include "../include/utils.h"
#include "../include/Book.h"
#include "../include/Librarian.h"

#include <iostream>
#include <limits>
#include <sstream>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

Date currentDate;
std::vector<Member> members;
std::vector<Book> books;
bool isLastInputLine;

const std::regex REGEX_EMAIL("[^ ]+@[^ ]+\\.[a-z]{2,3}");
const std::regex REGEX_ANY_STRING(".*");

const std::string GET_MEMBER_NAME = "Enter the member's name> ";
const std::string GET_MEMBER_ADDRESS = "Enter the member's adress> ";
const std::string GET_MEMBER_EMAIL = "Enter the member's email adress> ";
const std::string GET_LIBRARIAN_NAME = "Enter your name> ";
const std::string GET_LIBRARIAN_DUE_DATE = "Enter the due date.\nThe day, month and year should be separated by a space (dd mm yyyy)> ";

const std::string MENU_INFO = "Type the number shown before each option to choose it.\n0. EXIT. ";
const std::string MENU_ADD_MEMBER = "Add a new member;";
const std::string MENU_ISSUE_BOOK = "Issue a book";
const std::string MENU_RETURN_BOOK = "Return a book";
const std::string MENU_DISPLAY_ALL_BOOKS = "Display the member's currently borrowed books;";
const std::string MENU_CALCULATE_FINE = "Calculate fine for due books;";
const std::string MENU_MAKE_CHOICE = "Enter the choice> ";
const std::string MENU_MEMBER_NAME = "Member name: ";
const std::string MENU_MEMBER_ID = "Member ID: ";
const std::string MENU_BOOK_ID = "Book ID: ";
const std::string MENU_MEMBER_ADDED = "A new member has been added";
const std::string MENU_EXIT = " \nThank you for using Virtual Library Manager\n\n EXITING...";
const std::string MENU_ISSUE = "Please enter Member ID and the Book ID you want to issue:";
const std::string MENU_ISSUE_ISSUE = "Cannot issue this book to this member!";
const std::string MENU_RETURN = "Please enter Member ID and the Book ID you want to return:";
const std::string MENU_RETURN_ISSUE = "There is no member with member ID:";
const std::string MENU_MEMBER_ISSUE = "There are no members registered in the library";

const std::vector<std::string> MENU = {MENU_INFO, MENU_ADD_MEMBER, MENU_ISSUE_BOOK, MENU_RETURN_BOOK, MENU_DISPLAY_ALL_BOOKS, MENU_CALCULATE_FINE, MENU_MAKE_CHOICE};

const std::string CONFIG_CHANGE_DATE = "Enter the new current date, The day, month and year should be separated by a space (dd mm yyyy)> ";
const std::string CONFIG_START = "Staring Virtual Library Manager...\n";

int getUserInt(std::string message, int min, int max)
{
    int number = 0;
    while (true)
    {
        try
        {
            std::cout << message;
            std::cin.clear();
            std::cin >> number;
            isLastInputLine = false;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Invalid input. Please enter a valid integer.");
            }

            if (number >= min && number <= max)
            {
                break;
            }
            else
            {
                throw std::runtime_error("The number is not in range.");
            }
        }
        catch (const std::runtime_error &ex)
        {
            std::cout << std::endl
                      << ex.what() << std::endl;
        }
        catch (...)
        {
            std::cout << "\n\nTry again" << std::endl;
        }
    }

    return number;
}

int getUserInt(std::vector<std::string> message, int min, int max)
{
    int number = 0;
    while (true)
    {
        try
        {
            printMenuOptions(message);
            std::cin.clear();
            std::cin >> number;
            isLastInputLine = false;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Invalid input. Please enter a valid integer.");
            }

            if (number >= min && number <= max)
            {
                break;
            }
            else
            {
                throw std::runtime_error("The number is not in range.");
            }
        }
        catch (const std::runtime_error &ex)
        {
            std::cout << std::endl
                      << ex.what() << std::endl;
        }
        catch (...)
        {
            std::cout << "\n\nTry again" << std::endl;
        }
    }

    return number;
}

std::string getUserString(std::string message, std::regex pattern)
{
    if (!isLastInputLine)
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string userInput;
    while (true)
    {
        std::cout << message;
        std::getline(std::cin, userInput);
        isLastInputLine = true;

        if (std::cin.fail())
        {
            if (std::cin.eof())
            {
                std::cin.clear();
                std::cout << "End of file encountered. Please provide input again.\n";
            }
            else
            {
                std::cin.clear();
                std::cout << "Failed to read input. Please try again.\n";
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (std::regex_match(userInput, pattern))
        {
            break;
        }
        else
        {
            std::cout << "The input does not match the required pattern. Try again.\n\n";
        }
    }
    return userInput;
}

Date getUserDate(std::string message)
{
    Date newDate;
    while (true)
    {
        std::cout << message;
        short unsigned int day;
        short unsigned int month;
        unsigned int year;

        try
        {
            std::cin.clear();
            std::cin >> day >> month >> year;
            isLastInputLine = false;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Invalid input. Please enter a valid date.");
            }

            newDate.setDay(day);
            newDate.setMonth(month);
            newDate.setYear(year);

            if (newDate.isValid())
            {
                break;
            }
            else
            {
                throw std::runtime_error("Entered date is not valid.");
            }
        }
        catch (const std::runtime_error &ex)
        {
            std::cout << "Error: " << ex.what() << "\nTry again.\n\n";
            std::cin.clear();
        }
        catch (...)
        {
            std::cout << "An unknown error occurred. Try again.\n\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return newDate;
}

bool hasBorrowedThisBook(Member member, Book book)
{
    bool hasBook = false;
    for (Book element : member.getBooksBorrowed())
        if (std::stoi(element.getbookID()) == std::stoi(book.getbookID()))
        {
            hasBook = true;
            break;
        }
    return hasBook;
}

// Menu related functions

void printMenuOptions(std::vector<std::string> menu)
{
    std::cout << std::endl
              << std::endl
              << menu[0];
    for (long unsigned int i = 1; i < menu.size() - 1; i++)
    {
        std::cout << std::endl
                  << i << ". " << menu[i];
    }
    std::cout << std::endl
              << std::endl
              << menu[menu.size() - 1];
}

void runMenu()
{
    int choice = 1, bookID;
    long unsigned int memberID;

    std::string csvFile = findCsvFile();
    if (csvFile.empty())
    {
        std::cout << "No CSV file found in the root folder." << std::endl;
        choice = 0;
    }
    else
    {
        books = readBooksFromCsv(csvFile);
        std::cout << CONFIG_START;
    }
    void createBook();

    currentDate = getUserDate(CONFIG_CHANGE_DATE);
    std::cout << "\nThe date is: " << currentDate.getDate();
    Librarian librarian;

    while (choice != 0)
    {
        choice = getUserInt(MENU, 0, 5);
        switch (choice)
        {
        case 1:
            librarian.addMember();
            std::cout << MENU_MEMBER_ADDED << ", " << MENU_MEMBER_NAME << members[members.size() - 1].getName() << ", " << MENU_MEMBER_ID << members[members.size() - 1].getMemberID();
            break;

        case 2:
            std::cout << MENU_ISSUE << std::endl;
            memberID = getUserInt(MENU_MEMBER_ID, 1, std::numeric_limits<int>::max());
            bookID = getUserInt(MENU_BOOK_ID, 1, books.size());
            if (memberID <= members.size())
                librarian.issueBook(memberID, bookID);
            else
                std::cout << std::endl
                          << MENU_ISSUE_ISSUE;
            break;

        case 3:
            std::cout << MENU_RETURN << std::endl;
            memberID = getUserInt(MENU_MEMBER_ID, 1, std::numeric_limits<int>::max());
            bookID = getUserInt(MENU_BOOK_ID, 1, books.size());
            if (memberID <= members.size())
                librarian.returnBook(memberID, bookID);
            else
                std::cout << std::endl
                          << MENU_RETURN_ISSUE << memberID;
            break;

        case 4:
            memberID = getUserInt(MENU_MEMBER_ID, 1, std::numeric_limits<int>::max());
            if (memberID <= members.size())
                librarian.displayBorrowedBooks(memberID);
            else
                std::cout << std::endl
                          << MENU_RETURN_ISSUE << memberID;
            break;

        case 5:
            memberID = getUserInt(MENU_MEMBER_ID, 1, std::numeric_limits<int>::max());
            if (memberID <= members.size())
                librarian.calcFine(memberID);
            else
                std::cout << std::endl
                          << MENU_RETURN_ISSUE << memberID;
            break;
        }
    }
    std::cout << MENU_EXIT;
}

std::string findCsvFile()
{
    fs::path dataDir = fs::current_path() / "../data";

    if (!fs::exists(dataDir) || !fs::is_directory(dataDir))
    {
        std::cout << "Data directory does not exist." << std::endl;
        return "";
    }

    for (const auto &entry : fs::directory_iterator(dataDir))
    {
        if (entry.path().extension() == ".csv")
        {
            return entry.path().string();
        }
    }
    return "";
}

std::vector<Book> readBooksFromCsv(const std::string &filePath)
{
    std::vector<Book> books;
    std::ifstream file(filePath);
    std::string line;

    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::istringstream sstream(line);
        std::string field;
        std::vector<std::string> fields;

        while (sstream.good())
        {
            std::getline(sstream, field, ',');
            fields.push_back(field);
        }

        if (fields.size() >= 6)
        {
            int bookID = std::stoi(fields[0]);
            Book book(bookID, fields[1], fields[3], fields[4]);
            books.push_back(book);
        }
    }

    return books;
}
