#ifndef _GET_ACCOUNT_USECASE_H_
#define _GET_ACCOUNT_USECASE_H_

#include "../../domain/repositories/IAccountRepository.h"
#include "visitors/GetAccountVisitor.h"

#include <string>
#include <vector>
#include <memory>
using std::string;
using std::vector;
using std::shared_ptr, std::make_shared;

class GetAccountUseCase {
private:
    shared_ptr<IAccountRepository> _accountRepo;

public:
    GetAccountUseCase(shared_ptr<IAccountRepository> accountRepo) 
        : _accountRepo(accountRepo) {}

public:
    vector<vector<string>> execute(const string& userId);

public:
    // Rule of Three
    ~GetAccountUseCase() = default; // shared_ptr tự quản lý

    GetAccountUseCase(const GetAccountUseCase&) = default; // copy được
    GetAccountUseCase& operator=(const GetAccountUseCase&) = default; 
    
    GetAccountUseCase(GetAccountUseCase&&) = default; // move được
    GetAccountUseCase& operator=(GetAccountUseCase&&) = default;
};

#endif