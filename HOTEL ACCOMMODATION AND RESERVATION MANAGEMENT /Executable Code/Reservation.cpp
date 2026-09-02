#include "Reservation.h"
#include "Exceptions.h"
#include <iostream>
#include <iomanip>

int Reservation::reservationCounter = 5000;

std::string statusToString(ReservationStatus status) {
    switch (status) {
        case ReservationStatus::ACTIVE:      return "ACTIVE";
        case ReservationStatus::CANCELLED:   return "CANCELLED";
        case ReservationStatus::CHECKED_OUT: return "CHECKED-OUT";
    }
    return "UNKNOWN";
}

Reservation::Reservation(std::shared_ptr<Guest> guest, Room* room,
                          const std::string& checkInDate, const std::string& checkOutDate,
                          int nights, bool weekendStay, bool seasonalPeak)
    : reservationId(++reservationCounter),
      guest(guest),
      room(room),
      checkInDate(checkInDate),
      checkOutDate(checkOutDate),
      nights(nights),
      weekendStay(weekendStay),
      seasonalPeak(seasonalPeak),
      roomCharge(0.0),
      serviceCharge(0.0),
      discountAmount(0.0),
      finalBill(0.0),
      billed(false),
      status(ReservationStatus::ACTIVE) {
    if (nights <= 0) {
        throw InvalidDateException("Number of nights must be at least 1.");
    }
}

int Reservation::getReservationId() const { return reservationId; }
std::shared_ptr<Guest> Reservation::getGuest() const { return guest; }
Room* Reservation::getRoom() const { return room; }
const std::string& Reservation::getCheckInDate() const { return checkInDate; }
const std::string& Reservation::getCheckOutDate() const { return checkOutDate; }
int Reservation::getNights() const { return nights; }
bool Reservation::isWeekendStay() const { return weekendStay; }
bool Reservation::isSeasonalPeak() const { return seasonalPeak; }
ReservationStatus Reservation::getStatus() const { return status; }

void Reservation::addService(std::shared_ptr<Service> service) {
    if (status != ReservationStatus::ACTIVE) {
        throw InvalidReservationException(
            "Cannot add services to a reservation that is not active.");
    }
    services.push_back(service);
    billed = false; // adding a service invalidates any previous bill
}

const std::vector<std::shared_ptr<Service>>& Reservation::getServices() const {
    return services;
}

void Reservation::setBillingResult(double roomChargeIn, double serviceChargeIn,
                                    double discountAmountIn, double finalBillIn) {
    roomCharge = roomChargeIn;
    serviceCharge = serviceChargeIn;
    discountAmount = discountAmountIn;
    finalBill = finalBillIn;
    billed = true;
}

bool Reservation::isBilled() const { return billed; }
double Reservation::getRoomCharge() const { return roomCharge; }
double Reservation::getServiceCharge() const { return serviceCharge; }
double Reservation::getDiscountAmount() const { return discountAmount; }
double Reservation::getFinalBill() const { return finalBill; }

void Reservation::cancel() {
    if (status != ReservationStatus::ACTIVE) {
        throw InvalidReservationException(
            "Reservation #" + std::to_string(reservationId) +
            " is already " + statusToString(status) + " and cannot be cancelled.");
    }
    status = ReservationStatus::CANCELLED;
    room->setAvailable(true);
}

void Reservation::checkOut() {
    if (status != ReservationStatus::ACTIVE) {
        throw InvalidReservationException(
            "Reservation #" + std::to_string(reservationId) + " cannot be checked out.");
    }
    status = ReservationStatus::CHECKED_OUT;
    room->setAvailable(true);
}

void Reservation::displaySummary() const {
    std::cout << "  ---- Reservation #" << reservationId << " ----\n"
              << "  Guest        : " << guest->getName() << " (ID " << guest->getGuestId()
              << ", " << guest->getGuestType() << ")\n"
              << "  Room         : " << room->getRoomNumber() << " (" << room->getRoomType()
              << ")\n"
              << "  Check-in     : " << checkInDate << "\n"
              << "  Check-out    : " << checkOutDate << "\n"
              << "  Nights       : " << nights << "\n"
              << "  Weekend Stay : " << (weekendStay ? "Yes" : "No") << "\n"
              << "  Seasonal     : " << (seasonalPeak ? "Yes" : "No") << "\n"
              << "  Status       : " << statusToString(status) << "\n"
              << "  Services     : ";
    if (services.empty()) {
        std::cout << "None\n";
    } else {
        std::cout << "\n";
        for (const auto& s : services) {
            std::cout << "    - " << s->getDescription() << " -> Rs. " << std::fixed
                       << std::setprecision(2) << s->getCost() << "\n";
        }
    }
    if (billed) {
        std::cout << "  Final Bill   : Rs. " << std::fixed << std::setprecision(2)
                   << finalBill << "\n";
    }
}
