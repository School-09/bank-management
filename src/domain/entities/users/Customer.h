#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include "User.h"

class Customer : public User {
public:
    Customer() = default;
    Customer(
        string username,
        string fullName,
        string email,
        string phone,
        string rawPassword
    );
    ~Customer() override = default;

public: // Visitor Pattern
    void accept(IUserVisitor& visitor) override;

public:
    string serialize() const override;
    void deserialize(const vector<string>& lines) override;
};

#endif
