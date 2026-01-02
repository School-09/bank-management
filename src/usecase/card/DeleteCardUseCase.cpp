#include "DeleteCardUseCase.h"
#include "../../domain/entities/CreditCard.h"
#include "../../domain/entities/CreditAccount.h"

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
    auto creditCard = dynamic_pointer_cast<CreditCard>(card);
    if (creditCard) {
        auto creditAcc =
            dynamic_pointer_cast<CreditAccount> (_accountRepo->findByAccountId(card->getAccountId()));

        if (creditAcc && creditAcc->getUsed() > 0)
            throw std::runtime_error("Cannot delete card with outstanding debt");
    }

    _cardRepo->remove(cardId);
}
