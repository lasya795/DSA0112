#include "LoyaltyAccount.h"

// Same virtual-base note as Guest.cpp: this Person(...) call only takes
// effect when LoyaltyAccount is instantiated on its own. When used inside
// PremiumGuest, PremiumGuest's constructor initializes Person directly and
// this call is bypassed by the compiler.
LoyaltyAccount::LoyaltyAccount(const std::string& name, const std::string& phone,
                                const std::string& email, int initialPoints)
    : Person(0, name, phone, email), // id unused here; PremiumGuest supplies the real one
      loyaltyPoints(initialPoints),
      membershipTier(computeTier(initialPoints)) {}

LoyaltyAccount::~LoyaltyAccount() {}

void LoyaltyAccount::addPoints(int points) {
    loyaltyPoints += points;
    membershipTier = computeTier(loyaltyPoints);
}

int LoyaltyAccount::getLoyaltyPoints() const { return loyaltyPoints; }
const std::string& LoyaltyAccount::getMembershipTier() const { return membershipTier; }

double LoyaltyAccount::getLoyaltyDiscount() const {
    if (membershipTier == "Platinum") return 0.15;
    if (membershipTier == "Gold") return 0.10;
    return 0.05; // Silver - the minimum for any PremiumGuest
}

std::string LoyaltyAccount::computeTier(int points) const {
    if (points >= 2000) return "Platinum";
    if (points >= 800) return "Gold";
    return "Silver";
}
