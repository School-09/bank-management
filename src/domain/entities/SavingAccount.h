#ifndef _SAVING_ACCOUNT_H_
#define _SAVING_ACCOUNT_H_

#include "Account.h"


// --- Tài khoản Tiết kiệm (Có lãi, hạn chế rút) ---
class SavingAccount : public Account {
private:
    double _interestRate;   // Lãi suất (%/năm)
    //int _termInMonths;      // Kỳ hạn (6 tháng, 12 tháng)
    //bool _allowEarlyWithdraw; // Cho phép rút trước hạn ko?

public:
    SavingAccount() : _interestRate(0.05) {}
    ~SavingAccount() override = default;

public:
    void setInterestRate(double rate) { _interestRate = rate; }
    double getInterestRate() const { return _interestRate; }

    string getType() const override {
        return "SavingAccount";
    }

public:
    bool canWithdraw(double amount) const override {
        return _active && amount <= _balance;
    }

    string serialize() const override;
    void deserialize(const vector<string>& lines) override;

    string toString() const override { return "Saving Account"; };
};

#endif