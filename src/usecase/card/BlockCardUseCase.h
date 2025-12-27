#ifndef _BLOCKCARDUSECASE_H_
#define _BLOCKCARDUSECASE_H_

#include "../../domain/repositories/ICardRepository.h"
#include "../../domain/repositories/IAccountRepository.h"


class BlockCardUseCase {
private:
    shared_ptr<ICardRepository> _cardRepo;
    shared_ptr<IAccountRepository> _accountRepo;

public:
    BlockCardUseCase(shared_ptr<ICardRepository> cardRepo,
                     shared_ptr<IAccountRepository> accountRepo)
        : _cardRepo(cardRepo), _accountRepo(accountRepo) {}

    void execute(const string& userId, const string& cardId, bool block);

public:
    // Rule of Three
    ~BlockCardUseCase() = default; // shared_ptr tự quản lý

    BlockCardUseCase(const BlockCardUseCase&) = default; // copy được
    BlockCardUseCase& operator=(const BlockCardUseCase&) = default; 
    
    BlockCardUseCase(BlockCardUseCase&&) = default; // move được
    BlockCardUseCase& operator=(BlockCardUseCase&&) = default;
};

#endif