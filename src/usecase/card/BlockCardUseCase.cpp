#include "BlockCardUseCase.h"

#include <stdexcept>

void BlockCardUseCase::execute(
    const string& userId,
    const string& cardId,
    bool block
) {
    auto card = _cardRepo->findByCardId(cardId);

    if (!card)
        throw std::runtime_error("Card not found"); //TODO: throw

    if (card->getUserId() != userId)
        throw std::runtime_error("Permission denied"); //TODO: throw

    if (block) card->lock();
    else card->unlock();

    _cardRepo->save(card);
}
