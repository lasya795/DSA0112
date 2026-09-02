#ifndef SUITEROOM_H
#define SUITEROOM_H

#include "Room.h"

class SuiteRoom : public Room {
public:
    SuiteRoom(int roomNumber, double basePrice);

    double calculatePrice(int nights, bool weekend, bool seasonal) const override;
    void displayDetails() const override;
    std::string getRoomType() const override;
};

#endif // SUITEROOM_H
