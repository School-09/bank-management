#ifndef _ADMIN_H_
#define _ADMIN_H_

#include "User.h"

class Admin : public User {
public:
    Admin(
        string id,
        string username,
        string rawPassword,
        string fullName,
        string email,
        string phone
    );
    ~Admin() override = default;

public: // Visitor Pattern
    void accept(UserVisitor& visitor) override;

public:
    string serialize() const override;
    void deserialize(const vector<string>& lines) override;
};

#endif
