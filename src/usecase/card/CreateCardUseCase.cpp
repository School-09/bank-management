#include "CreateCardUseCase.h"
#include "../../domain/entities/accounts/CheckingAccount.h"
#include "../../domain/entities/accounts/CreditAccount.h"
#include "../../domain/factories/BaseFactory.h"
#include "../../infrastructure/utils/StringUtils.h"
#include "../../infrastructure/utils/TimeUtils.h"

#include <stdexcept>
#include <cstdlib>

shared_ptr<Card> CreateCardUseCase::execute(
    const string& userId,
    const string& accountId,
    const string& typeCard,
    const string& info
) {
    auto cards = _cardRepo->findByAccountId(accountId);

    if (cards.size() >= 5) {
        throw std::runtime_error("Each account can have at most 5 cards."); //TODO: throw
    }

    string type = StringUtils::normalizeString(typeCard);

    auto acc = _accountRepo->findByAccountId(accountId);
    if (!acc)
        throw std::runtime_error("Account not found"); //TODO: throw

    if (acc->getUserId() != userId)
        throw std::runtime_error("Permission denied"); //TODO: throw

    // kiểm tra loại card và account
    if (type == "debit") {
        auto checkingAcc = dynamic_pointer_cast<CheckingAccount>(acc);
        if (!checkingAcc) {
            throw std::runtime_error("DebitCard must be linked to a CheckingAccount"); //TODO: throw
        }
    } else if (type == "credit") {
        auto creditAcc = dynamic_pointer_cast<CreditAccount>(acc);
        if (!creditAcc) {
            throw std::runtime_error("CreditCard must be linked to a CreditAccount"); //TODO: throw
        }
    } else {
        throw std::runtime_error("Unsupported card type: " + type); //TODO: throw
    }

    auto card = BaseFactory<Card>::instance().create(type, info);

    _cardRepo->save(card);

    return card;
}
