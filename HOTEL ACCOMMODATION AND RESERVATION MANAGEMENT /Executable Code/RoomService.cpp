#include "RoomService.h"

RoomService::RoomService(int quantity, double unitPrice)
    : Service("Room Service", unitPrice, quantity) {}

double RoomService::calculateCost() const {
    // Each call-out costs the base price plus a 20% convenience surcharge.
    return (unitPrice * quantity) * 1.20;
}

std::string RoomService::getServiceName() const { return serviceName; }
