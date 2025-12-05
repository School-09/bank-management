#ifndef SAVINGACCOUNT_H
#define SAVINGACCOUNT_H

#include "Account.h"

namespace domain{
    class SavingAccount:public Account{
        public:
            SavingAccount(string id, string userID, Currency curr);

            bool canWithdraw(double amount) const override;
            bool withdraw(double amount) override;
    };
}

#endif // SAVINGACCOUNT_H