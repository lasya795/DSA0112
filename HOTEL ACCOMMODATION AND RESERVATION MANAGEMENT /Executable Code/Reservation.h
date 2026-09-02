#ifndef RESERVATION_H
#define RESERVATION_H

#include "Guest.h"
#include "Room.h"
#include "Service.h"
#include <memory>
#include <string>
#include <vector>

enum class ReservationStatus { ACTIVE, CANCELLED, CHECKED_OUT };

std::string statusToString(ReservationStatus status);

// Reservation is the CENTRAL object in the whole system: it ties a Guest,
// a Room, a stay period and a list of Services together, and holds the
// billing figures once BillingEngine has computed them.
//
// Ownership design:
//   - guest  : shared_ptr<Guest>  -> shared with Hotel's guest list
//              (a guest can exist / be looked up even without an active
//              reservation, so Reservation only shares ownership, it
//              doesn't own the guest outright)
//   - room   : Room* (raw, non-owning) -> Hotel owns the Room via
//              unique_ptr; a reservation merely ASSOCIATES with a room,
//              it never owns or deletes it.
//   - services : vector<shared_ptr<Service>> -> the reservation is the
//              natural owner of the services attached to it.
class Reservation {
private:
    static int reservationCounter;

    int reservationId;
    std::shared_ptr<Guest> guest;
    Room* room;
    std::string checkInDate;
    std::string checkOutDate;
    int nights;
    bool weekendStay;
    bool seasonalPeak;
    std::vector<std::shared_ptr<Service>> services;

    // Populated by BillingEngine::generateBill()
    double roomCharge;
    double serviceCharge;
    double discountAmount;
    double finalBill;
    bool billed;

    ReservationStatus status;

public:
    Reservation(std::shared_ptr<Guest> guest, Room* room,
                const std::string& checkInDate, const std::string& checkOutDate,
                int nights, bool weekendStay, bool seasonalPeak);

    int getReservationId() const;
    std::shared_ptr<Guest> getGuest() const;
    Room* getRoom() const;
    const std::string& getCheckInDate() const;
    const std::string& getCheckOutDate() const;
    int getNights() const;
    bool isWeekendStay() const;
    bool isSeasonalPeak() const;
    ReservationStatus getStatus() const;

    void addService(std::shared_ptr<Service> service);
    const std::vector<std::shared_ptr<Service>>& getServices() const;

    void setBillingResult(double roomCharge, double serviceCharge,
                           double discountAmount, double finalBill);
    bool isBilled() const;
    double getRoomCharge() const;
    double getServiceCharge() const;
    double getDiscountAmount() const;
    double getFinalBill() const;

    void cancel();
    void checkOut();

    void displaySummary() const;
};

#endif // RESERVATION_H
