#ifndef _CREDIT_ACCOUNT_H_
#define _CREDIT_ACCOUNT_H_

#include "Account.h"

class CreditAccount : public Account {
private:
    int _creditLimit; // hạn mức sử dụng
    int _used; // đã dùng

public:
    CreditAccount(string userId, int creditLimit);
    ~CreditAccount() override = default;

public: // Visitor Pattern
    void accept(AccountVisitor& visitor) override;

public:
    bool canWithdraw(int amount) override {
        return _status == Status::ACTIVE && _creditLimit >= amount + _used;
    }

    void deposit(int amount) override;
    void withdraw(int amount) override;

    string serialize() const override;
    void deserialize(const vector<string>& lines) override;

public:
    int getCredittLimit() const { return _creditLimit; }
    int getUsed() const { return _used; }
    void setCreditLimit(int limit) { _creditLimit = limit; }
};

#endif