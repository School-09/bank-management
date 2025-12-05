#include "SavingAccount.h"
#include <iostream>

namespace domain
{
    SavingAccount::SavingAccount(string id, string userID, Currency curr)
        : Account(id, userID, curr) {}

    bool SavingAccount::canWithdraw(double amount) const
    {
        if (amount <= 0)
            return false;
        return balance > amount;
    }
    bool SavingAccount::withdraw(double amount)
    {
        if (canWithdraw(amount))
        {
            balance -= amount;
            return true;
        }
        return false;
    }
}
