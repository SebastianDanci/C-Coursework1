#include "../include/utils.h"
#include "../include/Book.h"
#include "../include/Librarian.h"

#include <iostream>
#include <limits>
#include <sstream>
#include <fstream>

Date currentDate;
std::vector<Member> members;
std::vector<Book> books;
std::string sourceFile = "library_books.csv";
bool isLastInputLine;

const std::regex REGEX_EMAIL("[^ ]+@[^ ]+\\.[a-z]{2,3}");
const std::regex REGEX_ANY_STRING(".*");

const std::string GET_MEMBER_NAME = "Enter the member's name> ";
const std::string GET_MEMBER_ADDRESS = "Enter the member's adress> ";
const std::string GET_MEMBER_EMAIL = "Enter the member's email adress> ";
const std::string GET_LIBRARIAN_NAME = "Enter your name> ";
const std::string GET_LIBRARIAN_DUE_DATE = "Enter the due date.\nThe day, month and year should be separated by a space (dd mm yyyy)> ";

const std::string MENU_INFO = "Type the number shown before each option to chose it.\n0. EXIT. ";
const std::string MENU_ADD_MEMBER = "Add a new member;";
const std::string MENU_ISSUE_BOOK = "Issue a book";
const std::string MENU_RETURN_BOOK = "Return a book";
const std::string MENU_DISPLAY_ALL_BOOKS = "Display the member's currently borrowed books;";
const std::string MENU_CALCULATE_FINE = "Claculate fine for due books;";
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

const std::vector<std::string> MENU = {MENU_INFO, MENU_ADD_MEMBER, MENU_ISSUE_BOOK, MENU_RETURN_BOOK, MENU_DISPLAY_ALL_BOOKS, MENU_CALCULATE_FINE, MENU_MAKE_CHOICE};

const std::string CONFIG_CHANGE_FILE = "Change the book csv file;";
const std::string CONFIG_CHANGE_DATE = "Enter the current date, The day, month and year should be separated by a space (dd mm yyyy)> ";
const std::string CONFIG_PROCEED = "Start the program;";
const std::string CONFIG_PROMPT_NEW_CSV = "\nEnter the name of the file (The file should be situated in the Data directory)> ";
const std::string CONFIG_START = "Staring Virtual Library Manager...\n";

const std::vector<std::string> CONFIG = {MENU_INFO, CONFIG_CHANGE_FILE, CONFIG_PROCEED, MENU_MAKE_CHOICE};

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
                // End-of-file was encountered
                std::cin.clear(); // Clear the EOF flag
                std::cout << "End of file encountered. Please provide input again.\n";
            }
            else
            {
                // Input stream is in an error state
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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

int runConfigs()
{
    currentDate = getUserDate(CONFIG_CHANGE_DATE);
    while (true)
    {
        int choice;
        choice = getUserInt(CONFIG, 0, 2);
        if (choice == 1)
            changeCsv();
        else
        {
            std::cout << CONFIG_START;
            createBook();
            return choice;
        }
    }
}

void changeCsv()
{
    sourceFile = getUserString(CONFIG_PROMPT_NEW_CSV, REGEX_ANY_STRING);
}

void runMenu()
{
    int choice, bookID;
    long unsigned int memberID;
    Librarian librarian;
    choice = runConfigs();
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

void createBook() {
    std::string filePath = "../data/" + sourceFile; // Construct the file path
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filePath << std::endl;
        return;
    }

    std::string line;
    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        // Extract each token separated by commas
        while (std::getline(ss, token, ',')) {
            // Handle potential quoted fields (like book names with commas)
            if (token.front() == '"' && token.back() != '"') {
                std::string nextToken;
                std::getline(ss, nextToken, ',');
                token += ',' + nextToken;
            }
            // Remove potential quotes from the token
            token.erase(remove(token.begin(), token.end(), '"'), token.end());
            tokens.push_back(token);
        }

        // Assuming the CSV format and Book constructor matches exactly:
        // Book ID, Book Name, Author First Name, Author Last Name, Book Type
        if (tokens.size() == 6) { // Ensure we have the correct number of tokens
            int bookID = std::stoi(tokens[0]);
            // Create a Book object
            Book book(bookID, tokens[1], tokens[3], tokens[4]); // Skipping page count here
            // Add the Book to the vector
            books.push_back(book);
        } else {
            std::cerr << "Invalid line format: " << line << std::endl;
        }
    }

    file.close();
}