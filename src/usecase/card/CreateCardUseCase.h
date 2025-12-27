#ifndef _CREATECARDUSECASE_H_
#define _CREATECARDUSECASE_H_

#include "../../domain/repositories/ICardRepository.h"
#include "../../domain/repositories/IAccountRepository.h"


class CreateCardUseCase {
private:
    shared_ptr<ICardRepository> _cardRepo;
    shared_ptr<IAccountRepository> _accountRepo;

public:
    CreateCardUseCase(
        shared_ptr<ICardRepository> cardRepo,
        shared_ptr<IAccountRepository> accountRepo
    ) : _cardRepo(cardRepo), _accountRepo(accountRepo) {}

    void execute(
        const string& userId,
        const string& accountId,
        const string& type
    );

public:
    // Rule of Three
    ~CreateCardUseCase() = default; // shared_ptr tự quản lý

    CreateCardUseCase(const CreateCardUseCase&) = default; // copy được
    CreateCardUseCase& operator=(const CreateCardUseCase&) = default; 
    
    CreateCardUseCase(CreateCardUseCase&&) = default; // move được
    CreateCardUseCase& operator=(CreateCardUseCase&&) = default;
};

#endif