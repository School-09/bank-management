#include "DepositUseCase.h"
#include "../../domain/entities/transactions/Transaction.h"
#include "../../domain/factories/BaseFactory.h"

#include <memory>

void DepositUseCase::execute(
    const string& userId,
    const string& toAccountId,
    int amount,
    const string& info
) {
    if (amount <= 0)
        throw std::runtime_error("Invalid amount"); //TODO: throw

    auto acc = _accountRepo->findByAccountId(toAccountId);
    if (!acc)
        throw std::runtime_error("Account not found"); //TODO: throw

    if (acc->getUserId() != userId)
        throw std::runtime_error("Permission denied"); //TODO: throw

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
