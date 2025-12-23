#include "RegisterUseCase.h"

shared_ptr<User>RegisterUseCase::execute(
    const string& username,
    const string& password,
    const string& fullName,
    const string& email,
    const string& phone,
    const string& roleStr
) {
    // 1. Validate unique
    if (_userRepo->existsByUsername(username))
        throw std::runtime_error("Username already taken.");

    if (_userRepo->existsByEmail(email))
        throw std::runtime_error("Email already registered.");

    // 2. Xác định role
    Role role;
    if (roleStr == "Admin")
        role = Role::ADMIN;
    else
        role = Role::CUSTOMER;

    // 3. Create correct user type
    shared_ptr<User> user = nullptr;
    if (role == Role::ADMIN)
        user = make_shared<Admin> (Admin());
    else
        user = make_shared<Customer> (Customer());

    // 4. Set basic info
    user->setId(std::to_string(std::rand())); // TODO: sinh id
    user->setUsername(username);
    user->setEmail(email);
    user->setFullName(fullName);
    user->setPhone(phone);
    user->setRole(role);

    // 5. Hash password
    user->setPassword(password);

    //TODO if user is .. what attributes are there ?

    // 6. Persist
    _userRepo->save(user);

    return user;
}