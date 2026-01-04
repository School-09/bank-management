#include "DepositUseCase.h"
#include "../../domain/entities/transactions/Transaction.h"
#include "../../domain/factories/BaseFactory.h"

#include <memory>

Result<void> DepositUseCase::execute(
    const string& userId,
    const string& toAccountId,
    int amount,
    const string& info
) {
    if (amount <= 0)
        return unexpected(ErrorCode::InvalidTransactionAmount);

    auto acc = _accountRepo->findByAccountId(toAccountId);
    if (!acc)
        return unexpected(ErrorCode::AccountNotFound);

    if (acc->getUserId() != userId)
        return unexpected(ErrorCode::PermissionDenied);

    acc->deposit(amount);
    _accountRepo->save(acc);

    auto tx = BaseFactory<Transaction>::instance().create("deposit", info);

    _txRepo->save(tx);

    _notifyRepo->save(
        std::make_shared<Notification>(
            userId,
            "Deposit " + std::to_string(amount) + " successfully"
        )
    );
}
