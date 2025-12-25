#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include "Enum.h"
#include "../../infrastructure/utils/FileUtils.h"

#include <string>
#include <sstream>
#include <map>
#include <functional>
using std::string;
using std::vector;

class Account {
protected:
    string _id;
    string _userId;
    AccountType _type;
    double _balance;
    bool _active;
    string _createdAt;

public:
    Account() : _balance(0), _active(true) {}

public:
    // getters
    string getId() const { return _id; }
    string getUserId() const { return _userId; }
    double getBalance() const { return _balance; }
    bool isActive() const { return _active; }

    // setters
    void setId(const string& id) { _id = id; }
    void setUserId(const string& userId) { _userId = userId; }
    void setType(AccountType type) { type = type; }
    void setBalance(double balance) { _balance = balance; }
    void setCreatedAt(const string& createdAt) { _createdAt = createdAt; }
    void deactivate() { _active = false; }

    virtual string getType() const = 0;

public:
    void increaseBalance(double amount);
    void decreaseBalance(double amount);
    // business rule
    virtual bool canWithdraw(double amount) const = 0;

    // persistence
    virtual string serialize() const = 0;
    virtual void deserialize(const vector<string>& lines) = 0;
};

#endif