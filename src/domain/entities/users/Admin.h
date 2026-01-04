#ifndef _ADMIN_H_
#define _ADMIN_H_

#include "User.h"

class Admin : public User {
public:
    Admin() = default;
    Admin(
        string username,
        string fullName,
        string email,
        string phone,
        string rawPassword
    );
    ~Admin() override = default;

public: // Visitor Pattern
    void accept(IUserVisitor& visitor) override;

public:
    string serialize() const override;
    void deserialize(const vector<string>& lines) override;
};

#endif
