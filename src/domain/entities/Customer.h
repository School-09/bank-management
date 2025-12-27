#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include "User.h"


class Customer : public User {
private:
    //vector<string> _accountIds; 
    //vector<string> _cardIds;

public:
    Customer() = default;
    ~Customer() override = default;

    Customer(const string& id,
             const string& username,
             const string& passwordHash,
             const string& fullName,
             const string& email,
             const string& phone,
             Status status,
             Role role)
            : User(id, username, passwordHash, fullName, email, phone, status, Role::CUSTOMER)
    {}

public:
    string getType() const override {
        return "Customer";
    }

public:
    string serialize() const override;
    void deserialize(const vector<string>& lines) override;

    string toString() const override { return "Customer"; };
};

#endif
