#ifndef _CREATE_ACCOUNT_USECASE_H_
#define _CREATE_ACCOUNT_USECASE_H_

#include "../../domain/repositories/IAccountRepository.h"

#include <stdexcept>
#include <ctime>
#include <memory>
using std::shared_ptr, std::make_shared;

class CreateAccountUseCase {
private:
    shared_ptr<IAccountRepository> _accountRepo;

public:
    CreateAccountUseCase(shared_ptr<IAccountRepository> accountRepo) 
        : _accountRepo(accountRepo) {}

public:
    shared_ptr<Account> execute(
        const string& userId,
        const string& typeAcc,
        const string& inf
    );

public:
    // Rule of Three
    ~CreateAccountUseCase() = default; // shared_ptr tự quản lý

    CreateAccountUseCase(const CreateAccountUseCase&) = default; // copy được
    CreateAccountUseCase& operator=(const CreateAccountUseCase&) = default; 
    
    CreateAccountUseCase(CreateAccountUseCase&&) = default; // move được
    CreateAccountUseCase& operator=(CreateAccountUseCase&&) = default;
};

#endif