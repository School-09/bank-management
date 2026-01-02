#include "DepositUseCase.h"
#include "../../domain/entities/Transaction.h"
#include "../../domain/entities/Deposit.h"
#include "../../domain/factories/TransactionFactory.h"

void DepositUseCase::execute(
    const string& userId,
    const string& toAccountId,
    int amount
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

    auto t = TransactionFactory::instance().create("deposit");
    auto tx = dynamic_pointer_cast<Deposit> (t);

    tx->setUserId(userId);
    tx->setAmount(amount);
    tx->setToAccount(toAccountId);

    _txRepo->save(tx);

    _notifyRepo->save(
        Notification::create(
            userId,
            "Deposit " + std::to_string(amount) + " successfully"
        )
    );
}
