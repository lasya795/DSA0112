#include "BillingEngine.h"
#include <iostream>
#include <iomanip>

void BillingEngine::generateBill(Reservation& reservation) const {
    Room* room = reservation.getRoom();

    // 1) Room charge - polymorphic call: BillingEngine has no idea (and
    //    does not care) whether this is a StandardRoom, DeluxeRoom or
    //    SuiteRoom. calculatePrice() already folds in the weekend and
    //    seasonal adjustment for us, per that room type's own formula.
    double roomCharge = room->calculatePrice(reservation.getNights(),
                                              reservation.isWeekendStay(),
                                              reservation.isSeasonalPeak());

    // 2) Service charges - again polymorphic: every service in the list
    //    is accessed only through the Service base class (getCost() ->
    //    calculateCost()), regardless of whether it is food, laundry or
    //    room service.
    double serviceCharge = 0.0;
    for (const auto& service : reservation.getServices()) {
        serviceCharge += service->getCost();
    }

    double subtotal = roomCharge + serviceCharge;

    // 3) Premium guest discount - Guest::getDiscountRate() is virtual;
    //    a Normal Guest returns 0, a PremiumGuest returns its loyalty-
    //    tier-based rate. BillingEngine just calls it, it never checks
    //    "is this guest premium?" directly.
    double discountRate = reservation.getGuest()->getDiscountRate();
    double discountAmount = subtotal * discountRate;

    double finalBill = subtotal - discountAmount;

    reservation.setBillingResult(roomCharge, serviceCharge, discountAmount, finalBill);

    // ---- Itemized invoice ----
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n==================== INVOICE ====================\n";
    std::cout << "Reservation #" << reservation.getReservationId() << "  |  Guest: "
              << reservation.getGuest()->getName() << " ("
              << reservation.getGuest()->getGuestType() << ")\n";
    std::cout << "Room " << room->getRoomNumber() << " (" << room->getRoomType() << ") x "
              << reservation.getNights() << " night(s)"
              << (reservation.isWeekendStay() ? " [weekend]" : "")
              << (reservation.isSeasonalPeak() ? " [seasonal]" : "") << "\n";
    std::cout << "--------------------------------------------------\n";
    std::cout << "  Room Charge          : Rs. " << std::setw(10) << roomCharge << "\n";

    if (reservation.getServices().empty()) {
        std::cout << "  Service Charges      : Rs. " << std::setw(10) << 0.0 << "\n";
    } else {
        for (const auto& service : reservation.getServices()) {
            std::cout << "    + " << std::left << std::setw(28) << service->getDescription()
                       << std::right << "Rs. " << std::setw(10) << service->getCost() << "\n";
        }
        std::cout << "  Service Charges Total: Rs. " << std::setw(10) << serviceCharge << "\n";
    }

    std::cout << "  Subtotal             : Rs. " << std::setw(10) << subtotal << "\n";
    std::cout << "  Premium Discount(" << std::setprecision(0) << (discountRate * 100)
              << "%)  : Rs. " << std::setprecision(2) << std::setw(10) << -discountAmount
              << "\n";
    std::cout << "--------------------------------------------------\n";
    std::cout << "  FINAL BILL           : Rs. " << std::setw(10) << finalBill << "\n";
    std::cout << "==================================================\n";
}
