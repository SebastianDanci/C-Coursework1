#include "../include/utils.h"
#include "../include/Book.h"
#include "../include/Librarian.h"

#include <iostream>
#include <limits>

Date currentDate;
std::vector<Member> members;
std::vector<Book> books;

const std::regex REGEX_NAME("^[A-Z][a-z]*$");
const std::regex REGEX_ADDRESS(R"(^\d+\s[A-z]+\s[A-z]+)");
const std::regex REGEX_EMAIL(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}\.uk$)");

const std::string GET_MEMBER_NAME = "Enter the member's name: ";
const std::string GET_MEMBER_ADDRESS = "Enter the member's adress: ";
const std::string GET_MEMBER_EMAIL = "Enter the member's email adress: ";
const std::string GET_LIBRARIAN_NAME = "Enter your name: ";
const std::string GET_LIBRARIAN_DUE_DATE = "Enter the due date.\nThe day, month and year should be separated by a space (dd mm yyyy): ";

const std::string MENU_INFO = "Type the number shown before each option to chose it.\nType 0 to exit.";
const std::string MENU_ADD_MEMBER = "Add a new member;";
const std::string MENU_ISSUE_BOOK = "Issue a book";
const std::string MENU_RETURN_BOOK = "Return a book";
const std::string MENU_DISPLAY_ALL_BOOKS = "Display the member's currently borrowed books;";
const std::string MENU_CALCULATE_FINE = "Claculate fine for due books;";
const std::string MENU_MAKE_CHOICE = "Enter the choice> ";
const std::vector<std::string> MENU = {MENU_INFO, MENU_ADD_MEMBER, MENU_ISSUE_BOOK, MENU_RETURN_BOOK, MENU_DISPLAY_ALL_BOOKS, MENU_CALCULATE_FINE, MENU_MAKE_CHOICE};

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
        catch (const std::runtime_error& ex)
        {
            std::cout << std::endl << ex.what() << std::endl;
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
    std::string userInput;
    while (true)
    {
        try
        {
            std::cout << message;
            std::getline(std::cin, userInput);

            if (std::cin.fail())
            {
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Failed to read input. Please try again.");
            }
            if (std::regex_match(userInput, pattern))
            {
                break;
            }
            else
            {
                throw std::runtime_error("The input does not match the required pattern.");
            }
        }
        catch (const std::runtime_error& ex)
        {
            std::cout << "Error: " << ex.what() << "\nTry again.\n\n";
        }
        catch (...)
        {
            std::cout << "An unknown error occurred. Try again.\n\n";
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
            std::cin >> day >> month >> year;
        }
        catch (...)
        {
            day = 0;
            month = 0;
            year = 0;
        }

        newDate.setDay(day);
        newDate.setMonth(month);
        newDate.setYear(year);
        if (newDate.isValid())
            break;
    }
    return newDate;
}

bool hasBorrowedThisBook(Member member, Book book)
{
    bool hasBook = false;
    for (Book element : member.getBooksBorrowed())
        if (std::stoi(element.getboookID()) == std::stoi(book.getboookID()))
        {
            hasBook = true;
            break;
        }
    return hasBook;
}

// Menu related functions

void printMenuOptions()
{
    for (int i = 0; i < MENU.size(); i++)
    {
        std::cout << std::endl
                  << std::endl
                  << i << ". " << MENU[i];
    }
}

void runMenu()
{
    while (true)
    {
        printMenuOptions();
        int choice =0;
        choice = getUserInt("", 0, 4);
        std::cout<<choice;
    }
}