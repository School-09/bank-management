#include "RegisterUseCase.h"
#include "../../domain/entities/users/Customer.h"
#include "../../domain/factories/BaseFactory.h"

shared_ptr<User> RegisterUseCase::execute(
    const string& username,
    const string& email,
    const string& info
) {
    // 1. Validate unique
    if (_userRepo->existsByUsername(username))
        throw std::runtime_error("Username already taken."); //TODO: throw

    if (_userRepo->existsByEmail(email))
        throw std::runtime_error("Email already registered."); //TODO: throw

    auto user = BaseFactory<User>::instance().create("customer", info);

    _userRepo->save(user);

    return user;
}
