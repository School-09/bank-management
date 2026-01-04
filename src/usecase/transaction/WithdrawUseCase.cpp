#include "WithdrawUseCase.h"
#include "../../domain/entities/transactions/Transaction.h"
#include "../../domain/factories/BaseFactory.h"

Result<void> WithdrawUseCase::execute(
    const string& userId,
    const string& fromAccountId,
    int amount,
    const string& info
) {
    if (amount <= 0)
        return unexpected(ErrorCode::InvalidTransactionAmount);

    auto acc = _accountRepo->findByAccountId(fromAccountId);
    if (!acc)
        return unexpected(ErrorCode::AccountNotFound);

    if (acc->getUserId() != userId)
        return unexpected(ErrorCode::PermissionDenied);

    if (!acc->canWithdraw(amount))
        return unexpected(ErrorCode::WithdrawalLimitExceeded);
    
    acc->withdraw(amount);
    _accountRepo->save(acc);

    auto tx = BaseFactory<Transaction>::instance().create("withdraw", info);

    _txRepo->save(tx);

    _notifyRepo->save(
        std::make_shared<Notification>(
            userId,
            "Withdraw " + std::to_string(amount) + " successfully"
        )
    );
}
