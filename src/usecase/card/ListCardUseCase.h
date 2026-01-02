#ifndef _LIST_CARD_USECASE_H_
#define _LIST_CARD_USECASE_H_

#include "../../domain/repositories/ICardRepository.h"
#include "visitors/GetCardVisitor.h"

#include <vector>
#include <memory>
using std::vector;
using std::shared_ptr, std::make_shared;

class ListCardUseCase {
private:
    shared_ptr<ICardRepository> _cardRepo;

public:
    ListCardUseCase(shared_ptr<ICardRepository> cardRepo)
        : _cardRepo(cardRepo) {}

public:
    vector<vector<string>> execute(const string& userId);

public:
    // Rule of Three
    ~ListCardUseCase() = default; // shared_ptr tự quản lý

    ListCardUseCase(const ListCardUseCase&) = default; // copy được
    ListCardUseCase& operator=(const ListCardUseCase&) = default; 
    
    ListCardUseCase(ListCardUseCase&&) = default; // move được
    ListCardUseCase& operator=(ListCardUseCase&&) = default;
};

#endif
