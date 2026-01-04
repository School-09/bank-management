#include "BlockCardUseCase.h"

#include <stdexcept>

Result<void> BlockCardUseCase::execute(
    const string& userId,
    const string& cardId,
    bool block
) {
    auto card = _cardRepo->findByCardId(cardId);

    if (!card)
        return unexpected(ErrorCode::CardNotFound);

    if (card->getUserId() != userId)
        return unexpected(ErrorCode::PermissionDenied);

    if (block) card->lock();
    else card->unlock();

    _cardRepo->save(card);
}
