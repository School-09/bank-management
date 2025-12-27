#include "WithdrawUseCase.h"


void WithdrawUseCase::execute(
    const string& userId,
    const string& accountId,
    double amount
) {
    if (amount <= 0)
        throw std::runtime_error("Invalid amount");

    auto acc = _accountRepo->findByAccountId(accountId);
    if (!acc)
        throw std::runtime_error("Account not found");

    if (acc->getUserId() != userId)
        throw std::runtime_error("Permission denied");

    acc->decreaseBalance(amount);
    _accountRepo->save(acc);

    auto tx = Transaction::createWithdraw(userId, accountId, amount);
    _txRepo->save(tx);

    _notifyRepo->save(
        Notification::create(
            userId,
            "Withdraw " + std::to_string(amount) + " successfully"
        )
    );
}
