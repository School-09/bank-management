#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include "User.h"
#include "../../infrastructure/utils/FileUtils.h"

#include <sstream>
#include <map>
#include <functional>

class Customer : public User {
private:
    //vector<string> _accountIds; 
    //vector<string> _cardIds;

public:
    Customer() = default;

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

    ~Customer() override = default;

public:
    string getType() const override {
        return "Customer";
    }

public:
    string serialize() const override;
    void deserialize(const vector<string>& lines) override;
};

#endif
