#ifndef DELUXEROOM_H
#define DELUXEROOM_H

#include "Room.h"

class DeluxeRoom : public Room {
public:
    DeluxeRoom(int roomNumber, double basePrice);

    double calculatePrice(int nights, bool weekend, bool seasonal) const override;
    void displayDetails() const override;
    std::string getRoomType() const override;
};

#endif // DELUXEROOM_H
