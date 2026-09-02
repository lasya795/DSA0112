// =====================================================================
// Hotel Accommodation and Reservation Management Using C++
// main.cpp
//
// This file is intentionally "thin": it only prints the menu, reads
// input, does light input-format checking (is this actually a number?)
// and calls into Hotel. All real business logic (guest rules, room
// pricing, billing, cancellation rules, etc.) lives in the other
// classes - see Hotel.cpp, BillingEngine.cpp, Reservation.cpp and the
// Room/Service/Guest hierarchies.
// =====================================================================

#include "Exceptions.h"
#include "Hotel.h"
#include <iostream>
#include <limits>
#include <string>

namespace {

void printBanner() {
    std::cout << "\n============================================\n";
    std::cout << "       HOTEL STAY MANAGEMENT SYSTEM\n";
    std::cout << "============================================\n";
    std::cout << " 1. Register Guest\n";
    std::cout << " 2. View Guests\n";
    std::cout << " 3. Check Room Availability\n";
    std::cout << " 4. Create Reservation\n";
    std::cout << " 5. Add Services\n";
    std::cout << " 6. View Reservation\n";
    std::cout << " 7. Cancel Reservation\n";
    std::cout << " 8. Generate Bill\n";
    std::cout << " 9. Hotel Summary\n";
    std::cout << "10. Exit\n";
    std::cout << "============================================\n";
    std::cout << "Enter your choice: ";
}

// Reads a line of text (allows spaces in names/emails).
std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

// Reads an integer robustly; throws InvalidInputException on bad input
// instead of leaving cin in a broken state.
int readInt(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    try {
        size_t consumed = 0;
        int value = std::stoi(line, &consumed);
        if (consumed != line.size()) {
            throw std::invalid_argument("trailing characters");
        }
        return value;
    } catch (const std::exception&) {
        throw InvalidInputException("\"" + line + "\" is not a valid whole number.");
    }
}

void handleRegisterGuest(Hotel& hotel) {
    std::cout << "\n-- Register Guest --\n";
    std::cout << "1. Normal Guest\n2. Premium Guest\n";
    int type = readInt("Choose guest type: ");

    std::string name = readLine("Name: ");
    std::string phone = readLine("Phone: ");
    std::string email = readLine("Email: ");

    if (type == 1) {
        int id = hotel.registerNormalGuest(name, phone, email);
        std::cout << "  Registered! Guest ID = " << id << "\n";
    } else if (type == 2) {
        int points = readInt("Starting loyalty points: ");
        int id = hotel.registerPremiumGuest(name, phone, email, points);
        std::cout << "  Registered! Premium Guest ID = " << id << "\n";
    } else {
        throw InvalidInputException("Guest type must be 1 (Normal) or 2 (Premium).");
    }
}

void handleCreateReservation(Hotel& hotel) {
    std::cout << "\n-- Create Reservation --\n";
    int guestId = readInt("Guest ID: ");
    int roomNumber = readInt("Room Number: ");
    std::string checkIn = readLine("Check-in date (DD-MM-YYYY): ");
    std::string checkOut = readLine("Check-out date (DD-MM-YYYY): ");

    int reservationId = hotel.createReservation(guestId, roomNumber, checkIn, checkOut);
    std::cout << "  Reservation created! Reservation ID = " << reservationId << "\n";
}

void handleAddServices(Hotel& hotel) {
    std::cout << "\n-- Add Services --\n";
    int reservationId = readInt("Reservation ID: ");

    std::cout << "1. Food Service\n2. Laundry Service\n3. Room Service\n";
    int choice = readInt("Choose service type: ");
    int quantity = readInt("Quantity: ");

    std::string type;
    if (choice == 1) type = "food";
    else if (choice == 2) type = "laundry";
    else if (choice == 3) type = "room";
    else throw InvalidInputException("Service type must be 1, 2 or 3.");

    hotel.addServiceToReservation(reservationId, type, quantity);
    std::cout << "  Service added to reservation #" << reservationId << ".\n";
}

} // namespace

int main() {
    Hotel hotel;
    bool running = true;

    std::cout << "Welcome to the Hotel Stay Management System!\n";
    std::cout << "(Sample rooms 101-103 Standard, 201-202 Deluxe, 301-302 Suite are pre-loaded.)\n";

    while (running) {
        printBanner();
        int choice;
        try {
            choice = readInt("");
        } catch (const InvalidInputException& e) {
            std::cout << "  ERROR: " << e.what() << "\n";
            continue;
        }

        try {
            switch (choice) {
                case 1:
                    handleRegisterGuest(hotel);
                    break;
                case 2:
                    hotel.viewGuests();
                    break;
                case 3:
                    hotel.showRoomAvailability();
                    break;
                case 4:
                    handleCreateReservation(hotel);
                    break;
                case 5:
                    handleAddServices(hotel);
                    break;
                case 6: {
                    int id = readInt("Reservation ID: ");
                    hotel.viewReservation(id);
                    break;
                }
                case 7: {
                    int id = readInt("Reservation ID: ");
                    hotel.cancelReservation(id);
                    break;
                }
                case 8: {
                    int id = readInt("Reservation ID: ");
                    hotel.generateBill(id);
                    break;
                }
                case 9:
                    hotel.printHotelSummary();
                    break;
                case 10:
                    std::cout << "\nThank you for using the Hotel Stay Management System.\n";
                    running = false;
                    break;
                default:
                    std::cout << "  Invalid menu choice. Please enter a number from 1-10.\n";
            }
        } catch (const HotelException& e) {
            // Every domain-specific error (bad guest ID, unavailable room,
            // bad date, etc.) derives from HotelException, so one catch
            // here keeps the menu loop alive no matter what goes wrong.
            std::cout << "  ERROR: " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cout << "  UNEXPECTED ERROR: " << e.what() << "\n";
        }
    }

    return 0;
}
