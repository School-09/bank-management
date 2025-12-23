#include "CreateAccountUseCase.h"

shared_ptr<Account> CreateAccountUseCase::execute(
    const string& id,
    const string& userId,
    const string& balance,
    const string& type
) {
    if (_repo->exists(id))
        throw std::runtime_error("Account already exists");

    shared_ptr<Account> acc = nullptr;

    if (type == "SAVING") {
        acc = make_shared<SavingAccount> (SavingAccount());
    } 
    else if (type == "CHECKING") {
        acc = make_shared<CheckingAccount> (CheckingAccount());
    } 
    else {
        throw std::runtime_error("Invalid account type");
    }

    acc->setId(id);
    acc->setUserId(userId);
    acc->setBalance(stod(balance));
    acc->setCreatedAt(TimeUtil::toString(time(nullptr)));

    _repo->save(acc);

    return acc;
}
