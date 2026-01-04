#ifndef _REGISTER_USECASE_H_
#define _REGISTER_USECASE_H_

#include "../../domain/repositories/IUserRepository.h"

#include <stdexcept>
#include <memory>
using std::shared_ptr, std::make_shared;

class RegisterUseCase {
private:
    shared_ptr<IUserRepository> _userRepo;

public:
    RegisterUseCase(shared_ptr<IUserRepository> repo) : _userRepo(repo) {}

public:
    shared_ptr<User> execute(
        const string& username,
        const string& email,
        const string& info
    );

public:
    // Rule of Three
    ~RegisterUseCase() = default; // shared_ptr tự quản lý

    RegisterUseCase(const RegisterUseCase&) = default; // copy được
    RegisterUseCase& operator=(const RegisterUseCase&) = default; 
    
    RegisterUseCase(RegisterUseCase&&) = default; // move được
    RegisterUseCase& operator=(RegisterUseCase&&) = default;
};


#endif