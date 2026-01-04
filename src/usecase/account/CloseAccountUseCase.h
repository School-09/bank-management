#ifndef _CLOSE_ACCOUNT_USECASE_H_
#define _CLOSE_ACCOUNT_USECASE_H_

#include "../../domain/repositories/IAccountRepository.h"
#include "../../domain/repositories/ICardRepository.h"


#include <stdexcept>
#include <memory>
#include <expected>
using std::expected, std::unexpected;
using std::shared_ptr, std::make_shared;

template <typename T>
using Result = std::expected<T, ErrorCode>;

class CloseAccountUseCase {
private:
    shared_ptr<IAccountRepository> _accountRepo;
    shared_ptr<ICardRepository> _cardRepo;

public:
    CloseAccountUseCase(
        shared_ptr<IAccountRepository> accountRepo,
        shared_ptr<ICardRepository> cardRepo
    ) : _accountRepo(accountRepo),
        _cardRepo(cardRepo) {}

public:
    Result<void> execute(const string& userId, const string& accountId, bool close);

public:
    // Rule of Three
    ~CloseAccountUseCase() = default; // shared_ptr tự quản lý

    CloseAccountUseCase(const CloseAccountUseCase&) = default; // copy được
    CloseAccountUseCase& operator=(const CloseAccountUseCase&) = default; 
    
    CloseAccountUseCase(CloseAccountUseCase&&) = default; // move được
    CloseAccountUseCase& operator=(CloseAccountUseCase&&) = default;
};

#endif