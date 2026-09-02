#ifndef BILLABLE_H
#define BILLABLE_H

#include <string>

// Billable is a small abstract interface (pure virtual, no data of its
// own) implemented by anything that can appear as a line item on an
// invoice. Room and Service both implement it, which is what lets the
// BillingEngine and invoice-printing code deal with "billable things" in
// general instead of hard-coding "a room and three kinds of service".
class Billable {
public:
    virtual double getCost() const = 0;
    virtual std::string getDescription() const = 0;
    virtual ~Billable() {}
};

#endif // BILLABLE_H
