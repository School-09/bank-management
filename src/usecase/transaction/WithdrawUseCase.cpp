#include "WithdrawUseCase.h"
#include "../../domain/entities/Transaction.h"
#include "../../domain/entities/Withdraw.h"
#include "../../domain/factories/TransactionFactory.h"

void WithdrawUseCase::execute(
    const string& userId,
    const string& fromAccountId,
    int amount
) {
    if (amount <= 0)
        throw std::runtime_error("Invalid amount");

    auto acc = _accountRepo->findByAccountId(fromAccountId);
    if (!acc)
        throw std::runtime_error("Account not found");

    if (acc->getUserId() != userId)
        throw std::runtime_error("Permission denied");

    if (!acc->canWithdraw(amount))
        throw std::runtime_error("Can't withdraw");
    
    acc->withdraw(amount);
    _accountRepo->save(acc);

    auto t = TransactionFactory::instance().create("withdraw");
    auto tx = dynamic_pointer_cast<Withdraw> (t);

    tx->setUserId(userId);
    tx->setAmount(amount);
    tx->setFromAccount(fromAccountId);

    _txRepo->save(tx);

    _notifyRepo->save(
        Notification::create(
            userId,
            "Withdraw " + std::to_string(amount) + " successfully"
        )
    );
}
