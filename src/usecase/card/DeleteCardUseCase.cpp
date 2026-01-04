#include "DeleteCardUseCase.h"
#include "../../domain/entities/cards/CreditCard.h"
#include "../../domain/entities/accounts/CreditAccount.h"

#include <stdexcept>

Result<void> DeleteCardUseCase::execute(
    const string& userId,
    const string& cardId
) {
    auto card = _cardRepo->findByCardId(cardId);

    if (!card)
        return unexpected(ErrorCode::CardNotFound);

    if (card->getUserId() != userId)
        return unexpected(ErrorCode::PermissionDenied);

    // Nếu là credit card → kiểm tra dư nợ
    auto creditCard = dynamic_pointer_cast<CreditCard>(card);
    if (creditCard) {
        auto creditAcc =
            dynamic_pointer_cast<CreditAccount> (_accountRepo->findByAccountId(card->getAccountId()));

        if (creditAcc && creditAcc->getUsed() > 0)
            return unexpected(ErrorCode::CardError);
    }

    _cardRepo->remove(cardId);
}
