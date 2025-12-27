#ifndef _CREDITACCOUNT_H_
#define _CREDITACCOUNT_H_

#include "Account.h"
#include "../../infrastructure/utils/FileUtils.h"

#include <map>
#include <functional>

// --- Tài khoản tín dụng ---
class CreditAccount : public Account {
private:
    double _creditLimit;
    double _used;

public:
    CreditAccount() : _used(0), _creditLimit(0) {}
    ~CreditAccount() override = default;

public:
    void setCreditLimit(double limit) { _creditLimit = limit; }
    double getCredittLimit() const { return _creditLimit; }

    string getType() const override {
        return "CreditAccount";
    }

public:
    bool canSpend(double amount) const;
    void spend(double amount);
    void pay(double amount);

    bool canWithdraw(double amount) const override {
        return _active && amount <= _balance;
    }

    string serialize() const override;
    void deserialize(const vector<string>& lines) override;

    string toString() const override { return "Credit Account"; };
};

#endif