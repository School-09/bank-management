#include "CreateCardUseCase.h"
#include "../../domain/entities/CheckingAccount.h"
#include "../../domain/entities/CreditAccount.h"
#include "../../domain/factories/CardFactory.h"
#include "../../infrastructure/utils/StringUtils.h"
#include "../../infrastructure/utils/TimeUtils.h"

#include <stdexcept>
#include <cstdlib>

shared_ptr<Card> CreateCardUseCase::execute(
    const string& userId,
    const string& accountId,
    const string& typeCard
) {
    auto cards = _cardRepo->findByAccountId(accountId);
    if (cards.size() >= 5) {
        throw std::runtime_error("Each account can have at most 5 cards.");
    }

    string type = StringUtils::normalizeString(typeCard);

    auto acc = _accountRepo->findByAccountId(accountId);
    if (!acc)
        throw std::runtime_error("Account not found");

    if (acc->getUserId() != userId)
        throw std::runtime_error("Permission denied");

    // kiểm tra loại card và account
    if (type == "debitcard") {
        auto checkingAcc = dynamic_pointer_cast<CheckingAccount>(acc);
        if (!checkingAcc) {
            throw std::runtime_error("DebitCard must be linked to a CheckingAccount");
        }
    } else if (type == "creditcard") {
        auto creditAcc = dynamic_pointer_cast<CreditAccount>(acc);
        if (!creditAcc) {
            throw std::runtime_error("CreditCard must be linked to a CreditAccount");
        }
    } else {
        throw std::runtime_error("Unsupported card type: " + type);
    }

    auto card = CardFactory::instance().create(type);

    card->setUserId(userId);
    card->setAccountId(accountId);

    _cardRepo->save(card);

    return card;
}
