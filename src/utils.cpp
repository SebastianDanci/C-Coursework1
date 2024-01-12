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

// Global variables used throughout the program
Date currentDate;            // Holds the current date for the library system
std::vector<Member> members; // A list of all the members in the library
std::vector<Book> books;     // A list of all the books in the library
bool isLastInputLine;        // Flag to check if the last input line should be ignored

// Regular expressions for validating user input
const std::regex REGEX_EMAIL("[^ ]+@[^ ]+\\.[a-z]{2,3}");                               // Regex to validate email addresses
const std::regex REGEX_ANY_STRING(".*");                                                // Regex to match any string
const std::regex REGEX_FULL_NAME("^[A-Za-zÀ-ÖØ-öø-ÿ]+(?:[\\s'-][A-Za-zÀ-ÖØ-öø-ÿ]+)*$"); // Regex to match any name

// Constants for user prompts and messages
const std::string GET_MEMBER_NAME = "Enter the member's name> ";
const std::string GET_MEMBER_ADDRESS = "Enter the member's address> ";
const std::string GET_MEMBER_EMAIL = "Enter the member's email address> ";
const std::string GET_LIBRARIAN_NAME = "Enter your name> ";
const std::string GET_LIBRARIAN_DUE_DATE = "Enter the due date (format: dd mm yyyy)> ";

// Menu information strings
const std::string MENU_INFO = "Choose an option by typing the corresponding number:\n0. EXIT. ";
const std::string MENU_ADD_MEMBER = "Add a new member;";
const std::string MENU_ISSUE_BOOK = "Issue a book;";
const std::string MENU_RETURN_BOOK = "Return a book;";
const std::string MENU_DISPLAY_ALL_BOOKS = "Display currently borrowed books;";
const std::string MENU_CHANGE_DATE = "Change the system date;";
const std::string MENU_CALCULATE_FINE = "Calculate fine for overdue books;";
const std::string MENU_MAKE_CHOICE = "Enter your choice> ";

// Feedback messages for various menu actions
const std::string MENU_MEMBER_NAME = "Member name: ";
const std::string MENU_MEMBER_ID = "Member ID: ";
const std::string MENU_BOOK_ID = "Book ID: ";
const std::string MENU_MEMBER_ADDED = "A new member has been added.";
const std::string MENU_EXIT = "Thank you for using the Virtual Library Manager.\n\nEXITING...";
const std::string MENU_ISSUE = "Enter the Member ID and Book ID for issuing:";
const std::string MENU_ISSUE_ISSUE = "Book cannot be issued to this member.";
const std::string MENU_RETURN = "Enter the Member ID and Book ID for returning:";
const std::string MENU_RETURN_ISSUE = "No member found with this ID:";
const std::string MENU_MEMBER_ISSUE = "No members registered in the library.";
const std::string MENU_CURRENT_DATE = "\nThe current date is: ";

// A list representing the main menu options
const std::vector<std::string> MENU = {
    MENU_INFO, MENU_ADD_MEMBER, MENU_ISSUE_BOOK, MENU_RETURN_BOOK,
    MENU_DISPLAY_ALL_BOOKS, MENU_CALCULATE_FINE, MENU_CHANGE_DATE, MENU_MAKE_CHOICE};

// Additional configuration prompts
const std::string CONFIG_CHANGE_DATE = "Enter the new date (format: dd mm yyyy)> ";
const std::string CONFIG_START = "Starting Virtual Library Manager...\n";
const std::string CONFIG_ERROR_CSV = "No CSV file found in the root folder or its subdirectories.";
const std::string CONFIG_ERROR_ROOT = "No CSV file found in the root folder.";

// Error messages for input failiure
const std::string ERROR_UNKNOWN = "An unknown error occurred. Try again.\n\n";
const std::string ERROR_INTEGER = "Invalid input. Please enter a valid integer.\n\n";
const std::string ERROR_RANGE = "The number is not in range.";
const std::string ERROR_PATTERN = "The input does not match the required pattern. Try again.\n\n";
const std::string ERROR_DATE = "Invalid input. Please enter a valid date.";
const std::string ERROR_EOF =  "End of file encountered. Please provide input again.\n";
const std::string ERROR_INPUT_FAILED = "Failed to read input. Please try again.\n";
const std::string ERROR_DATE_DAY =  "Invalid day. Please enter a valid day for the specified month.";
const std::string ERROR_DATE_MONTH =  "Invalid month. Please enter a month between 1 and 12.";
const std::string ERROR_DATE_YEAR = "Invalid year. Please enter a year between 1900 and 2100.";

// Reads an integer input from the user, ensuring it is within a specified range.
int getUserInt(std::string message, int min, int max)
{
    int number = 0;
    while (true)
    {
        try
        {
            // Display the message and get input
            std::cout << message;
            std::cin.clear();        // Clearing any error flags
            std::cin >> number;      // Reading input
            isLastInputLine = false; // Resetting line input flag

            // Check for input failure (non-integer values)
            if (std::cin.fail())
            {
                std::cin.clear(); // Clear the error flag
                // Ignore remaining input till next line
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error(ERROR_INTEGER);
            }

            // Check if the input is within the specified range
            if (number >= min && number <= max)
            {
                break; // Exit loop if valid
            }
            else
            {
                // Throw an exception if out of range
                throw std::runtime_error(ERROR_RANGE);
            }
        }
        catch (const std::runtime_error &ex)
        {
            // Handling standard runtime errors
            std::cout << std::endl
                      << ex.what() << std::endl;
        }
        catch (...)
        {
            // Catch-all for other exceptions
            std::cout << ERROR_UNKNOWN << std::endl;
        }
    }

    return number; // Return the validated integer
}

// Similar to the first function but takes a vector of strings to display as menu options.
int getUserInt(std::vector<std::string> message, int min, int max)
{
    int number = 0;
    while (true)
    {
        try
        {
            // Print the menu options and get input
            printMenuOptions(message);
            std::cin.clear();        // Clearing any error flags
            std::cin >> number;      // Reading input
            isLastInputLine = false; // Resetting line input flag

            // Check for input failure (non-integer values)
            if (std::cin.fail())
            {
                std::cin.clear(); // Clear the error flag
                // Ignore remaining input till next line
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error(ERROR_INTEGER);
            }

            // Check if the input is within the specified range
            if (number >= min && number <= max)
            {
                break; // Exit loop if valid
            }
            else
            {
                // Throw an exception if out of range
                throw std::runtime_error(ERROR_RANGE);
            }
        }
        catch (const std::runtime_error &ex)
        {
            // Handling standard runtime errors
            std::cout << std::endl
                      << ex.what() << std::endl;
        }
        catch (...)
        {
            // Catch-all for other exceptions
            std::cout << ERROR_UNKNOWN << std::endl;
        }
    }

    return number; // Return the validated integer
}

// Reads a string input from the user that matches a specified regular expression pattern.
std::string getUserString(std::string message, std::regex pattern)
{
    // Check if the last input line should be ignored
    if (!isLastInputLine)
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string userInput;
    while (true)
    {
        std::cout << message;
        std::getline(std::cin, userInput); // Read the complete line as input
        isLastInputLine = true;

        // Handle input read failures
        if (std::cin.fail())
        {
            // Check for end of file condition
            if (std::cin.eof())
            {
                std::cin.clear();
                std::cout <<ERROR_EOF;
            }
            else
            {
                std::cin.clear();
                std::cout <<ERROR_INPUT_FAILED;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Validate input against the regex pattern
        if (std::regex_match(userInput, pattern))
        {
            break; // Break the loop if input matches the pattern
        }
        else
        {
            std::cout << ERROR_PATTERN;
        }
    }
    return userInput; // Return the validated input
}

// Reads a date input from the user and validates it.
Date getUserDate(std::string message)
{
    Date newDate;
    while (true)
    {
        std::cout << message;
        short unsigned int day, month;
        unsigned int year;

        try
        {
            std::cin.clear();
            std::cin >> day >> month >> year; // Read date components
            isLastInputLine = false;

            // Check for input read failure
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error(ERROR_DATE);
            }

            // Set the date components and validate
            newDate.setDay(day);
            newDate.setMonth(month);
            newDate.setYear(year);

            if (newDate.isValid())
            {
                break; // Break the loop if date is valid
            }
            else
            {
                throw std::runtime_error("ERROR_DATE");
            }
        }
        catch (const std::runtime_error &ex)
        {
            // Handle standard runtime errors
            std::cout << "Error: " << ex.what() << "\nTry again.\n\n";
            std::cin.clear();
        }
        catch (...)
        {
            // Catch-all for other exceptions
            std::cout << ERROR_UNKNOWN;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return newDate; // Return the validated Date object
}

// Checks if a Member object has borrowed a specific Book.
bool hasBorrowedThisBook(Member member, Book book)
{
    bool hasBook = false;
    for (Book element : member.getBooksBorrowed())
    {
        // Check if the book ID matches with any in the member's borrowed books
        if (std::stoi(element.getbookID()) == std::stoi(book.getbookID()))
        {
            hasBook = true;
            break; // Break the loop if the book is found
        }
    }
    return hasBook; // Return the result
}

// Prints the menu options to the console.
void printMenuOptions(std::vector<std::string> menu)
{
    // Print the header or title of the menu
    std::cout << std::endl
              << std::endl
              << menu[0];

    // Loop through and print each menu option
    for (long unsigned int i = 1; i < menu.size() - 1; i++)
    {
        std::cout << std::endl
                  << i << ". " << menu[i];
    }

    // Print the footer or the last item of the menu
    std::cout << std::endl
              << std::endl
              << menu[menu.size() - 1];
}

// Handles the main menu interaction and execution of library operations.
void runMenu()
{
    int choice = 1, bookID;
    long unsigned int memberID;

    // Find and load the CSV file containing books
    std::string csvFile = findCsvFile();
    if (csvFile.empty())
    {
        std::cout << CONFIG_ERROR_ROOT << std::endl;
        choice = 0; // Exit if no file is found
    }
    else
    {
        books = readBooksFromCsv(csvFile);
        std::cout << CONFIG_START;
    }

    // Set the current date for library operations
    currentDate = getUserDate(CONFIG_CHANGE_DATE);
    std::cout << MENU_CURRENT_DATE << currentDate.getDate();
    Librarian librarian;

    // Main menu loop
    while (choice != 0)
    {
        // Get the user's choice from the menu
        choice = getUserInt(MENU, 0, 6);

        // Handle different choices
        switch (choice)
        {
        case 1: // Add a new library member
            librarian.addMember();
            std::cout << MENU_MEMBER_ADDED << ", " << MENU_MEMBER_NAME << members[members.size() - 1].getName() << ", " << MENU_MEMBER_ID << members[members.size() - 1].getMemberID();
            break;

        case 2: // Issue a book to a member
            std::cout << MENU_ISSUE << std::endl;
            memberID = getUserInt(MENU_MEMBER_ID, 1, std::numeric_limits<int>::max());
            bookID = getUserInt(MENU_BOOK_ID, 1, books.size());
            if (memberID <= members.size())
                librarian.issueBook(memberID, bookID);
            else
                std::cout << std::endl
                          << MENU_ISSUE_ISSUE;
            break;

        case 3: // Return a borrowed book
            std::cout << MENU_RETURN << std::endl;
            memberID = getUserInt(MENU_MEMBER_ID, 1, std::numeric_limits<int>::max());
            bookID = getUserInt(MENU_BOOK_ID, 1, books.size());
            if (memberID <= members.size())
                librarian.returnBook(memberID, bookID);
            else
                std::cout << std::endl
                          << MENU_RETURN_ISSUE << memberID;
            break;

        case 4: // Display borrowed books of a member
            memberID = getUserInt(MENU_MEMBER_ID, 1, std::numeric_limits<int>::max());
            if (memberID <= members.size())
                librarian.displayBorrowedBooks(memberID);
            else
                std::cout << std::endl
                          << MENU_RETURN_ISSUE << memberID;
            break;

        case 5: // Calculate fine for a member
            memberID = getUserInt(MENU_MEMBER_ID, 1, std::numeric_limits<int>::max());
            if (memberID <= members.size())
                librarian.calcFine(memberID);
            else
                std::cout << std::endl
                          << MENU_RETURN_ISSUE << memberID;
            break;
        case 6: // Change the system current date
            currentDate = getUserDate(CONFIG_CHANGE_DATE);
            std::cout << MENU_CURRENT_DATE << currentDate.getDate();
            break;
        }
    }

    // Print exit message when leaving the menu
    std::cout << MENU_EXIT;
}

// Recursively searches for the first CSV file within the root folder and its subdirectories.
std::string findCsvFile()
{
    // Start from the directory where the executable is located (assuming this is root/bin)
    fs::path execPath = fs::current_path();

    // Navigate up two levels to get to the root directory
    fs::path rootDir = execPath.parent_path();

    // Recursive directory iterator to go through all directories and files from the root
    for (const auto &entry : fs::recursive_directory_iterator(rootDir))
    {
        // Check if the file is a CSV
        if (entry.path().extension() == ".csv")
        {
            // Return the path to the CSV file
            return entry.path().string();
        }
    }

    // Inform the user if no CSV file is found
    std::cout << CONFIG_ERROR_CSV << std::endl;
    return ""; // Return an empty string if no CSV file is found
}

// Reads book data from a CSV file and creates a vector of Book objects.
std::vector<Book> readBooksFromCsv(const std::string &filePath)
{
    std::vector<Book> books;      // Initialize a vector to hold the book objects
    std::ifstream file(filePath); // Open the file
    std::string line;

    // Skip the header line in the CSV file
    std::getline(file, line);

    // Read each line from the file
    while (std::getline(file, line))
    {
        std::istringstream sstream(line); // Use a string stream to parse the line
        std::string field;
        std::vector<std::string> fields; // To hold each field from the line

        // Split the line into fields based on commas
        while (sstream.good())
        {
            std::getline(sstream, field, ',');
            fields.push_back(field);
        }

        // Create a Book object if there are enough fields
        if (fields.size() >= 6)
        {
            int bookID = std::stoi(fields[0]);                  // Convert book ID from string to int
            Book book(bookID, fields[1], fields[3], fields[4]); // Create a Book object
            books.push_back(book);                              // Add the book to the vector
        }
    }

    return books; // Return the vector of books
}
