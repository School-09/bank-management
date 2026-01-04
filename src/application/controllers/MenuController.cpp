#include "MenuController.h"
#include "../menu/MenuFactory.h"

void MenuController::run() {
    while (true) {
        MenuPrinter::printAuthMenu();
        string choice;
        getline(cin, choice);

        AuthMenuOption option = static_cast<AuthMenuOption> (stoi(choice));

        if (option == AuthMenuOption::REGISTER) {
            _authController->registerAction();
        }
        else if (option == AuthMenuOption::LOGIN) {
            string role = _authController->loginAction();

            auto menu = MenuFactory::create(
                role,
                _authController, 
                _accountController, 
                _transactionController, 
                _cardController
            );

            menu->run();
        }
        else if (option == AuthMenuOption::RESET_PASSWORD) {
            _authController->requestResetPasswordAction();
            string subchoice;
            MenuPrinter::printResetPasswordStep2();
            getline(cin, subchoice);

            ResetPasswordMenuOption suboption = static_cast<ResetPasswordMenuOption> (stoi(subchoice));

            if (suboption == ResetPasswordMenuOption::ENTER_RESET_TOKEN)
                _authController->confirmResetPasswordAction();
        }
        else if (option == AuthMenuOption::EXIT) break;
    }
}