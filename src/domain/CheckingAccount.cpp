#include "CheckingAccount.h"
#include <iostream>

namespace domain
{
    CheckingAccount::CheckingAccount(string id, string userID, Currency curr, double overdraftLimit)
        : Account(id, userID, curr), overdraftLimit(overdraftLimit) {}

    bool CheckingAccount::canWithdraw(double amount) const
    {
        if (amount <= 0)
            return false;
        return balance + overdraftLimit >= amount;
    }

    bool CheckingAccount::withdraw(double amount)
    {
        if (canWithdraw(amount))
        {
            balance -= amount;
            return true;
        }
        return false;
    }
    double CheckingAccount::getOverdraftLimit() const
    {
        return overdraftLimit;
    }
}