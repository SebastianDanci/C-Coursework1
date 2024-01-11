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
    return std::to_string(this->memberId);
}

std::vector<Book> Member::getBooksBorrowed()
{
    return this->booksLoaned;
}

void Member::setBooksBorrowed(Book book)
{
    if (!hasBorrowedThisBook(*this, book))
        booksLoaned.push_back(book);
    else
        this->booksLoaned.erase(this->booksLoaned.begin() + std::stoi(book.getbookID()));
}
