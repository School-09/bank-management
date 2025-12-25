#include "MenuController.h"

void MenuController::runAuthMenu() {
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

            ResetPasswordMenuOption suboption = static_cast<ResetPasswordMenuOption> (stoi(subchoice));

            if (suboption == ResetPasswordMenuOption::ENTER_RESET_TOKEN)
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

        if (option == UserMenuOption::ACCOUNT_MANAGE) {
            runAccountMenu();
        }
        else if (option == UserMenuOption::TRANSACTION_MANAGE) {
            runTransactionMenu();
        }
        else if (option == UserMenuOption::CARD_MANAGE) {
            runCardMenu();
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

void MenuController::runAccountMenu() {
    while (_authController->getLoggedIn()) {
        MenuPrinter::printAccountMenu();
        string choice;
        getline(cin, choice);

        AccountMenuOption option = static_cast<AccountMenuOption> (stoi(choice));

        if (option == AccountMenuOption::CREATE_ACCOUNT) {
            _accountController->createAccount();
        }
        else if (option == AccountMenuOption::LIST_ACCOUNTS) {
            _accountController->showAccounts();
        }
        else if (option == AccountMenuOption::CLOSE_ACCOUNT) {
            _accountController->closeAccount();
        }
        else if (option == AccountMenuOption::LOGOUT) {
            _authController->logoutAction();
        }
        else if (option == AccountMenuOption::BACK) {
            break;
        }
    }
}

void MenuController::runTransactionMenu() {
    while (_authController->getLoggedIn()) {
        MenuPrinter::printTransactionMenu();
        string choice;
        getline(cin, choice);

        TransactionMenuOption option = static_cast<TransactionMenuOption> (stoi(choice));

        if (option == TransactionMenuOption::DEPOSIT) {
            _transactionController->deposit();
        }
        else if (option == TransactionMenuOption::WITHDRAW) {
            _transactionController->withdraw();
        }
        else if (option == TransactionMenuOption::TRANSFER) {
            _transactionController->transfer();
        }
        else if (option == TransactionMenuOption::LOGOUT) {
            _authController->logoutAction();
        }
        else if (option == TransactionMenuOption::BACK) {
            break;
        }
    }
}

void MenuController::runCardMenu() {
    while (_authController->getLoggedIn()) {
        MenuPrinter::printCardMenu();
        string choice;
        getline(cin, choice);

        CardMenuOption option = static_cast<CardMenuOption> (stoi(choice));

        if (option == CardMenuOption::CREATE_CARD) {
            //_cardController->c();
        }
        else if (option == CardMenuOption::LIST_CARDS) {
            //_cardController->s();
        }
        else if (option == CardMenuOption::CLOSE_CARD) {
            //_cardController->c();
        }
        else if (option == CardMenuOption::LOGOUT) {
            //_cardController->l();
        }
        else if (option == CardMenuOption::BACK) {
            break;
        }
    }
}
