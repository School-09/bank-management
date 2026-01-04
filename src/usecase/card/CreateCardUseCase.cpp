#include "CreateCardUseCase.h"
#include "../../domain/entities/accounts/CheckingAccount.h"
#include "../../domain/entities/accounts/CreditAccount.h"
#include "../../domain/factories/BaseFactory.h"
#include "../../infrastructure/utils/StringUtils.h"
#include "../../infrastructure/utils/TimeUtils.h"

#include <stdexcept>
#include <cstdlib>

Result<shared_ptr<Card>> CreateCardUseCase::execute(
    const string& userId,
    const string& accountId,
    const string& typeCard,
    const string& info
) {
    auto cards = _cardRepo->findByAccountId(accountId);

    if (cards.size() >= 5) {
      return unexpected(ErrorCode::CardError);
    }

    string type = StringUtils::normalizeString(typeCard);

    auto acc = _accountRepo->findByAccountId(accountId);
    if (!acc)
      return unexpected(ErrorCode::AccountNotFound);

    if (acc->getUserId() != userId)
      return unexpected(ErrorCode::PermissionDenied);

    // kiểm tra loại card và account
    if (type == "debit") {
        auto checkingAcc = dynamic_pointer_cast<CheckingAccount>(acc);
        if (!checkingAcc) {
           return unexpected(ErrorCode::CardError);
        }
    } else if (type == "credit") {
        auto creditAcc = dynamic_pointer_cast<CreditAccount>(acc);
        if (!creditAcc) {
           return unexpected(ErrorCode::CardError);
        }
    } else {
       return unexpected(ErrorCode::CardError);
    }

    auto card = BaseFactory<Card>::instance().create(type, info);

    _cardRepo->save(card);

    return card;
}
