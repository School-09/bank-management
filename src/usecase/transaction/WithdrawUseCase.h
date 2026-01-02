#ifndef _WITHDRAW_USECASE_H_
#define _WITHDRAW_USECASE_H_

#include "../../domain/repositories/IAccountRepository.h"
#include "../../domain/repositories/ITransactionRepository.h"
#include "../../domain/repositories/INotificationRepository.h"

#include <stdexcept>
#include <exception>
#include <memory>
using std::shared_ptr, std::make_shared;

class WithdrawUseCase {
private:
    shared_ptr<IAccountRepository> _accountRepo;
    shared_ptr<ITransactionRepository> _txRepo;
    shared_ptr<INotificationRepository> _notifyRepo;

public:
    WithdrawUseCase(
        shared_ptr<IAccountRepository> accountRepo,
        shared_ptr<ITransactionRepository> txRepo,
        shared_ptr<INotificationRepository> notifyRepo
    ) : _accountRepo(accountRepo),
        _txRepo(txRepo),
        _notifyRepo(notifyRepo) {}

public:
    void execute(
        const string& userId,
        const string& fromAccountId,
        int amount
    );

public:
    // Rule of Three
    ~WithdrawUseCase() = default; // shared_ptr tự quản lý

    WithdrawUseCase(const WithdrawUseCase&) = default; // copy được
    WithdrawUseCase& operator=(const WithdrawUseCase&) = default; 
    
    WithdrawUseCase(WithdrawUseCase&&) = default; // move được
    WithdrawUseCase& operator=(WithdrawUseCase&&) = default;
};

#endif