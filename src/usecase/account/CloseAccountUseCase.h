#ifndef _CLOSEACCOUNTUSECASE_H_
#define _CLOSEACCOUNTUSECASE_H_

#include "../../domain/repositories/IAccountRepository.h"

#include <stdexcept>
#include <memory>
using std::shared_ptr, std::make_shared;


class CloseAccountUseCase {
private:
    shared_ptr<IAccountRepository> _repo;

public:
    CloseAccountUseCase(shared_ptr<IAccountRepository> accountRepo) 
        : _repo(accountRepo) {}

public:
    void execute(const string& accountId, const string& userId);

public:
    // Rule of Three
    ~CloseAccountUseCase() = default; // shared_ptr tự quản lý

    CloseAccountUseCase(const CloseAccountUseCase&) = default; // copy được
    CloseAccountUseCase& operator=(const CloseAccountUseCase&) = default; 
    
    CloseAccountUseCase(CloseAccountUseCase&&) = default; // move được
    CloseAccountUseCase& operator=(CloseAccountUseCase&&) = default;
};

#endif