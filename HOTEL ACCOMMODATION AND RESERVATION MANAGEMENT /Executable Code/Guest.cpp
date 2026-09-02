#include "Guest.h"
#include <iostream>

int Guest::guestCounter = 1000; // first guest gets ID 1001, keeps it distinct from array indices

// NOTE: Because Person is a virtual base, it is normally initialized by the
// MOST-DERIVED class. When a plain Guest object is created directly, Guest
// itself is the most-derived class, so it is responsible for constructing
// Person here. When a PremiumGuest is created instead, PremiumGuest becomes
// the most-derived class and this Person(...) call in Guest's initializer
// list is simply ignored in favour of PremiumGuest's own call.
Guest::Guest(const std::string& name, const std::string& phone, const std::string& email)
    : Person(++guestCounter, name, phone, email),
      guestId(guestCounter),
      totalStays(0) {}

Guest::~Guest() {}

int Guest::getGuestId() const { return guestId; }
int Guest::getTotalStays() const { return totalStays; }
void Guest::incrementStays() { totalStays++; }

void Guest::displayProfile() const {
    std::cout << "  ---- Guest Profile (" << getGuestType() << ") ----\n";
    displayInfo();
    std::cout << "  Total Stays : " << totalStays << "\n";
}

double Guest::getDiscountRate() const { return 0.0; }

std::string Guest::getGuestType() const { return "Normal Guest"; }
