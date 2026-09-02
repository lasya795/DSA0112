#include "LaundryService.h"

LaundryService::LaundryService(int quantity, double unitPrice)
    : Service("Laundry Service", unitPrice, quantity) {}

double LaundryService::calculateCost() const {
    // Per-item price, plus a small flat handling fee for the batch.
    const double handlingFee = 50.0;
    return (unitPrice * quantity) + handlingFee;
}

std::string LaundryService::getServiceName() const { return serviceName; }
