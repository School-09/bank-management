#include "TransferUseCase.h"
#include "../../domain/entities/Transaction.h"
#include "../../domain/entities/Transfer.h"
#include "../../domain/factories/TransactionFactory.h"

void TransferUseCase::execute(
    const string& userId,
    const string& fromAccountId,
    const string& toAccountId,
    int amount
) {
    if (amount <= 0)
        throw std::runtime_error("Invalid amount");

    auto from = _accountRepo->findByAccountId(fromAccountId);
    auto to   = _accountRepo->findByAccountId(toAccountId);

    if (!from || !to)
        throw std::runtime_error("Account not found");

    if (from->getUserId() != userId)
        throw std::runtime_error("Permission denied");

    if (!from->canWithdraw(amount))
        throw std::runtime_error("Can't withdraw");

    from->withdraw(amount);
    to->deposit(amount);
    _accountRepo->save(from);
    _accountRepo->save(to);

    auto t = TransactionFactory::instance().create("transfer");
    auto tx = dynamic_pointer_cast<Transfer> (t);

    tx->setUserId(userId);
    tx->setAmount(amount);
    tx->setFromAccount(fromAccountId);
    tx->setToAccount(toAccountId);

    _notifyRepo->save(
        Notification::create(
            userId,
            "Transfer " + std::to_string(amount) + " successfully"
        )
    );
}
