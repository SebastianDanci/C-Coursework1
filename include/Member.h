#ifndef MEMBER_H
#define MEMBER_H
#include "Person.h"
#include "Book.h"
#include <string>
#include <vector>

class Member : public Person
{
private:
int memberId;
std::vector<Book> booksLoaned;

public:
// constructor for member class
Member(int memberId, std::string name, std::string adress, std::string email);
std::string getMemberID();
std::vector<Book> getBooksBorrowed();
void setBooksBorrowed(Book book);
};

#endif