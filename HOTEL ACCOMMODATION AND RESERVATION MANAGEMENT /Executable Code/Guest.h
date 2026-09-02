#ifndef GUEST_H
#define GUEST_H

#include "Person.h"

// Guest virtually inherits Person. A plain Guest is a "Normal Guest":
// no loyalty points, no discount. PremiumGuest (see PremiumGuest.h)
// layers loyalty behaviour on top via multiple inheritance.
class Guest : virtual public Person {
protected:
    int guestId;
    int totalStays;

    static int guestCounter; // used to auto-generate guest IDs

public:
    Guest(const std::string& name, const std::string& phone, const std::string& email);
    virtual ~Guest();

    int getGuestId() const;
    int getTotalStays() const;
    void incrementStays();

    // Overridable so PremiumGuest can show loyalty info alongside it.
    virtual void displayProfile() const;

    // Discount applied at billing time. A normal guest gets none;
    // PremiumGuest overrides this using its loyalty tier.
    virtual double getDiscountRate() const;

    virtual std::string getGuestType() const;
};

#endif // GUEST_H
