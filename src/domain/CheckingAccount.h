#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "Account.h"

namespace domain
{
    class CheckingAccount : public Account
    {
    private:
        double overdraftLimit;

    public:
        CheckingAccount(string id, string userID, Currency curr, double overdraftLimit);

        bool canWithdraw(double amount) const override;
        bool withdraw(double amount) override;
        double getOverdraftLimit() const;
    };
}

#endif // CHECKINGACCOUNT_H