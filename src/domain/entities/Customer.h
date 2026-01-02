#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include "User.h"

class Customer : public User {
public:
    Customer(
        string id,
        string username,
        string rawPassword,
        string fullName,
        string email,
        string phone
    );
    ~Customer() override = default;

public: // Visitor Pattern
    void accept(UserVisitor& visitor) override;

public:
    string serialize() const override;
    void deserialize(const vector<string>& lines) override;
};

#endif
