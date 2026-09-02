#ifndef PERSON_H
#define PERSON_H

#include <string>

// Person is the shared base at the top of the diamond inheritance
// structure: Guest and LoyaltyAccount both derive from Person, and
// PremiumGuest derives from both Guest and LoyaltyAccount.
//
// Guest and LoyaltyAccount both inherit VIRTUALLY from Person so that
// PremiumGuest (which inherits from both) ends up with exactly ONE
// Person sub-object instead of two duplicated copies. This is a genuine
// use of virtual inheritance: a premium guest really is one person with
// two "roles" (a guest role and a loyalty-account role) layered on top.
class Person {
protected:
    int personId;
    std::string name;
    std::string phone;
    std::string email;

public:
    Person(int personId, const std::string& name, const std::string& phone,
           const std::string& email);

    // Polymorphic base - Guest/LoyaltyAccount related classes may want to
    // extend how a person's basic info is shown.
    virtual void displayInfo() const;

    int getPersonId() const;
    const std::string& getName() const;
    const std::string& getPhone() const;
    const std::string& getEmail() const;

    void setPhone(const std::string& phone);
    void setEmail(const std::string& email);

    virtual ~Person();
};

#endif // PERSON_H
