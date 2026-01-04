#include "RegisterUseCase.h"
#include "../../domain/entities/users/Customer.h"
#include "../../domain/factories/BaseFactory.h"

Result<shared_ptr<User>> RegisterUseCase::execute(
    const string& username,
    const string& email,
    const string& info
) {
    // 1. Validate unique
    if (_userRepo->existsByUsername(username))
        return unexpected(ErrorCode::UserAlreadyExists);

    if (_userRepo->existsByEmail(email))
        return unexpected(ErrorCode::EmailAlreadyExists);

    auto user = BaseFactory<User>::instance().create("customer", info);

    _userRepo->save(user);

    return user;
}
