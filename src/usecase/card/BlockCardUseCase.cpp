#include "BlockCardUseCase.h"

#include <stdexcept>


void BlockCardUseCase::execute(
    const string& userId,
    const string& cardId,
    bool block
) {
    auto card = _cardRepo->findByCardId(cardId);
    if (!card)
        throw std::runtime_error("Card not found");

    if (card->getUserId() != userId)
        throw std::runtime_error("Permission denied");

    if (block)
        card->block();
    else
        card->unblock();

    _cardRepo->save(card);
}
