#include "CreateAccountUseCase.h"
#include "../../domain/factories/BaseFactory.h"

shared_ptr<Account> CreateAccountUseCase::execute( 
    const string& userId,
    const string& typeAcc,
    const string& inf
) {
    auto accounts = _accountRepo->findByUserId(userId);
    if (accounts.size() >= 10) {
        throw std::runtime_error("Each user can have at most 10 accounts.");
    }

    auto acc = BaseFactory<Account>::instance().create(typeAcc, inf);

    _accountRepo->save(acc);

    return acc;
}
