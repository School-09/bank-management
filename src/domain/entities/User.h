#ifndef _USER_H_
#define _USER_H_

#include "Object.h"

#include "Enum.h"
#include "../../infrastructure/utils/FileUtils.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <map>
#include <functional>
using std::vector;
using std::string;

class User : public Object {
protected:
    string _id;
    string _username;
    string _passwordHash;
    string _fullName;
    string _email;
    string _phone;
    Status _status;
    Role _role;

public:
    User() = default;
    virtual ~User() = default;

    User(const string& id,
         const string& username,
         const string& passwordHash,
         const string& fullName,
         const string& email,
         const string& phone,
         Status status,
         Role role)
        : _id(id),
          _username(username),
          _passwordHash(passwordHash),
          _fullName(fullName),
          _email(email),
          _phone(phone),
          _status(status),
          _role(role) {}

public:
    // =========== ABSTRACT / VIRTUAL FUNCTIONS ===========
    virtual string getType() const = 0;

    // =========== GETTER ===========
    string getId() const { return _id; }
    string getUsername() const { return _username; }
    string getPasswordHash() const { return _passwordHash; }
    string getFullName() const { return _fullName; }
    string getEmail() const { return _email; }
    string getPhone() const { return _phone; }
    Status getStatus() const { return _status; }
    Role getRole() const { return _role; }

    // =========== SETTER ===========
    void setId(const string& id) { _id = id; }
    void setUsername(const string& username) { _username = username; }
    void setFullName(const string& fullName) { _fullName = fullName; }
    void setEmail(const string& email) { _email = email; }
    void setPhone(const string& phone) { _phone = phone; }
    void setStatus(const Status& status) { _status = status; }
    void setRole(const Role& role) { _role = role; }

public:
    // =========== PASSWORD MANAGEMENT ===========
    virtual void setPassword(const string& rawPassword);
    virtual bool verifyPassword(const string& rawPassword) const;

    // =========== FILE SERIALIZATION ===========
    virtual string serialize() const = 0;
    virtual void deserialize(const vector<string>& lines) = 0;

    virtual string toString() const override { return "User"; };
};

#endif
