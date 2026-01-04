#include "WithdrawUseCase.h"
#include "../../domain/entities/transactions/Transaction.h"
#include "../../domain/factories/BaseFactory.h"

void WithdrawUseCase::execute(
    const string& userId,
    const string& fromAccountId,
    int amount,
    const string& info
) {
    if (amount <= 0)
        throw std::runtime_error("Invalid amount"); //TODO: throw

    auto acc = _accountRepo->findByAccountId(fromAccountId);
    if (!acc)
        throw std::runtime_error("Account not found"); //TODO: throw

    if (acc->getUserId() != userId)
        throw std::runtime_error("Permission denied"); //TODO: throw

    if (!acc->canWithdraw(amount))
        throw std::runtime_error("Can't withdraw"); //TODO: throw
    
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
