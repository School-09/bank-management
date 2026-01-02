#ifndef _DELETE_CARD_USECASE_H_
#define _DELETE_CARD_USECASE_H_

#include "../../domain/repositories/ICardRepository.h"
#include "../../domain/repositories/IAccountRepository.h"

class DeleteCardUseCase {
private:
    shared_ptr<ICardRepository> _cardRepo;
    shared_ptr<IAccountRepository> _accountRepo;

public:
    DeleteCardUseCase(
        shared_ptr<ICardRepository> cardRepo,
        shared_ptr<IAccountRepository> accountRepo
    ) : _cardRepo(cardRepo), _accountRepo(accountRepo) {}

    void execute(const string& userId, const string& cardId);

public:
    // Rule of Three
    ~DeleteCardUseCase() = default; // shared_ptr tự quản lý

    DeleteCardUseCase(const DeleteCardUseCase&) = default; // copy được
    DeleteCardUseCase& operator=(const DeleteCardUseCase&) = default; 
    
    DeleteCardUseCase(DeleteCardUseCase&&) = default; // move được
    DeleteCardUseCase& operator=(DeleteCardUseCase&&) = default;
};

#endif