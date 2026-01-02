#ifndef _CHECKING_ACCOUNT_H_
#define _CHECKING_ACCOUNT_H_

#include "Account.h"

class CheckingAccount : public Account {
private:
    int _balance; // số dư

public:
    CheckingAccount(string userId, int balance);
    ~CheckingAccount() override = default;

public: // Visitor Pattern
    void accept(AccountVisitor& visitor) override;

public:
    bool canWithdraw(int amount) override {
        return _status == Status::ACTIVE && _balance - 50000 >= amount;
    }

    void deposit(int amount) override;
    void withdraw(int amount) override;

    string serialize() const override;
    void deserialize(const vector<string>& lines) override;

public:
    int getBalance() const { return _balance; }
    void setBalance(int balance) { _balance = balance; }
};

#endif