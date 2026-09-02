#include "Service.h"

Service::Service(const std::string& serviceName, double unitPrice, int quantity)
    : serviceName(serviceName), unitPrice(unitPrice), quantity(quantity) {
    if (quantity <= 0) {
        throw InvalidInputException("Service quantity must be a positive number.");
    }
}

Service::~Service() {}

double Service::getCost() const { return calculateCost(); }

std::string Service::getDescription() const {
    return getServiceName() + " x " + std::to_string(quantity);
}

int Service::getQuantity() const { return quantity; }

void Service::setQuantity(int newQuantity) {
    if (newQuantity <= 0) {
        throw InvalidInputException("Service quantity must be a positive number.");
    }
    quantity = newQuantity;
}
