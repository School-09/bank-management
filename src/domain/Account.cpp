#include "Account.h"
#include <iostream>

namespace domain
{
    // Constructor
    Account::Account(const string &id, const string &userID, Currency curr)
        : id(id), userId(userID), balance(0.0), currency(curr)
    {
        createdAt = std::time(nullptr);
    }

    // Virtual Destructor
    Account::~Account() {}

    // Business Logic
    void Account::deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
        }
        else
        {
            std::cerr << "Số tiền gửi phải là số dương.\n";
        }
    }

    bool Account::canWithdraw(double amount) const
    {
        return amount > 0 && amount <= balance;
    }

    // Getters
    string Account::getId() const
    {
        return id;
    }

    string Account::getUserId() const
    {
        return userId;
    }

    double Account::getBalance() const
    {
        return balance;
    }

    Currency Account::getCurrency() const
    {
        return currency;
    }

    std::time_t Account::getCreatedAt() const
    {
        return createdAt;
    }
} // namespace domain