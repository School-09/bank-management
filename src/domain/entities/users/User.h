#ifndef _USER_H_
#define _USER_H_

#include "../Enum.h"
#include "../../visitors/UserVisitor.h"

#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::string;

class User {
protected:
    string _id;
    string _username;
    string _passwordHash;
    string _fullName;
    string _email;
    string _phone;
    Status _status; // TODO: đăng nhập cùng 1 username sai quá 3 lần sẽ khóa, đợi admin mở khóa

public:
    User() = default;
    User(
        string id,
        string username,
        string fullName,
        string email,
        string phone,
        string rawPassword
    );
    virtual ~User() = default;

public: // Visitor Pattern
    virtual void accept(UserVisitor& visitor) = 0;

public:
    // =========== PASSWORD MANAGEMENT ===========
    virtual void setPassword(const string& rawPassword);
    virtual bool verifyPassword(const string& rawPassword) const;

    // =========== FILE SERIALIZATION ===========
    virtual string serialize() const = 0;
    virtual void deserialize(const vector<string>& lines) = 0;

public:
    // =========== GETTER ===========
    string getId() const { return _id; }
    string getUsername() const { return _username; }
    string getPasswordHash() const { return _passwordHash; }
    string getFullName() const { return _fullName; }
    string getEmail() const { return _email; }
    string getPhone() const { return _phone; }
    Status getStatus() const { return _status; }

    // =========== SETTER ===========
    void setId(const string& id) { _id = id; }
    void setUsername(const string& username) { _username = username; }
    void setFullName(const string& fullName) { _fullName = fullName; }
    void setEmail(const string& email) { _email = email; }
    void setPhone(const string& phone) { _phone = phone; }
    void setStatus(const Status& status) { _status = status; }

};

#endif
