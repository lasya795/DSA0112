#include "SuiteRoom.h"
#include <iostream>
#include <iomanip>

SuiteRoom::SuiteRoom(int roomNumber, double basePrice) : Room(roomNumber, basePrice) {
    amenities = {"Wi-Fi", "Smart TV", "Mini Bar", "Jacuzzi", "Living Area", "Butler Service"};
}

double SuiteRoom::calculatePrice(int nights, bool weekend, bool seasonal) const {
    double subtotal = basePrice * nights;
    // Suites carry the steepest surcharges - premium demand pricing.
    lastCalculatedCharge = applyAdjustments(subtotal, weekend, seasonal, 0.15, 0.20);
    return lastCalculatedCharge;
}

void SuiteRoom::displayDetails() const {
    std::cout << "  Room " << roomNumber << " - Suite\n"
              << "  Base Price : Rs. " << std::fixed << std::setprecision(2)
              << basePrice << " / night\n"
              << "  Status     : " << (available ? "Available" : "Occupied") << "\n"
              << "  Amenities  : ";
    for (size_t i = 0; i < amenities.size(); ++i) {
        std::cout << amenities[i] << (i + 1 < amenities.size() ? ", " : "\n");
    }
}

std::string SuiteRoom::getRoomType() const { return "Suite"; }
