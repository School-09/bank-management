#include "CardPaymentUseCase.h"
#include "../transaction/WithdrawUseCase.h"

#include <stdexcept>
#include <format>

Result<void> CardPaymentUseCase::execute(
    const string& userId,
    const string& cardId,
    int amount
) {
    auto card = _cardRepo->findByCardId(cardId);

    if (!card)
        return unexpected(ErrorCode::CardNotFound);

    if (card->getUserId() != userId)
        return unexpected(ErrorCode::PermissionDenied);

    if (card->isLocked())
        return unexpected(ErrorCode::CardLocked);

    auto withdrawUseCase  = make_shared<WithdrawUseCase>(_accountRepo, _txRepo, _notifyRepo);

    string info = std::format("{}|{}|{}", userId, card->getAccountId(), amount);
    
    withdrawUseCase->execute(userId, card->getAccountId(), amount, info);
}
