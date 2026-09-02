#include "Hotel.h"
#include "DateUtils.h"
#include "DeluxeRoom.h"
#include "Exceptions.h"
#include "FoodService.h"
#include "LaundryService.h"
#include "PremiumGuest.h"
#include "RoomService.h"
#include "StandardRoom.h"
#include "SuiteRoom.h"
#include <algorithm>
#include <iomanip>
#include <iostream>

Hotel::Hotel() { initializeRooms(); }

void Hotel::initializeRooms() {
    // A reasonable starting inventory so the app can be demoed immediately.
    rooms.push_back(std::make_unique<StandardRoom>(101, 2000.0));
    rooms.push_back(std::make_unique<StandardRoom>(102, 2000.0));
    rooms.push_back(std::make_unique<StandardRoom>(103, 2200.0));

    rooms.push_back(std::make_unique<DeluxeRoom>(201, 3500.0));
    rooms.push_back(std::make_unique<DeluxeRoom>(202, 3800.0));

    rooms.push_back(std::make_unique<SuiteRoom>(301, 6000.0));
    rooms.push_back(std::make_unique<SuiteRoom>(302, 7000.0));
}

// ---------------- Guests ----------------

int Hotel::registerNormalGuest(const std::string& name, const std::string& phone,
                                const std::string& email) {
    if (name.empty() || phone.empty() || email.empty()) {
        throw InvalidInputException("Name, phone and email cannot be empty.");
    }
    auto guest = std::make_shared<Guest>(name, phone, email);
    guests.push_back(guest);
    return guest->getGuestId();
}

int Hotel::registerPremiumGuest(const std::string& name, const std::string& phone,
                                 const std::string& email, int initialPoints) {
    if (name.empty() || phone.empty() || email.empty()) {
        throw InvalidInputException("Name, phone and email cannot be empty.");
    }
    if (initialPoints < 0) {
        throw InvalidInputException("Loyalty points cannot be negative.");
    }
    auto guest = std::make_shared<PremiumGuest>(name, phone, email, initialPoints);
    guests.push_back(guest); // stored as base Guest pointer - polymorphism at work
    return guest->getGuestId();
}

void Hotel::viewGuests() const {
    if (guests.empty()) {
        std::cout << "  No guests registered yet.\n";
        return;
    }
    std::cout << "\n--------- Registered Guests (" << guests.size() << ") ---------\n";
    for (const auto& guest : guests) {
        // guest->displayProfile() is a virtual call: prints differently
        // for a Guest vs. a PremiumGuest even though both are held here
        // through the same base-class shared_ptr<Guest>.
        guest->displayProfile();
        std::cout << "\n";
    }
}

std::shared_ptr<Guest> Hotel::findGuest(int guestId) const {
    for (const auto& guest : guests) {
        if (guest->getGuestId() == guestId) return guest;
    }
    throw InvalidGuestException("No guest found with ID " + std::to_string(guestId) + ".");
}

// ---------------- Rooms ----------------

void Hotel::showRoomAvailability() const {
    std::cout << "\n--------- Room Availability ---------\n";
    for (const auto& room : rooms) {
        room->printAvailabilityLine();
    }
}

Room* Hotel::findRoom(int roomNumber) const {
    for (const auto& room : rooms) {
        if (room->getRoomNumber() == roomNumber) return room.get();
    }
    throw InvalidRoomException("No room found with number " + std::to_string(roomNumber) + ".");
}

// ---------------- Reservations ----------------

int Hotel::createReservation(int guestId, int roomNumber, const std::string& checkIn,
                              const std::string& checkOut) {
    auto guest = findGuest(guestId); // throws InvalidGuestException if not found

    Room* room = findRoom(roomNumber); // throws InvalidRoomException if not found
    if (!room->isAvailable()) {
        throw RoomUnavailableException(
            "Room " + std::to_string(roomNumber) + " is currently unavailable.");
    }

    int nights = DateUtils::nightsBetween(checkIn, checkOut); // throws InvalidDateException
    bool weekend = DateUtils::isWeekendCheckIn(checkIn);
    bool seasonal = DateUtils::isSeasonalPeak(checkIn);

    auto reservation = std::make_unique<Reservation>(guest, room, checkIn, checkOut, nights,
                                                       weekend, seasonal);
    int id = reservation->getReservationId();

    room->setAvailable(false);
    guest->incrementStays();
    reservations.push_back(std::move(reservation));
    return id;
}

void Hotel::addServiceToReservation(int reservationId, const std::string& serviceType,
                                     int quantity) {
    Reservation* reservation = findReservation(reservationId);

    if (quantity <= 0) {
        throw InvalidInputException("Service quantity must be a positive number.");
    }

    std::shared_ptr<Service> service;
    if (serviceType == "food") {
        service = std::make_shared<FoodService>(quantity);
    } else if (serviceType == "laundry") {
        service = std::make_shared<LaundryService>(quantity);
    } else if (serviceType == "room") {
        service = std::make_shared<RoomService>(quantity);
    } else {
        throw InvalidInputException("Unknown service type: " + serviceType);
    }

    reservation->addService(service); // throws if reservation is not ACTIVE
}

void Hotel::viewReservation(int reservationId) const {
    Reservation* reservation = findReservation(reservationId);
    reservation->displaySummary();
}

void Hotel::cancelReservation(int reservationId) {
    Reservation* reservation = findReservation(reservationId);
    reservation->cancel(); // throws InvalidReservationException if not ACTIVE
    std::cout << "  Reservation #" << reservationId << " cancelled. Room "
              << reservation->getRoom()->getRoomNumber() << " is available again.\n";
}

void Hotel::generateBill(int reservationId) {
    Reservation* reservation = findReservation(reservationId);
    billingEngine.generateBill(*reservation);
}

Reservation* Hotel::findReservation(int reservationId) const {
    for (const auto& reservation : reservations) {
        if (reservation->getReservationId() == reservationId) return reservation.get();
    }
    throw InvalidReservationException(
        "No reservation found with ID " + std::to_string(reservationId) + ".");
}

// ---------------- Reporting ----------------

void Hotel::printHotelSummary() const {
    int totalRooms = static_cast<int>(rooms.size());
    int availableRooms = 0;
    for (const auto& room : rooms) {
        if (room->isAvailable()) availableRooms++;
    }
    int occupiedRooms = totalRooms - availableRooms;

    int activeReservations = 0;
    double totalRevenue = 0.0;
    for (const auto& reservation : reservations) {
        if (reservation->getStatus() == ReservationStatus::ACTIVE) activeReservations++;
        if (reservation->isBilled()) totalRevenue += reservation->getFinalBill();
    }

    int premiumGuests = 0;
    for (const auto& guest : guests) {
        if (guest->getGuestType() == "Premium Guest") premiumGuests++;
    }

    std::cout << "\n============ HOTEL SUMMARY ============\n";
    std::cout << "  Total Rooms         : " << totalRooms << "\n";
    std::cout << "  Available Rooms     : " << availableRooms << "\n";
    std::cout << "  Occupied Rooms      : " << occupiedRooms << "\n";
    std::cout << "  Total Guests        : " << guests.size() << " (Premium: " << premiumGuests
              << ")\n";
    std::cout << "  Total Reservations  : " << reservations.size() << "\n";
    std::cout << "  Active Reservations : " << activeReservations << "\n";
    std::cout << "  Billed Revenue      : Rs. " << std::fixed << std::setprecision(2)
              << totalRevenue << "\n";
    std::cout << "========================================\n";
}
