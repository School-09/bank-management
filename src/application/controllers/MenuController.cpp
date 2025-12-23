#include "MenuController.h"

void MenuController::runAuthMenu() { // TODO chuyen cac option thanh enum
    while (true) {
        MenuPrinter::printAuthMenu();
        string choice;
        getline(cin, choice);

        AuthMenuOption option = static_cast<AuthMenuOption> (stoi(choice));

        if (option == AuthMenuOption::REGISTER) {
            _authController->registerAction();
        }
        else if (option == AuthMenuOption::LOGIN) {
            _authController->loginAction();
            runUserMenu();
        }
        else if (option == AuthMenuOption::RESET_PASSWORD) {
            _authController->requestResetPasswordAction();
            string subchoice;
            MenuPrinter::printResetPasswordStep2();
            getline(cin, subchoice);

            ResetPasswordOption suboption = static_cast<ResetPasswordOption> (stoi(subchoice));

            if (suboption == ResetPasswordOption::ENTER_RESET_TOKEN)
                _authController->confirmResetPasswordAction();
        }
        else if (option == AuthMenuOption::EXIT) break;
    }
}

// ===============================
// USER MENU (sau khi login)
// ===============================
void MenuController::runUserMenu() {
    while (_authController->getLoggedIn()) {
        MenuPrinter::printUserMenu();
        string choice;
        getline(cin, choice);

        UserMenuOption option = static_cast<UserMenuOption> (stoi(choice));

        if (option == UserMenuOption::CREATE_ACCOUNT) {
            _accountController->createAccount();
        }
        else if (option == UserMenuOption::LIST_ACCOUNTS) {
            _accountController->showAccounts();
        }
        else if (option == UserMenuOption::CLOSE_ACCOUNT) {
            _accountController->closeAccount();
        }
        else if (option == UserMenuOption::LOGOUT) {
            _authController->logoutAction();
        }
        else if (option == UserMenuOption::BACK) {
            _authController->logoutAction();
            break;
        }
    }
}