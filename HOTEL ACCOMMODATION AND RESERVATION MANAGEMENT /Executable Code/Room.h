#ifndef ROOM_H
#define ROOM_H

#include "Billable.h"
#include <string>
#include <vector>

// Abstract Room. StandardRoom / DeluxeRoom / SuiteRoom each provide their
// own pricing rule and amenity list through the pure virtual functions
// below. Every place in the system that deals with a room (Reservation,
// Hotel, BillingEngine) does so through a Room* base-class pointer, so
// adding a brand new room category later would need no changes to that
// code - just a new subclass. That is the runtime-polymorphism payoff.
class Room : public Billable {
protected:
    int roomNumber;
    double basePrice; // price per night before any adjustment
    bool available;
    std::vector<std::string> amenities;

    // Cache of the total charge from the most recent calculatePrice()
    // call, so getCost() (the Billable interface) can report it without
    // needing to be told nights/weekend/season again.
    mutable double lastCalculatedCharge;

public:
    Room(int roomNumber, double basePrice);
    virtual ~Room();

    // Pure virtual - every concrete room type must supply its own pricing
    // formula (a Suite costs more per night than a Standard room, etc).
    virtual double calculatePrice(int nights, bool weekend, bool seasonal) const = 0;

    virtual void displayDetails() const = 0;
    virtual std::string getRoomType() const = 0;

    // Billable interface
    double getCost() const override;
    std::string getDescription() const override;

    int getRoomNumber() const;
    double getBasePrice() const;
    bool isAvailable() const;
    void setAvailable(bool value);
    const std::vector<std::string>& getAmenities() const;

    void printAvailabilityLine() const;

protected:
    // Shared helper so every room subclass applies weekend/seasonal
    // adjustments the same simple way, just with different rates -
    // avoids duplicating the same "if/if" logic three times while still
    // letting each room type set its own percentages.
    double applyAdjustments(double subtotal, bool weekend, bool seasonal,
                             double weekendRate, double seasonalRate) const;
};

#endif // ROOM_H
