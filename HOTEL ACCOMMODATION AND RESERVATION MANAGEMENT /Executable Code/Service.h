#ifndef SERVICE_H
#define SERVICE_H

#include "Billable.h"
#include "Exceptions.h"
#include <string>

// Abstract Service. FoodService / LaundryService / RoomService each
// implement calculateCost() with their own pricing rule. Reservation
// stores services as a vector of (shared_ptr to) this base type, so a
// reservation never needs to know which concrete kind of service it is
// holding - it just calls calculateCost() / getDescription() politely
// through the base pointer (runtime polymorphism again).
class Service : public Billable {
protected:
    std::string serviceName;
    double unitPrice;
    int quantity;

public:
    Service(const std::string& serviceName, double unitPrice, int quantity);
    virtual ~Service();

    virtual double calculateCost() const = 0;
    virtual std::string getServiceName() const = 0;

    // Billable interface, expressed in terms of the pure virtuals above.
    double getCost() const override;
    std::string getDescription() const override;

    int getQuantity() const;
    void setQuantity(int newQuantity); // throws InvalidInputException if <= 0
};

#endif // SERVICE_H
