#ifndef _DEPOSIT_USECASE_H_
#define _DEPOSIT_USECASE_H_

#include "../../domain/repositories/IAccountRepository.h"
#include "../../domain/repositories/ITransactionRepository.h"
#include "../../domain/repositories/INotificationRepository.h"

#include <stdexcept>
#include <exception>
#include <memory>
using std::shared_ptr, std::make_shared;

class DepositUseCase {
private:
    shared_ptr<IAccountRepository> _accountRepo;
    shared_ptr<ITransactionRepository> _txRepo;
    shared_ptr<INotificationRepository> _notifyRepo;

public:
    DepositUseCase(
        shared_ptr<IAccountRepository> accountRepo,
        shared_ptr<ITransactionRepository> txRepo,
        shared_ptr<INotificationRepository> notifyRepo
    ) : _accountRepo(accountRepo),
        _txRepo(txRepo),
        _notifyRepo(notifyRepo) {}

public:
    void execute(
        const string& userId,
        const string& toAccountId,
        int amount,
        const string& info
    );

public:
    // Rule of Three
    ~DepositUseCase() = default; // shared_ptr tự quản lý

    DepositUseCase(const DepositUseCase&) = default; // copy được
    DepositUseCase& operator=(const DepositUseCase&) = default; 
    
    DepositUseCase(DepositUseCase&&) = default; // move được
    DepositUseCase& operator=(DepositUseCase&&) = default;
};

#endif