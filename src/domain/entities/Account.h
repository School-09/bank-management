#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include "Enum.h"
#include "../visitors/AccountVisitor.h"

#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

class Account {
protected:
    string _id;
    string _userId;
    string _createdAt;
    Status _status;

public:
    Account(string id, string userId);
    virtual ~Account() = default;

public: // Visitor Pattern
    virtual void accept(AccountVisitor& visitor) = 0;

public:
    virtual bool canWithdraw(int amount) = 0;
    virtual void deposit(int mount) = 0;
    virtual void withdraw(int amount) = 0;

    // =========== FILE SERIALIZATION ===========
    virtual string serialize() const = 0;
    virtual void deserialize(const vector<string>& lines) = 0;

public:
    // =========== GETTER ===========
    string getId() const { return _id; }
    string getUserId() const { return _userId; }
    string getCreatedAt() const { return _createdAt; }
    bool isActive() const { return _status == Status::ACTIVE; }

    // =========== SETTER ===========
    void setId(const string& id) { _id = id; }
    void setUserId(const string& userId) { _userId = userId; }
    void setCreatedAt(const string& createdAt) { _createdAt = createdAt; }
    void deActivate() { _status = Status::LOCKED; }
    void activate() { _status = Status::ACTIVE; }

};

#endif