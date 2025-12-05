#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Currency.h"
#include <string>
#include <ctime>

using std::string;

namespace domain
{
    class Account
    {
    protected:
        string id;
        string userId;
        double balance;
        Currency currency;
        std::time_t createdAt;

    public:
        // Constructor
        Account(const string &id, const string &userID, Currency curr);
        // Virtual Destructor
        virtual ~Account();
        // Business Logic
        void deposit(double amount);

        virtual bool withdraw(double amount) = 0;

        virtual bool canWithdraw(double amount) const;
        // Getters
        string getId() const;
        string getUserId() const;
        double getBalance() const;
        Currency getCurrency() const;
        std::time_t getCreatedAt() const;
    };
}

#endif // ACCOUNT_H