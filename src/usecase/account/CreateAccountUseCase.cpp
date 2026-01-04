#include "CreateAccountUseCase.h"
#include "../../domain/factories/BaseFactory.h"

Result<shared_ptr<Account>> CreateAccountUseCase::execute( 
    const string& userId,
    const string& typeAcc,
    const string& info
) {
    auto accounts = _accountRepo->findByUserId(userId);
    if (accounts.size() >= 10) {
        return unexpected(ErrorCode::AccountLimitExceeded);
    }
    
    auto acc = BaseFactory<Account>::instance().create(typeAcc, info);

    _accountRepo->save(acc);

    return acc;
}
