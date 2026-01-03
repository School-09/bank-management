#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <regex>
#include <map>
#include <functional>
using std::string;
using std::vector;
using std::shared_ptr, std::make_shared;

class Transaction {
protected:
    string _id;
    string _userId;
    int _amount;
    string _createdAt;

public:
    Transaction() = default;
    Transaction(string id, string userId, int amount);
    virtual ~Transaction() = default;

public:
    virtual string serialize() const;
    virtual void deserialize(const vector<string>& lines);

public:
    // ===== getters =====
    string getId() const { return _id;}
    string getUserId() const { return _userId;}
    int getAmount() const { return _amount;}

    void setId(const string& id) { _id = id; }
    void setUserId(const string& userId) { _userId = userId; }
    void setAmount(int amount) { _amount = amount; }
    void setCreatedAt(const string& createdAt) { _createdAt = createdAt; }
};

#endif
