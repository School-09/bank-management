#include "RegisterUseCase.h"
#include "../../domain/entities/users/Customer.h"
#include "../../domain/factories/BaseFactory.h"

shared_ptr<User> RegisterUseCase::execute(
    const string& username,
    const string& email,
    const string& inf
) {
    // 1. Validate unique
    if (_userRepo->existsByUsername(username))
        throw std::runtime_error("Username already taken.");

    if (_userRepo->existsByEmail(email))
        throw std::runtime_error("Email already registered.");

    auto user = BaseFactory<User>::instance().create("customer", inf);

    _userRepo->save(user);

    return user;
}
