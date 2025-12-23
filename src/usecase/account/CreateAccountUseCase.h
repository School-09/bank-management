#ifndef _CREATEACCOUNTUSECASE_H_
#define _CREATEACCOUNTUSECASE_H_

#include "../../domain/repositories/IAccountRepository.h"
#include "../../domain/entities/Account.h"
#include "../../domain/entities/SavingAccount.h"
#include "../../domain/entities/CheckingAccount.h"
#include "../../infrastructure/utils/TimeUtils.h"

#include <stdexcept>
#include <ctime>
#include <memory>
using std::shared_ptr, std::make_shared;

class CreateAccountUseCase {
private:
    shared_ptr<IAccountRepository> _repo;

public:
    CreateAccountUseCase(shared_ptr<IAccountRepository> accountRepo) 
        : _repo(accountRepo) {}

public:
    shared_ptr<Account> execute(
        const string& id,
        const string& userId,
        const string& balance,
        const string& type
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