# Hotel Accommodation and Reservation Management Using C++

A fully working, multi-file C++ console application for a university OOP
project. No placeholders, no stub functions - every menu option is backed
by real logic, and the system has been compiled and exercised end-to-end
(see **Testing** below).

## Project Structure

```
HotelAccommodationReservationSystem/
├── main.cpp                         Menu/UI only - no business logic
├── Exceptions.h                     Custom exception hierarchy
├── DateUtils.h                      Date parsing/validation helpers
├── Person.h / Person.cpp            Top of the virtual-inheritance diamond
├── Guest.h / Guest.cpp              Normal guest (virtual base: Person)
├── LoyaltyAccount.h / .cpp          Loyalty side of a premium guest (virtual base: Person)
├── PremiumGuest.h / .cpp            Multiple inheritance: Guest + LoyaltyAccount
├── Billable.h                       Abstract interface for invoice line items
├── Room.h / Room.cpp                Abstract room base class
├── StandardRoom.h / .cpp            Concrete room type
├── DeluxeRoom.h / .cpp              Concrete room type
├── SuiteRoom.h / .cpp               Concrete room type
├── Service.h / Service.cpp          Abstract service base class
├── FoodService.h / .cpp             Concrete service type
├── LaundryService.h / .cpp          Concrete service type
├── RoomService.h / .cpp             Concrete service type
├── Reservation.h / .cpp             Central business object
├── BillingEngine.h / .cpp           Separate billing calculator
├── Hotel.h / Hotel.cpp              Main controller (guests/rooms/reservations)
└── README.md                        This file
```

## How to Build & Run

### Option A - Apache NetBeans (as requested)

1. Open NetBeans → **File → New Project → C/C++ → C/C++ Application from
   Existing Sources**.
2. For "Existing Sources", browse to and select this
   `HotelAccommodationReservationSystem` folder (the one containing
   `main.cpp`).
3. NetBeans will auto-detect all the `.h`/`.cpp` files in the folder -
   confirm and finish the wizard.
4. Right-click the project → **Properties → Build → C++ Compiler** and set
   the **C++ Standard** to `C++17` (the code uses `std::make_unique`,
   `std::make_shared`, structured bracket-init lists, etc., which need
   C++14/17).
5. Right-click the project → **Clean and Build** (or press **F11**).
6. **Run** the project (**F6**). The console window will show the menu.

If NetBeans's importer nests the files into a `src/` folder or names
things differently, that's fine - it does not change any `#include`
paths, since every file in this project only includes other files by
their bare filename (e.g. `#include "Hotel.h"`), and NetBeans keeps all
sources on the same include path by default.

### Option B - Command line (useful for quickly re-testing outside NetBeans)

```bash
g++ -std=c++17 -Wall -Wextra -o hotel_app *.cpp
./hotel_app
```

(On Windows with MinGW: `g++ -std=c++17 -o hotel_app.exe *.cpp` then run
`hotel_app.exe`.)

## Application Menu

```
============================================
       HOTEL STAY MANAGEMENT SYSTEM
============================================
 1. Register Guest
 2. View Guests
 3. Check Room Availability
 4. Create Reservation
 5. Add Services
 6. View Reservation
 7. Cancel Reservation
 8. Generate Bill
 9. Hotel Summary
10. Exit
============================================
```

The hotel starts pre-loaded with 7 rooms so it can be demoed immediately:
Standard 101/102/103, Deluxe 201/202, Suite 301/302.

Dates are entered as `DD-MM-YYYY` (e.g. `24-12-2026`).

## Main Features Implemented

- **Guest Management** - register Normal or Premium guests; premium guests
  carry loyalty points, a membership tier (Silver/Gold/Platinum), and a
  loyalty-based discount rate.
- **Room Management** - Standard/Deluxe/Suite rooms, each with its own
  amenities and per-night base price; availability flips automatically on
  booking/cancellation.
- **Reservation Management** - unique auto-generated reservation IDs,
  real check-in/check-out date validation, automatic night-count
  calculation via `<ctime>`, cancellation with room release.
- **Hotel Services** - Food/Laundry/Room service, each with its own cost
  formula, addable to any active reservation.
- **Billing** - a dedicated `BillingEngine` computes
  `Room Charge + Service Charges − Premium Discount = Final Bill` and
  prints an itemized invoice.
- **Dynamic Pricing** - each room type applies its own weekend/seasonal
  surcharge percentages (a Suite surcharges more heavily than a Standard
  room); weekend/seasonal status is derived from the real check-in date.
- **Hotel Summary** - total/available/occupied rooms, total guests
  (with premium count), active reservations, billed revenue.
- **Input Validation & Exceptions** - a `HotelException` hierarchy
  (`InvalidGuestException`, `InvalidRoomException`,
  `RoomUnavailableException`, `InvalidDateException`,
  `InvalidReservationException`, `InvalidInputException`) is thrown for
  every bad-input scenario and caught centrally in `main.cpp`, so a bad
  entry never crashes the app or corrupts state.

## OOP Concepts Demonstrated (and where)

| Concept | Where |
|---|---|
| Encapsulation | All classes keep data `private`/`protected` behind accessor methods |
| Inheritance | `Guest`/`LoyaltyAccount` → `Person`; `StandardRoom`/`DeluxeRoom`/`SuiteRoom` → `Room`; `FoodService`/`LaundryService`/`RoomService` → `Service` |
| Multiple inheritance | `PremiumGuest : public Guest, public LoyaltyAccount` |
| Virtual inheritance / virtual base class | `Guest` and `LoyaltyAccount` both `virtual public Person`, so `PremiumGuest` has exactly one `Person` sub-object |
| Abstract classes & pure virtual functions | `Billable`, `Room`, `Service` all have `= 0` methods and are never instantiated directly |
| Function overriding & runtime polymorphism | `calculatePrice()`, `displayDetails()`, `getRoomType()`, `calculateCost()`, `getDiscountRate()`, `displayProfile()` all resolve via base-class pointers/references at runtime |
| Base-class pointers | `Hotel` stores `vector<unique_ptr<Room>>`; `Reservation` stores `Room*`; `BillingEngine` operates on `Room*`/`Service` through their base interfaces |
| Constructors/destructors | Every class; virtual destructors on every polymorphic base (`Person`, `Room`, `Service`, `Billable`) |
| Composition / association | `Reservation` is composed of a `Guest`, associated with a `Room`, and owns its `Service` list |
| STL `vector` | Used throughout `Hotel` and `Reservation` for guests/rooms/reservations/services/amenities |
| Exception handling | Custom `HotelException` hierarchy, thrown from `Hotel`, `Reservation`, `Service`, `DateUtils`, caught centrally in `main.cpp` |
| Dynamic object management / smart pointers | `Hotel` owns rooms via `unique_ptr<Room>` and reservations via `unique_ptr<Reservation>`; guests and services use `shared_ptr` since they're referenced from more than one place |

## Testing Performed

The application was compiled with `g++ -std=c++17 -Wall -Wextra` (zero
warnings) and exercised through a full scripted console session covering:

- Normal guest registration and Premium guest registration
- Room availability listing (before and after booking)
- Successful reservation creation, with automatic night-count and
  weekend/seasonal detection from the check-in date
- Booking a room that's already occupied → `RoomUnavailableException`
- Booking with a non-existent guest ID / room number →
  `InvalidGuestException` / `InvalidRoomException`
- Adding multiple services (Food, Laundry, Room Service) to one
  reservation and viewing the itemized total
- Dynamic pricing verified by hand: e.g. a Standard room at ₹2000/night
  for 3 nights with weekend (+10%) and seasonal (+15%) adjustment
  correctly billed at ₹7500 (₹6000 × 1.25)
- Premium guest discount verified: a Gold-tier (900 points) premium
  guest correctly received a 12% discount (10% tier + 2% premium bonus)
  on their subtotal
- Full itemized bill generation for both a Normal and a Premium guest
- Reservation cancellation, confirming the room becomes available again
- Attempting to cancel an already-cancelled reservation →
  `InvalidReservationException`
- Viewing/billing/cancelling a non-existent reservation ID
- Invalid menu input (letters instead of numbers) handled without
  crashing
- Invalid service quantity (0) rejected
- Invalid dates rejected: bad format, out-of-range day/month, and
  check-out date not after check-in date

All scenarios behaved as expected and the program never crashed or left
the menu loop.

## How to Test It Yourself

A quick walkthrough to reproduce the core flow:

1. **Register Guest** (option 1) → choose `2` for Premium, give it a
   name/phone/email and, say, `900` starting points (this lands in the
   "Gold" tier → 12% discount).
2. **Check Room Availability** (option 3) to see the pre-loaded rooms.
3. **Create Reservation** (option 4) → use the guest ID just printed and
   room `201`, with dates like `18-12-2026` to `20-12-2026`.
4. **Add Services** (option 5) → add a Food Service with quantity `2`.
5. **View Reservation** (option 6) to see the running summary.
6. **Generate Bill** (option 8) to see the itemized invoice with the
   premium discount applied.
7. **Hotel Summary** (option 9) to see updated occupancy/revenue.
8. **Cancel Reservation** (option 7), then check option 3 again to
   confirm the room is available once more.

Try deliberately bad input at each step (a fake guest ID, an already
booked room, a malformed date, a negative quantity) to see the
`ERROR:` messages instead of a crash.
