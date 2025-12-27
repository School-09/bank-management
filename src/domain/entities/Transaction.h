#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_

#include "Object.h"

#include "../../infrastructure/utils/FileUtils.h"
#include "../../infrastructure/utils/TimeUtils.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <memory>
using std::string;
using std::vector;
using std::shared_ptr, std::make_shared;

class Transaction : public Object{
private:
    string _id;
    string _fromAccountId;   // rỗng với deposit
    string _toAccountId;     // rỗng với withdraw
    string _userId;
    double _amount;
    string _createdAt;
    string _type;

public:
    Transaction() = default;

    // ===== Factory methods (IMPORTANT) =====
    static shared_ptr<Transaction> createDeposit(
        const string& userId,
        const string& accountId,
        double amount
    );

    static shared_ptr<Transaction> createWithdraw(
        const string& userId,
        const string& accountId,
        double amount
    );

    static shared_ptr<Transaction> createTransfer(
        const string& userId,
        const string& fromId,
        const string& toId,
        double amount
    );

public:
    // ===== getters =====
    string getId() const { return _id;}
    string getUserId() const { return _userId;}
    string getType() const { return _type;}
    double getAmount() const { return _amount;}

    // ===== persistence =====
    string serialize() const;
    void deserialize(const vector<string>& lines);

    string toString() const override { return "Transaction"; };
};

#endif
