#include "DeleteCardUseCase.h"

#include <stdexcept>


void DeleteCardUseCase::execute(
    const string& userId,
    const string& cardId
) {
    auto card = _cardRepo->findByCardId(cardId);
    if (!card)
        throw std::runtime_error("Card not found");

    if (card->getUserId() != userId)
        throw std::runtime_error("Permission denied");

    // Nếu là credit card → kiểm tra dư nợ
    if (card->getType() == "Credit") {
        auto creditAcc =
            _accountRepo->findByAccountId(card->getLinkedAccountId());

        // if (creditAcc && creditAcc->getUsed() > 0)
        //     throw std::runtime_error("Cannot delete card with outstanding debt");
    }

    _cardRepo->remove(cardId);
}
