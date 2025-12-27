#include "CreateCardUseCase.h"
#include "../../domain/entities/DebitCard.h"
#include "../../domain/entities/CreditCard.h"
#include "../../domain/entities/CreditAccount.h"

#include <stdexcept>
#include <cstdlib>

void CreateCardUseCase::execute(
    const string& userId,
    const string& accountId,
    const string& type
) {
    if (type != "DEBIT" && type != "CREDIT")
        throw std::runtime_error("Invalid card type");

    // ===== Debit Card =====
    if (type == "DEBIT") {
        auto acc = _accountRepo->findByAccountId(accountId);
        if (!acc)
            throw std::runtime_error("Account not found");

        if (acc->getUserId() != userId)
            throw std::runtime_error("Permission denied");

        auto card = make_shared<DebitCard>();
        card->setUserId(userId);
        card->setAccountId(accountId);

        _cardRepo->save(card);
        return;
    }

    // ===== Credit Card =====
    if (type == "CREDIT") {
        // 1. Tạo credit account
        auto creditAcc = make_shared<CreditAccount>();
        creditAcc->setId("credit_acc_" + std::to_string(rand()));
        creditAcc->setUserId(userId);
        creditAcc->setCreditLimit(10000000); // demo 10M
        //creditAcc->setUsed(0);

        _accountRepo->save(creditAcc);

        // 2. Tạo credit card
        auto card = make_shared<CreditCard>();
        card->setUserId(userId);
        card->setAccountId(creditAcc->getId());

        _cardRepo->save(card);
    }
}
