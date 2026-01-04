#include "TransferUseCase.h"
#include "../../domain/entities/transactions/Transaction.h"
#include "../../domain/factories/BaseFactory.h"

Result<void> TransferUseCase::execute(
    const string& userId,
    const string& fromAccountId,
    const string& toAccountId,
    int amount,
    const string& info
) {
    if (amount <= 0)
        return unexpected(ErrorCode::InvalidTransactionAmount);

    auto from = _accountRepo->findByAccountId(fromAccountId);
    auto to   = _accountRepo->findByAccountId(toAccountId);

    if (!from || !to)
        return unexpected(ErrorCode::AccountNotFound);

    if (from->getUserId() != userId)
        return unexpected(ErrorCode::PermissionDenied);

    if (!from->canWithdraw(amount))
        return unexpected(ErrorCode::WithdrawalLimitExceeded);

    from->withdraw(amount);
    to->deposit(amount);
    _accountRepo->save(from);
    _accountRepo->save(to);

    auto tx = BaseFactory<Transaction>::instance().create("transfer", info);

    _txRepo->save(tx);

    _notifyRepo->save(
        std::make_shared<Notification>(
            userId,
            "Transfer " + std::to_string(amount) + " successfully"
        )
    );
}
