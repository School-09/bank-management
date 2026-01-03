#include "DepositUseCase.h"
#include "../../domain/entities/transactions/Transaction.h"
#include "../../domain/entities/transactions/Deposit.h"
#include "../../domain/factories/BaseFactory.h"

#include <memory>

void DepositUseCase::execute(
    const string& userId,
    const string& toAccountId,
    int amount,
    const string& inf
) {
    if (amount <= 0)
        throw std::runtime_error("Invalid amount");

    auto acc = _accountRepo->findByAccountId(toAccountId);
    if (!acc)
        throw std::runtime_error("Account not found");

    if (acc->getUserId() != userId)
        throw std::runtime_error("Permission denied");

    acc->deposit(amount);
    _accountRepo->save(acc);

    auto tx = BaseFactory<Transaction>::instance().create("deposit", inf);

    _txRepo->save(tx);

    _notifyRepo->save(
        std::make_shared<Notification>(
            userId,
            "Deposit " + std::to_string(amount) + " successfully"
        )
    );
}
