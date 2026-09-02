#ifndef LAUNDRYSERVICE_H
#define LAUNDRYSERVICE_H

#include "Service.h"

class LaundryService : public Service {
public:
    // quantity = number of clothing items
    explicit LaundryService(int quantity, double unitPrice = 80.0);

    double calculateCost() const override;
    std::string getServiceName() const override;
};

#endif // LAUNDRYSERVICE_H
