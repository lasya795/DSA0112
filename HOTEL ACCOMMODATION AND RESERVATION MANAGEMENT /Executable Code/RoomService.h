#ifndef ROOMSERVICE_H
#define ROOMSERVICE_H

#include "Service.h"

class RoomService : public Service {
public:
    // quantity = number of times room service was called
    explicit RoomService(int quantity, double unitPrice = 200.0);

    double calculateCost() const override;
    std::string getServiceName() const override;
};

#endif // ROOMSERVICE_H
