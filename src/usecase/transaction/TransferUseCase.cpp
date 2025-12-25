#include "TransferUseCase.h"

void TransferUseCase::execute(
    const string& userId,
    const string& fromId,
    const string& toId,
    double amount
) {
    if (amount <= 0)
        throw std::runtime_error("Invalid amount");

    auto from = _accountRepo->findByAccountId(fromId);
    auto to   = _accountRepo->findByAccountId(toId);

    if (!from || !to)
        throw std::runtime_error("Account not found");

    if (from->getUserId() != userId)
        throw std::runtime_error("Permission denied");

    if (from->getBalance() < amount)
        throw std::runtime_error("Insufficient funds");

    from->decreaseBalance(amount);
    to->increaseBalance(amount);

    _accountRepo->save(from);
    _accountRepo->save(to);

    auto tx = Transaction::createTransfer(userId, fromId, toId, amount);
    _txRepo->save(tx);

    _notifyRepo->save(
        Notification::create(
            userId,
            "Transfer " + std::to_string(amount) + " successfully"
        )
    );
}
