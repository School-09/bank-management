#ifndef _CARDCONTROLLER_H_
#define _CARDCONTROLLER_H_

#include "../../usecase/card/CreateCardUseCase.h"
#include "../../usecase/card/ListCardUseCase.h"
#include "../../usecase/card/DeleteCardUseCase.h"
#include "../../usecase/card/BlockCardUseCase.h"
#include "../../usecase/card/CardPaymentUseCase.h"
#include "../../domain/repositories/ISessionRepository.h"
#include "../MenuPrinter.h"
#include "../ConsoleUI.h"

#include <iostream>
#include <stdexcept>
#include <memory>
using std::cin, std::cout;
using std::string;
using std::exception;
using std::shared_ptr, std::make_shared;

class CardController {
private:
    shared_ptr<CreateCardUseCase> _createUC;
    shared_ptr<ListCardUseCase> _listUC;
    shared_ptr<DeleteCardUseCase> _deleteUC;
    shared_ptr<BlockCardUseCase> _blockUC;
    shared_ptr<CardPaymentUseCase> _paymentUC;
    shared_ptr<ISessionRepository> _sessionRepo;
private:
    string getCurrentUserId() const;

public:
    CardController(
        shared_ptr<CreateCardUseCase> createUC,
        shared_ptr<ListCardUseCase> listUC,
        shared_ptr<DeleteCardUseCase> deleteUC,
        shared_ptr<BlockCardUseCase> blockUC,
        shared_ptr<CardPaymentUseCase> paymentUC,
        shared_ptr<ISessionRepository> sessionRepo
    ) : _createUC(createUC),
      _listUC(listUC),
      _deleteUC(deleteUC),
      _blockUC(blockUC),
      _paymentUC(paymentUC),
      _sessionRepo(sessionRepo) {}

public:
    void createCard();
    void listCards();
    void deleteCard();
    void blockCard();
    void unblockCard();
    void payWithCard();

public:
    // Rule of Three
    ~CardController() = default; // shared_ptr tự quản lý

    CardController(const CardController&) = default; // copy được
    CardController& operator=(const CardController&) = default; 
    
    CardController(CardController&&) = default; // move được
    CardController& operator=(CardController&&) = default;
};

#endif