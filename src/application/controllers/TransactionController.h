#ifndef _TRANSACTIONCONTROLLER_H_
#define _TRANSACTIONCONTROLLER_H_

#include "../../usecase/transaction/DepositUseCase.h"
#include "../../usecase/transaction/WithdrawUseCase.h"
#include "../../usecase/transaction/TransferUseCase.h"
#include "../../domain/repositories/ISessionRepository.h"
#include "../MenuPrinter.h"
#include "../ConsoleUI.h"

#include <iostream>
#include <stdexcept>
#include <memory>
using std::cin, std::cout;
using std::exception;
using std::shared_ptr, std::make_shared;

class TransactionController {
private:
    shared_ptr<DepositUseCase> _depositUC;
    shared_ptr<WithdrawUseCase> _withdrawUC;
    shared_ptr<TransferUseCase> _transferUC;
    shared_ptr<ISessionRepository> _sessionRepo;

private:
    std::string getCurrentUserId() const;

public:
    TransactionController(
        shared_ptr<DepositUseCase> depositUC,
        shared_ptr<WithdrawUseCase> withdrawUC,
        shared_ptr<TransferUseCase> transferUC,
        shared_ptr<ISessionRepository> sessionRepo
    ) : _depositUC(depositUC),
        _withdrawUC(withdrawUC),
        _transferUC(transferUC),
        _sessionRepo(sessionRepo) {}

public:
    void deposit();
    void withdraw();
    void transfer();

public:
    // Rule of Three
    ~TransactionController() = default; // shared_ptr tự quản lý

    TransactionController(const TransactionController&) = default; // copy được
    TransactionController& operator=(const TransactionController&) = default; 
    
    TransactionController(TransactionController&&) = default; // move được
    TransactionController& operator=(TransactionController&&) = default;
};

#endif