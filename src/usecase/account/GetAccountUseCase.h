#ifndef _GETACCOUNTUSECASE_H_
#define _GETACCOUNTUSECASE_H_

#include "../../domain/repositories/IAccountRepository.h"
#include "../../domain/entities/Account.h"

#include <vector>
#include <memory>
using std::vector;
using std::shared_ptr, std::make_shared;

class GetAccountUseCase {
private:
    shared_ptr<IAccountRepository> _repo;

public:
    GetAccountUseCase(shared_ptr<IAccountRepository> accountRepo) 
        : _repo(accountRepo) {}

public:
    vector<shared_ptr<Account>> execute(const string& userId);

public:
    // Rule of Three
    ~GetAccountUseCase() = default; // shared_ptr tự quản lý

    GetAccountUseCase(const GetAccountUseCase&) = default; // copy được
    GetAccountUseCase& operator=(const GetAccountUseCase&) = default; 
    
    GetAccountUseCase(GetAccountUseCase&&) = default; // move được
    GetAccountUseCase& operator=(GetAccountUseCase&&) = default;
};

#endif