#ifndef HOTEL_H
#define HOTEL_H

#include "BillingEngine.h"
#include "Guest.h"
#include "Reservation.h"
#include "Room.h"
#include "Service.h"
#include <memory>
#include <string>
#include <vector>

// Hotel is the main controller: it owns every guest, room and
// reservation in the system and exposes the operations the menu in
// main.cpp needs. main.cpp itself contains NO business logic - it only
// reads menu input and calls into Hotel.
class Hotel {
private:
    std::vector<std::shared_ptr<Guest>> guests;
    std::vector<std::unique_ptr<Room>> rooms;      // Hotel owns every room
    std::vector<std::unique_ptr<Reservation>> reservations; // Hotel owns every reservation
    BillingEngine billingEngine;

    void initializeRooms();

public:
    Hotel();

    // ---- Guests ----
    int registerNormalGuest(const std::string& name, const std::string& phone,
                             const std::string& email);
    int registerPremiumGuest(const std::string& name, const std::string& phone,
                              const std::string& email, int initialPoints);
    void viewGuests() const;
    std::shared_ptr<Guest> findGuest(int guestId) const; // throws InvalidGuestException

    // ---- Rooms ----
    void showRoomAvailability() const;
    Room* findRoom(int roomNumber) const; // throws InvalidRoomException

    // ---- Reservations ----
    int createReservation(int guestId, int roomNumber, const std::string& checkIn,
                           const std::string& checkOut);
    void addServiceToReservation(int reservationId, const std::string& serviceType,
                                  int quantity);
    void viewReservation(int reservationId) const;
    void cancelReservation(int reservationId);
    void generateBill(int reservationId);
    Reservation* findReservation(int reservationId) const; // throws InvalidReservationException

    // ---- Reporting ----
    void printHotelSummary() const;
};

#endif // HOTEL_H
