#ifndef _ADMIN_MENU_H_
#define _ADMIN_MENU_H_

#include "IUserMenu.h"
#include "../controllers/AuthController.h"
#include "../controllers/AccountController.h"
#include "../controllers/TransactionController.h"
#include "../controllers/CardController.h"
#include "../ui/MenuPrinter.h"
#include "../ui/OptionEnum.h"
#include <memory>
using std::shared_ptr, std::make_shared;

class AdminMenu : public IUserMenu {
private:
    shared_ptr<AuthController> _authController;
    shared_ptr<AccountController> _accountController;
    shared_ptr<TransactionController> _transactionController;
    shared_ptr<CardController> _cardController;

public:
    AdminMenu(
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
    void runCardMenu();

public:
    // Rule of Three
    ~AdminMenu() = default; // shared_ptr tự quản lý

    AdminMenu(const AdminMenu&) = default; // copy được
    AdminMenu& operator=(const AdminMenu&) = default; 
    
    AdminMenu(AdminMenu&&) = default; // move được
    AdminMenu& operator=(AdminMenu&&) = default;
};

#endif