#ifndef _ACCOUNT_CONTROLLER_H_
#define _ACCOUNT_CONTROLLER_H_

#include "../../usecase/account/GetAccountUseCase.h"
#include "../../usecase/account/CreateAccountUseCase.h"
#include "../../usecase/account/CloseAccountUseCase.h"
#include "../../domain/repositories/ISessionRepository.h"

#include <iostream>
#include <stdexcept>
#include <memory>
using std::cin, std::cout;
using std::shared_ptr, std::make_shared;

class AccountController {
private:
    shared_ptr<GetAccountUseCase> _getAccountsUC;
    shared_ptr<CreateAccountUseCase> _createAccountUC;
    shared_ptr<CloseAccountUseCase> _closeAccountUC;
    shared_ptr<ISessionRepository> _sessionRepo;

private:
    std::string getCurrentUserId() const;

public:
    AccountController(
        shared_ptr<GetAccountUseCase> getUC,
        shared_ptr<CreateAccountUseCase> createUC,
        shared_ptr<CloseAccountUseCase> closeUC,
        shared_ptr<ISessionRepository> sessionRepo
    ) : _getAccountsUC(getUC),
        _createAccountUC(createUC),
        _closeAccountUC(closeUC),
        _sessionRepo(sessionRepo) {}

public:
    void showAccounts();
    void createAccount();
    void closeAccount();
    void openAccount();

public:
    // Rule of Three
    ~AccountController() = default; // shared_ptr tự quản lý

    AccountController(const AccountController&) = default; // copy
    AccountController& operator=(const AccountController&) = default; 
    
    AccountController(AccountController&&) = default; // move
    AccountController& operator=(AccountController&&) = default;
};

#endif
