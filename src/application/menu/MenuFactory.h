#ifndef _MENU_FACTORY_H_
#define _MENU_FACTORY_H_

#include "CustomerMenu.h"
#include "AdminMenu.h"
#include "../controllers/AuthController.h"
#include "../controllers/AccountController.h"
#include "../controllers/TransactionController.h"
#include "../controllers/CardController.h"

#include <memory>
using std::shared_ptr, std::make_shared;

class MenuFactory {
public:
    static shared_ptr<IUserMenu> create(
        string role,
        shared_ptr<AuthController> authCtrl,
        shared_ptr<AccountController> accCtrl,
        shared_ptr<TransactionController> transactionController,
        shared_ptr<CardController> cardController
    ) {
        if (role == "Admin")
            return make_shared<AdminMenu>(authCtrl, accCtrl, transactionController, cardController);

        return make_shared<CustomerMenu>(authCtrl, accCtrl, transactionController, cardController);
    }
};

#endif


