#include "CreateAccountUseCase.h"
#include "../../domain/factories/AccountFactory.h"
#include "../../infrastructure/utils/StringUtils.h"
#include "../../infrastructure/utils/TimeUtils.h"

shared_ptr<Account> CreateAccountUseCase::execute( 
    const string& userId,
    const string& typeAcc
) {
    // TODO: đếm số acc đã tạo, giới hạn 10 acc chp 1 user

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
