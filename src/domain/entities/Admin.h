#ifndef _ADMIN_H_
#define _ADMIN_H_

#include "User.h"


class Admin : public User {
public:
    Admin() = default;
    ~Admin() override = default;

    Admin(const string& id,
         const string& username,
         const string& passwordHash,
         const string& fullName,
         const string& email,
         const string& phone,
         Status status,
         Role role)
        : User(id, username, passwordHash, fullName, email, phone, status, Role::ADMIN)
    {}

    string getType() const override {
        return "Admin";
    }

    string serialize() const override;
    void deserialize(const vector<string>& lines) override;

    string toString() const override { return "Admin"; };
};

#endif
