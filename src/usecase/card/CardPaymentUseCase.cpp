#include "CardPaymentUseCase.h"
#include "../../domain/entities/DebitCard.h"
#include "../../domain/entities/CreditCard.h"
#include "../../domain/entities/CreditAccount.h"
#include <stdexcept>

void CardPaymentUseCase::execute(
    const string& userId,
    const string& cardId,
    double amount
) {
    if (amount <= 0)
        throw std::runtime_error("Invalid amount");

    auto card = _cardRepo->findByCardId(cardId);
    if (!card)
        throw std::runtime_error("Card not found");

    if (card->getUserId() != userId)
        throw std::runtime_error("Permission denied");

    if (card->isBlocked())
        throw std::runtime_error("Card is blocked");

    // ===== Debit Card =====
    if (card->getType() == "Debit") {
        auto acc =
            _accountRepo->findByAccountId(card->getLinkedAccountId());

        if (!acc)
            throw std::runtime_error("Linked account not found");

        if (acc->getBalance() < amount)
            throw std::runtime_error("Insufficient funds");

        acc->decreaseBalance(amount);
        _accountRepo->save(acc);

        auto tx = Transaction::createWithdraw(userId, acc->getId(), amount);
        _txRepo->save(tx);

        return;
    }

    // ===== Credit Card =====
    if (card->getType() == "Credit") {
        std::shared_ptr<Account> acc = _accountRepo->findByAccountId(card->getLinkedAccountId());

        auto creditAcc = std::dynamic_pointer_cast<CreditAccount>(acc);

        if (!creditAcc)
            throw std::runtime_error("Credit account not found");

        if (!creditAcc->canSpend(amount))
            throw std::runtime_error("Credit limit exceeded");

        creditAcc->spend(amount);
        _accountRepo->save(creditAcc);

        auto tx = Transaction::createWithdraw(userId, creditAcc->getId(), amount);
        _txRepo->save(tx);
    }
}
