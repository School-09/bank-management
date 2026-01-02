#ifndef _WITHDRAW_H_
#define _WITHDRAW_H_

#include "Transaction.h"

class Withdraw : public Transaction {
private:
    string _fromAccountId;
    
public:
    Withdraw() : Transaction() {}

public:
    string serialize() const override;
    void deserialize(const vector<string>& lines) override;

public:
    string getFromAccount() const { return _fromAccountId; }
    void setFromAccount(const string& fromAccount) { _fromAccountId = fromAccount; }
};

#endif