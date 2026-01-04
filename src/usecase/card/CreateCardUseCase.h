#ifndef _CREATE_CARD_USECASE_H_
#define _CREATE_CARD_USECASE_H_

#include "../../domain/repositories/ICardRepository.h"
#include "../../domain/repositories/IAccountRepository.h"


#include <expected>
using std::expected, std::unexpected;

template <typename T>
using Result = std::expected<T, ErrorCode>;

class CreateCardUseCase {
private:
    shared_ptr<ICardRepository> _cardRepo;
    shared_ptr<IAccountRepository> _accountRepo;

public:
    CreateCardUseCase(
        shared_ptr<ICardRepository> cardRepo,
        shared_ptr<IAccountRepository> accountRepo
    ) : _cardRepo(cardRepo), _accountRepo(accountRepo) {}

    Result<shared_ptr<Card>> execute(
        const string& userId,
        const string& accountId,
        const string& typeCard,
        const string& info
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