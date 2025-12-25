#ifndef _TRANSFERUSECASE_H_
#define _TRANSFERUSECASE_H_

#include "../../domain/repositories/IAccountRepository.h"
#include "../../domain/repositories/ITransactionRepository.h"
#include "../../domain/repositories/INotificationRepository.h"
#include "../../domain/entities/Account.h"

#include <stdexcept>
#include <exception>
#include <memory>
using std::shared_ptr, std::make_shared;

class TransferUseCase {
private:
    shared_ptr<IAccountRepository> _accountRepo;
    shared_ptr<ITransactionRepository> _txRepo;
    shared_ptr<INotificationRepository> _notifyRepo;

public:
    TransferUseCase(
        shared_ptr<IAccountRepository> accountRepo,
        shared_ptr<ITransactionRepository> txRepo,
        shared_ptr<INotificationRepository> notifyRepo
    ) : _accountRepo(accountRepo),
        _txRepo(txRepo),
        _notifyRepo(notifyRepo) {}

public:
    void execute(
        const string& userId,
        const string& fromId,
        const string& toId,
        double amount
    );

public:
    // Rule of Three
    ~TransferUseCase() = default; // shared_ptr tự quản lý

    TransferUseCase(const TransferUseCase&) = default; // copy được
    TransferUseCase& operator=(const TransferUseCase&) = default; 
    
    TransferUseCase(TransferUseCase&&) = default; // move được
    TransferUseCase& operator=(TransferUseCase&&) = default;
};

#endif