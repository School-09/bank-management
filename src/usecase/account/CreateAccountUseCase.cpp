#include "CreateAccountUseCase.h"
#include "../../domain/factories/AccountFactory.h"
#include "../../infrastructure/utils/StringUtils.h"
#include "../../infrastructure/utils/TimeUtils.h"

shared_ptr<Account> CreateAccountUseCase::execute( 
    const string& userId,
    const string& typeAcc
) {
    auto accounts = _accountRepo->findByUserId(userId);
    if (accounts.size() >= 10) {
        throw std::runtime_error("Each user can have at most 10 accounts.");
    }

    string type = StringUtils::normalizeString(typeAcc);
    auto acc = AccountFactory::instance().create(type);

    acc->setId(std::to_string(std::rand()));
    acc->setUserId(userId);
    acc->setCreatedAt(TimeUtils::toString(time(nullptr)));

    CreateAccountVisitor visitor;
    acc->accept(visitor);

    _accountRepo->save(acc);

    return acc;
}
