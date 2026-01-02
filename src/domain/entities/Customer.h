#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include "User.h"

class Customer : public User {
public:
    Customer() = default;
    ~Customer() override = default;

    Customer(const string& id,
             const string& username,
             const string& passwordHash,
             const string& fullName,
             const string& email,
             const string& phone,
             Status status
    ) : User(id, username, passwordHash, fullName, email, phone, status) {}

public: // Visitor Pattern
    void accept(UserVisitor& visitor) override;

public:
    string serialize() const override;
    void deserialize(const vector<string>& lines) override;
};

#endif
