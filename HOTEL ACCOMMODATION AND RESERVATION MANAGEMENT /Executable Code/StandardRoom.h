#ifndef STANDARDROOM_H
#define STANDARDROOM_H

#include "Room.h"

class StandardRoom : public Room {
public:
    StandardRoom(int roomNumber, double basePrice);

    double calculatePrice(int nights, bool weekend, bool seasonal) const override;
    void displayDetails() const override;
    std::string getRoomType() const override;
};

#endif // STANDARDROOM_H
