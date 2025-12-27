#ifndef _CARDPAYMENTUSECASE_H_
#define _CARDPAYMENTUSECASE_H_

#include "../../domain/repositories/ICardRepository.h"
#include "../../domain/repositories/IAccountRepository.h"
#include "../../domain/repositories/ITransactionRepository.h"

#include <memory>
using std::shared_ptr, std::make_shared;


class CardPaymentUseCase {
private:
    shared_ptr<ICardRepository> _cardRepo;
    shared_ptr<IAccountRepository> _accountRepo;
    shared_ptr<ITransactionRepository> _txRepo;

public:
    CardPaymentUseCase(
        shared_ptr<ICardRepository> cardRepo,
        shared_ptr<IAccountRepository> accountRepo,
        shared_ptr<ITransactionRepository> txRepo
    ) : _cardRepo(cardRepo), _accountRepo(accountRepo), _txRepo(txRepo) {}

    void execute(
        const string& userId,
        const string& cardId,
        double amount
    );

public:
    // Rule of Three
    ~CardPaymentUseCase() = default; // shared_ptr tự quản lý

    CardPaymentUseCase(const CardPaymentUseCase&) = default; // copy được
    CardPaymentUseCase& operator=(const CardPaymentUseCase&) = default; 
    
    CardPaymentUseCase(CardPaymentUseCase&&) = default; // move được
    CardPaymentUseCase& operator=(CardPaymentUseCase&&) = default;
};

#endif