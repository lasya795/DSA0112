#include "StandardRoom.h"
#include <iostream>
#include <iomanip>

StandardRoom::StandardRoom(int roomNumber, double basePrice) : Room(roomNumber, basePrice) {
    amenities = {"Wi-Fi", "TV", "Attached Bathroom"};
}

double StandardRoom::calculatePrice(int nights, bool weekend, bool seasonal) const {
    double subtotal = basePrice * nights;
    // Standard rooms carry the smallest surcharge rates in the hotel.
    lastCalculatedCharge = applyAdjustments(subtotal, weekend, seasonal, 0.10, 0.15);
    return lastCalculatedCharge;
}

void StandardRoom::displayDetails() const {
    std::cout << "  Room " << roomNumber << " - Standard Room\n"
              << "  Base Price : Rs. " << std::fixed << std::setprecision(2)
              << basePrice << " / night\n"
              << "  Status     : " << (available ? "Available" : "Occupied") << "\n"
              << "  Amenities  : ";
    for (size_t i = 0; i < amenities.size(); ++i) {
        std::cout << amenities[i] << (i + 1 < amenities.size() ? ", " : "\n");
    }
}

std::string StandardRoom::getRoomType() const { return "Standard"; }
