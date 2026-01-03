#ifndef _TRANSFER_H_
#define _TRANSFER_H_

#include "Transaction.h"

class Transfer : public Transaction {
private:
    string _fromAccountId;
    string _toAccountId;
    
public:
    Transfer() = default;
    Transfer(
        string userId, int amount, 
        string fromAccountId, string toAccountId
    );

public:
    string serialize() const override;
    void deserialize(const vector<string>& lines) override;

public:
    string getFromAccount() const { return _fromAccountId; }
    string getToAccount() const { return _toAccountId; }
    void setFromAccount(const string& fromAccount) { _fromAccountId = fromAccount; }
    void setToAccount(const string& toAccount) { _toAccountId = toAccount; }
};

#endif