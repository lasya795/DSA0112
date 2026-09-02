#include "Room.h"
#include <iostream>
#include <iomanip>

Room::Room(int roomNumber, double basePrice)
    : roomNumber(roomNumber), basePrice(basePrice), available(true),
      lastCalculatedCharge(0.0) {}

Room::~Room() {}

double Room::getCost() const { return lastCalculatedCharge; }

std::string Room::getDescription() const {
    return "Room " + std::to_string(roomNumber) + " (" + getRoomType() + ")";
}

int Room::getRoomNumber() const { return roomNumber; }
double Room::getBasePrice() const { return basePrice; }
bool Room::isAvailable() const { return available; }
void Room::setAvailable(bool value) { available = value; }
const std::vector<std::string>& Room::getAmenities() const { return amenities; }

double Room::applyAdjustments(double subtotal, bool weekend, bool seasonal,
                               double weekendRate, double seasonalRate) const {
    double total = subtotal;
    if (weekend) total += subtotal * weekendRate;
    if (seasonal) total += subtotal * seasonalRate;
    return total;
}

void Room::printAvailabilityLine() const {
    std::cout << "  [" << (available ? "AVAILABLE  " : "OCCUPIED   ") << "] "
              << "Room " << std::setw(4) << roomNumber << " | " << std::left
              << std::setw(10) << getRoomType() << std::right
              << " | Rs. " << std::fixed << std::setprecision(2) << basePrice
              << " / night\n";
}
