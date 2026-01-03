#include "WithdrawUseCase.h"
#include "../../domain/entities/transactions/Transaction.h"
#include "../../domain/entities/transactions/Withdraw.h"
#include "../../domain/factories/BaseFactory.h"

void WithdrawUseCase::execute(
    const string& userId,
    const string& fromAccountId,
    int amount,
    const string& inf
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

    auto tx = BaseFactory<Transaction>::instance().create("withdraw", inf);

    _txRepo->save(tx);

    _notifyRepo->save(
        std::make_shared<Notification>(
            userId,
            "Withdraw " + std::to_string(amount) + " successfully"
        )
    );
}
