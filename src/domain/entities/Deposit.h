#ifndef _DEPOSIT_H_
#define _DEPOSIT_H_

#include "Transaction.h"

class Deposit : public Transaction {
private:
    string _toAccountId;

public:
    Deposit(
        string userId, int amount, 
        string toAccountId
    );

public:
    string serialize() const override;
    void deserialize(const vector<string>& lines) override;

public:
    string getToAccount() const { return _toAccountId; }
    void setToAccount(const string& toAccount) { _toAccountId = toAccount; }

};

#endif