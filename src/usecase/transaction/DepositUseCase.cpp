#include "DepositUseCase.h"


void DepositUseCase::execute(
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

    acc->increaseBalance(amount);
    _accountRepo->save(acc);

    auto tx = Transaction::createDeposit(userId, accountId, amount);
    _txRepo->save(tx);

    _notifyRepo->save(
        Notification::create(
            userId,
            "Deposit " + std::to_string(amount) + " successfully"
        )
    );
    std::cout << 3 << "\n";
}
