#include "PremiumGuest.h"
#include <iostream>

// PremiumGuest is the most-derived class in the diamond, so it alone is
// responsible for constructing the shared virtual base, Person. The
// Person(...) calls inside Guest's and LoyaltyAccount's initializer lists
// are skipped by the compiler for this object; only THIS call runs.
//
// Guest() and LoyaltyAccount() are still listed (with no Person args)
// because every class in the hierarchy must appear in the initializer
// list; their own non-Person members (guestId counter, loyalty points)
// still need to be set up normally.
PremiumGuest::PremiumGuest(const std::string& name, const std::string& phone,
                            const std::string& email, int initialPoints)
    : Person(++Guest::guestCounter, name, phone, email),
      Guest(name, phone, email),
      LoyaltyAccount(name, phone, email, initialPoints) {}

PremiumGuest::~PremiumGuest() {}

void PremiumGuest::displayProfile() const {
    std::cout << "  ---- Guest Profile (" << getGuestType() << ") ----\n";
    displayInfo();
    std::cout << "  Total Stays      : " << totalStays << "\n"
              << "  Loyalty Points   : " << getLoyaltyPoints() << "\n"
              << "  Membership Tier  : " << getMembershipTier() << "\n"
              << "  Discount Rate    : " << (getDiscountRate() * 100) << "%\n";
}

double PremiumGuest::getDiscountRate() const {
    // Loyalty tier discount plus a flat 2% "premium member" bonus.
    return getLoyaltyDiscount() + 0.02;
}

std::string PremiumGuest::getGuestType() const { return "Premium Guest"; }
