#ifndef FOODSERVICE_H
#define FOODSERVICE_H

#include "Service.h"

class FoodService : public Service {
public:
    // quantity = number of meals/orders
    explicit FoodService(int quantity, double unitPrice = 350.0);

    double calculateCost() const override;
    std::string getServiceName() const override;
};

#endif // FOODSERVICE_H
