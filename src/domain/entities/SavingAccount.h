#ifndef _SAVING_ACCOUNT_H_
#define _SAVING_ACCOUNT_H_

#include "Account.h"  

class SavingAccount : public Account {
private:
    int _balance;           // số dư
    float _interestRate;    // Lãi suất (%/ngày) ->  giả sử

public:
    SavingAccount(string userId, int balance);
    ~SavingAccount() override = default;

public: // Visitor Pattern
    void accept(AccountVisitor& visitor) override;

public:
    bool canWithdraw(int amount) override {
        return _status == Status::ACTIVE && getBalance() - 50000 >= amount;
    }

    void deposit(int amount) override;
    void withdraw(int amount) override;

    string serialize() const override;
    void deserialize(const vector<string>& lines) override;

public:
    void updateBalance();
    int getBalance();
    float getInterestRate() const { return _interestRate; }

    void setBalance(int balance) { _balance = balance; }
    void setInterestRate(float rate) { _interestRate = rate; } 

};

#endif