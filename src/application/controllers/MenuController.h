#ifndef _MENUCONTROLLER_H_
#define _MENUCONTROLLER_H_

#include "AuthController.h"
#include "AccountController.h"
#include "../MenuPrinter.h"
#include "../OptionEnum.h"
#include <memory>
using std::shared_ptr, std::make_shared;

class MenuController {
private:
    shared_ptr<AuthController> _authController;
    shared_ptr<AccountController> _accountController;

public:
    MenuController(
        shared_ptr<AuthController> authCtrl,
        shared_ptr<AccountController> accCtrl
    ) : _authController(authCtrl),
        _accountController(accCtrl) {}

public:
    void runAuthMenu();
    void runUserMenu();

public:
    // Rule of Three
    ~MenuController() = default; // shared_ptr tự quản lý

    MenuController(const MenuController&) = default; // copy được
    MenuController& operator=(const MenuController&) = default; 
    
    MenuController(MenuController&&) = default; // move được
    MenuController& operator=(MenuController&&) = default;
};


#endif