#include "CardPaymentUseCase.h"
#include "../transaction/WithdrawUseCase.h"

#include <stdexcept>
#include <format>

void CardPaymentUseCase::execute(
    const string& userId,
    const string& cardId,
    int amount
) {
    auto card = _cardRepo->findByCardId(cardId);
    if (!card)
        throw std::runtime_error("Card not found");

    if (card->getUserId() != userId)
        throw std::runtime_error("Permission denied");

    if (card->isLocked())
        throw std::runtime_error("Card is locked");

    auto withdrawUseCase  = make_shared<WithdrawUseCase>(_accountRepo, _txRepo, _notifyRepo);

    string inf = std::format("{}|{}|{}", userId, card->getAccountId(), amount);
    
    withdrawUseCase->execute(userId, card->getAccountId(), amount, inf);
}
