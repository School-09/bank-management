#ifndef _CARD_PAYMENT_USECASE_H_
#define _CARD_PAYMENT_USECASE_H_

#include "../../domain/repositories/ICardRepository.h"
#include "../../domain/repositories/IAccountRepository.h"
#include "../../domain/repositories/ITransactionRepository.h"
#include "../../domain/repositories/INotificationRepository.h"

#include <memory>
using std::shared_ptr, std::make_shared;

class CardPaymentUseCase {
private:
    shared_ptr<ICardRepository> _cardRepo;
    shared_ptr<IAccountRepository> _accountRepo;
    shared_ptr<ITransactionRepository> _txRepo;
    shared_ptr<INotificationRepository> _notifyRepo;

public:
    CardPaymentUseCase(
        shared_ptr<ICardRepository> cardRepo,
        shared_ptr<IAccountRepository> accountRepo,
        shared_ptr<ITransactionRepository> txRepo,
        shared_ptr<INotificationRepository> notifyRepo
    ) : _cardRepo(cardRepo), 
        _accountRepo(accountRepo), 
        _txRepo(txRepo), 
        _notifyRepo(notifyRepo) {}

    void execute(
        const string& userId,
        const string& cardId,
        int amount
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