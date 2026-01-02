#include "GetAccountVisitor.h"
#include "../../../domain/entities/CheckingAccount.h"
#include "../../../domain/entities/CreditAccount.h"
#include "../../../domain/entities/SavingAccount.h"
#include "../../../infrastructure/converters/IntegerToCurrencyConverter.h"

void GetAccountVisitor::visit(CheckingAccount& checkingAcc) {
    _results.push_back(vector<string>{
        std::to_string(_results.size() + 1),
        "Checking",
        checkingAcc.getId(),
        checkingAcc.getUserId(),
        format("balance={}", 
            IntegerToCurrencyConverter::convert(checkingAcc.getBalance())
        ),
        checkingAcc.getCreatedAt(),
        (checkingAcc.isActive() ? "Active" : "Locked")
    });
}

void GetAccountVisitor::visit(CreditAccount& creditAcc) {
    _results.push_back(vector<string>{
        std::to_string(_results.size() + 1),
        "Credit",
        creditAcc.getId(),
        creditAcc.getUserId(),
        format("limit={}, used={}", 
            IntegerToCurrencyConverter::convert(creditAcc.getCredittLimit()),
            IntegerToCurrencyConverter::convert(creditAcc.getUsed())
        ),
        creditAcc.getCreatedAt(),
        (creditAcc.isActive() ? "Active" : "Locked")
    });
}

void GetAccountVisitor::visit(SavingAccount& savingAcc) {
    _results.push_back(vector<string>{
        std::to_string(_results.size() + 1),
        "Saving",
        savingAcc.getId(),
        savingAcc.getUserId(),
        format("balance={}, rate={}", 
            IntegerToCurrencyConverter::convert(savingAcc.getBalance()),
            IntegerToCurrencyConverter::convert(savingAcc.getInterestRate())
        ),
        savingAcc.getCreatedAt(),
        (savingAcc.isActive() ? "Active" : "Locked")
    });
}
