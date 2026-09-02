#ifndef BILLINGENGINE_H
#define BILLINGENGINE_H

#include "Reservation.h"

// BillingEngine is deliberately kept separate from Reservation/Hotel: its
// only job is to turn a Reservation into money. It never needs to know
// whether a room is a StandardRoom or a Suite, or whether a service is
// Food/Laundry/RoomService - it always talks to Room* and Service (via
// Billable/virtual calculateCost()) through their base-class interfaces,
// so it never has a big if/else or switch over concrete types.
//
//   Final Bill = RoomCharge (incl. weekend/seasonal adjustment)
//              + ServiceCharges
//              - PremiumGuestDiscount
class BillingEngine {
public:
    // Computes the full bill for a reservation, stores the result back
    // into the reservation, and prints an itemized invoice.
    void generateBill(Reservation& reservation) const;
};

#endif // BILLINGENGINE_H
