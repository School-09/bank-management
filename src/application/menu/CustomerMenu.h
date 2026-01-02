#ifndef _CUSTOMER_MENU_H_
#define _CUSTOMER_MENU_H_

#include "IUserMenu.h"
#include "../controllers/AuthController.h"
#include "../controllers/AccountController.h"
#include "../controllers/TransactionController.h"
#include "../controllers/CardController.h"
#include "../ui/MenuPrinter.h"
#include "../ui/OptionEnum.h"
#include <memory>
using std::shared_ptr, std::make_shared;

class CustomerMenu : public IUserMenu {
private:
    shared_ptr<AuthController> _authController;
    shared_ptr<AccountController> _accountController;
    shared_ptr<TransactionController> _transactionController;
    shared_ptr<CardController> _cardController;

public:
    CustomerMenu(
        shared_ptr<AuthController> authCtrl,
        shared_ptr<AccountController> accCtrl,
        shared_ptr<TransactionController> transactionController,
        shared_ptr<CardController> cardController
    ) : _authController(authCtrl),
        _accountController(accCtrl),
        _transactionController(transactionController),
        _cardController(cardController) {}

    void run() override;
    void runAccountMenu();
    void runTransactionMenu();
    void runCardMenu();
    
public:
    // Rule of Three
    ~CustomerMenu() = default; // shared_ptr tự quản lý

    CustomerMenu(const CustomerMenu&) = default; // copy được
    CustomerMenu& operator=(const CustomerMenu&) = default; 
    
    CustomerMenu(CustomerMenu&&) = default; // move được
    CustomerMenu& operator=(CustomerMenu&&) = default;
};

#endif