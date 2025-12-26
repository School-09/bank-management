#ifndef _LISTCARDUSECASE_H_
#define _LISTCARDUSECASE_H_

#include "../../domain/repositories/ICardRepository.h"
#include "../../domain/entities/Card.h"

#include <memory>
#include <vector>
using std::shared_ptr;
using std::vector;
using std::shared_ptr, std::make_shared;

class ListCardUseCase {
private:
    shared_ptr<ICardRepository> _cardRepo;

public:
    ListCardUseCase(shared_ptr<ICardRepository> cardRepo)
        : _cardRepo(cardRepo) {}

    vector<shared_ptr<Card>> execute(const string& userId);

public:
    // Rule of Three
    ~ListCardUseCase() = default; // shared_ptr tự quản lý

    ListCardUseCase(const ListCardUseCase&) = default; // copy được
    ListCardUseCase& operator=(const ListCardUseCase&) = default; 
    
    ListCardUseCase(ListCardUseCase&&) = default; // move được
    ListCardUseCase& operator=(ListCardUseCase&&) = default;
};

#endif
