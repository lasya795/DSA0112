#ifndef LOYALTYACCOUNT_H
#define LOYALTYACCOUNT_H

#include "Person.h"

// LoyaltyAccount also virtually inherits Person - it is the other branch
// of the diamond. On its own it is never instantiated for a guest; it only
// becomes meaningful once combined with Guest inside PremiumGuest, giving
// a premium guest both "is-a Guest" and "has loyalty benefits" behaviour
// without duplicating the shared Person data.
class LoyaltyAccount : virtual public Person {
protected:
    int loyaltyPoints;
    std::string membershipTier; // "Silver", "Gold", "Platinum"

public:
    LoyaltyAccount(const std::string& name, const std::string& phone,
                    const std::string& email, int initialPoints);
    virtual ~LoyaltyAccount();

    void addPoints(int points);
    int getLoyaltyPoints() const;
    const std::string& getMembershipTier() const;

    // Discount purely from the loyalty side of things, based on tier.
    double getLoyaltyDiscount() const;

private:
    std::string computeTier(int points) const;
};

#endif // LOYALTYACCOUNT_H
