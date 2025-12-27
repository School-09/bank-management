#ifndef _CHECKING_ACCOUNT_H_
#define _CHECKING_ACCOUNT_H_

#include "Account.h"
#include "../../infrastructure/utils/FileUtils.h"

#include <map>
#include <functional>

// --- Tài khoản Thanh toán (Dùng thường xuyên) ---
class CheckingAccount : public Account {
private:
    double _overdraftLimit; // Hạn mức rút tiền (âm)

public:
    CheckingAccount() : _overdraftLimit(0) {}
    ~CheckingAccount() override = default;

public:
    void setOverdraftLimit(double limit) { _overdraftLimit = limit; }
    double getOverdraftLimit() const { return _overdraftLimit; }

    string getType() const override {
        return "CheckingAccount";
    }

public:
    bool canWithdraw(double amount) const override {
        return _active && (_balance + _overdraftLimit) >= amount;
    }

    string serialize() const override;
    void deserialize(const vector<string>& lines) override;

    string toString() const override { return "Checking Account"; };
};

#endif