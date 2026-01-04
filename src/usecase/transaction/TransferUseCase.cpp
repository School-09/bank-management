#include "TransferUseCase.h"
#include "../../domain/entities/transactions/Transaction.h"
#include "../../domain/factories/BaseFactory.h"

void TransferUseCase::execute(
    const string& userId,
    const string& fromAccountId,
    const string& toAccountId,
    int amount,
    const string& info
) {
    if (amount <= 0)
        throw std::runtime_error("Invalid amount"); //TODO: throw

    auto from = _accountRepo->findByAccountId(fromAccountId);
    auto to   = _accountRepo->findByAccountId(toAccountId);

    if (!from || !to)
        throw std::runtime_error("Account not found"); //TODO: throw

    if (from->getUserId() != userId)
        throw std::runtime_error("Permission denied"); //TODO: throw

    if (!from->canWithdraw(amount))
        throw std::runtime_error("Can't withdraw"); //TODO: throw

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
