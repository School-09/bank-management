#include "RegisterUseCase.h"
#include "../../domain/entities/Customer.h"

shared_ptr<User>RegisterUseCase::execute(
    const string& username,
    const string& password,
    const string& fullName,
    const string& email,
    const string& phone
) {
    // 1. Validate unique
    if (_userRepo->existsByUsername(username))
        throw std::runtime_error("Username already taken.");

    if (_userRepo->existsByEmail(email))
        throw std::runtime_error("Email already registered.");


    auto user = make_shared<Customer>(); // mặc định chỉ đăng ký được customer

    user->setId(std::to_string(std::rand())); // TODO: sinh id
    user->setUsername(username);
    user->setEmail(email);
    user->setFullName(fullName);
    user->setPhone(phone);

    user->setPassword(password);

    _userRepo->save(user);

    return user;
}
