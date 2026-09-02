#include "FoodService.h"

FoodService::FoodService(int quantity, double unitPrice)
    : Service("Food Service", unitPrice, quantity) {}

double FoodService::calculateCost() const {
    // Straightforward: per-meal price times number of meals ordered.
    return unitPrice * quantity;
}

std::string FoodService::getServiceName() const { return serviceName; }
