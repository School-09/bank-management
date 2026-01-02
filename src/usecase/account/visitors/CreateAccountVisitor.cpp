#include "CreateAccountVisitor.h"
#include "../../../domain/entities/CheckingAccount.h"
#include "../../../domain/entities/CreditAccount.h"
#include "../../../domain/entities/SavingAccount.h"
#include "../../../infrastructure/converters/IntegerToCurrencyConverter.h"

#include <iostream>
using std::cin, std::cout;

void CreateAccountVisitor::visit(CheckingAccount& checkingAcc) {
    int balance;
    cout << "Enter balance: ";
    cin >> balance;
    cin.ignore();
    checkingAcc.setBalance(balance);
}

void CreateAccountVisitor::visit(CreditAccount& creditAcc) {
    int limit;
    cout << "Enter creditLimit: ";
    cin >> limit;
    cin.ignore();
    creditAcc.setCreditLimit(limit);
}

void CreateAccountVisitor::visit(SavingAccount& savingAcc) {
    int balance;
    cout << "Enter balance: ";
    cin >> balance;
    cin.ignore();
    savingAcc.setBalance(balance);
}
