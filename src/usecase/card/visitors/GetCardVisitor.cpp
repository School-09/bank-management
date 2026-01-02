#include "GetCardVisitor.h"
#include "../../../domain/entities/DebitCard.h"
#include "../../../domain/entities/CreditCard.h"

void GetCardVisitor::visit(DebitCard& debitCard) {
    _results.push_back(vector<string>{
        std::to_string(_results.size() + 1),
        "Debit Card",
        debitCard.getId(),
        debitCard.getUserId(),
        debitCard.getAccountId(),
        debitCard.getCardNumber(),
        debitCard.getCreatedAt(),
        debitCard.getExpiredAt(),
        (!debitCard.isLocked() ? "Active" : "Locked")
    });
}

void GetCardVisitor::visit(CreditCard& creditCard) {
    _results.push_back(vector<string>{
        std::to_string(_results.size() + 1),
        "Credit Card",
        creditCard.getId(),
        creditCard.getUserId(),
        creditCard.getAccountId(),
        creditCard.getCardNumber(),
        creditCard.getCreatedAt(),
        creditCard.getExpiredAt(),
        (!creditCard.isLocked() ? "Active" : "Locked")
    });
}
