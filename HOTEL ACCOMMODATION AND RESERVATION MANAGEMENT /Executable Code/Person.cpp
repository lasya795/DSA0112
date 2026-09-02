#include "Person.h"
#include <iostream>

Person::Person(int personId, const std::string& name, const std::string& phone,
               const std::string& email)
    : personId(personId), name(name), phone(phone), email(email) {}

void Person::displayInfo() const {
    std::cout << "  Person ID : " << personId << "\n"
              << "  Name      : " << name << "\n"
              << "  Phone     : " << phone << "\n"
              << "  Email     : " << email << "\n";
}

int Person::getPersonId() const { return personId; }
const std::string& Person::getName() const { return name; }
const std::string& Person::getPhone() const { return phone; }
const std::string& Person::getEmail() const { return email; }

void Person::setPhone(const std::string& newPhone) { phone = newPhone; }
void Person::setEmail(const std::string& newEmail) { email = newEmail; }

Person::~Person() {}
