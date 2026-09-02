#include "DeluxeRoom.h"
#include <iostream>
#include <iomanip>

DeluxeRoom::DeluxeRoom(int roomNumber, double basePrice) : Room(roomNumber, basePrice) {
    amenities = {"Wi-Fi", "Smart TV", "Mini Bar", "Complimentary Breakfast"};
}

double DeluxeRoom::calculatePrice(int nights, bool weekend, bool seasonal) const {
    double subtotal = basePrice * nights;
    lastCalculatedCharge = applyAdjustments(subtotal, weekend, seasonal, 0.12, 0.18);
    return lastCalculatedCharge;
}

void DeluxeRoom::displayDetails() const {
    std::cout << "  Room " << roomNumber << " - Deluxe Room\n"
              << "  Base Price : Rs. " << std::fixed << std::setprecision(2)
              << basePrice << " / night\n"
              << "  Status     : " << (available ? "Available" : "Occupied") << "\n"
              << "  Amenities  : ";
    for (size_t i = 0; i < amenities.size(); ++i) {
        std::cout << amenities[i] << (i + 1 < amenities.size() ? ", " : "\n");
    }
}

std::string DeluxeRoom::getRoomType() const { return "Deluxe"; }
