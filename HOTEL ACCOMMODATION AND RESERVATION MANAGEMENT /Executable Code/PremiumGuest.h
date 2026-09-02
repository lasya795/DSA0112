#ifndef PREMIUMGUEST_H
#define PREMIUMGUEST_H

#include "Guest.h"
#include "LoyaltyAccount.h"

// PremiumGuest uses MULTIPLE INHERITANCE from Guest and LoyaltyAccount.
// Because both of those virtually inherit Person, PremiumGuest ends up
// with a single, shared Person sub-object (no duplicate name/phone/email) -
// this is the payoff of the diamond being virtual. PremiumGuest is the
// most-derived class, so IT is responsible for initializing Person
// directly in its constructor's initializer list.
class PremiumGuest : public Guest, public LoyaltyAccount {
public:
    PremiumGuest(const std::string& name, const std::string& phone,
                 const std::string& email, int initialPoints);
    ~PremiumGuest() override;

    // Overrides Guest::displayProfile to also show loyalty info.
    void displayProfile() const override;

    // Combines the loyalty discount with a small extra reward for being
    // premium at all - this is what actually drives the "Premium Guest
    // Discount" line in the final bill.
    double getDiscountRate() const override;

    std::string getGuestType() const override;
};

#endif // PREMIUMGUEST_H
