#include "../include/Member.h"
#include "../include/Book.h"
#include "../include/utils.h"

Member::Member(int memberId, std::string name, std::string adress, std::string email)
{
    setName(name);
    this->memberId = memberId;
    setAdress(adress);
    setEmail(email);
}

Member::Member()
{
}

std::string Member::getMemberID()
{
    return std::to_string(memberId);
}

std::vector<Book> Member::getBooksBorrowed()
{
    return booksLoaned;
}

void Member::setBooksBorrowed(Book book)
{
    if (!hasBorrowedThisBook(*this, book))
    {
        booksLoaned.push_back(book);
    }
    else
        booksLoaned.erase(booksLoaned.begin() + std::stoi(book.getbookID()));
}
