#include "AdminMenu.h"
#include "../ui/MenuPrinter.h"

void AdminMenu::run() {
    while (_authController->getLoggedIn()) {
        MenuPrinter::printAdminMenu();
        string choice;
        getline(cin, choice);

        AdminMenuOption option = static_cast<AdminMenuOption> (stoi(choice));

        if (option == AdminMenuOption::ACCOUNT_MANAGE) {
            runAccountMenu();
        }
        else if (option == AdminMenuOption::CARD_MANAGE) {
            runCardMenu();
        }
        else if (option == AdminMenuOption::LOGOUT) {
            _authController->logoutAction();
        }
        else if (option == AdminMenuOption::BACK) {
            _authController->logoutAction();
            break;
        }
    }
}

void AdminMenu::runAccountMenu() {
    while (_authController->getLoggedIn()) {
        MenuPrinter::printAdminAccountMenu();
        string choice;
        getline(cin, choice);

        AdminAccountMenuOption option = static_cast<AdminAccountMenuOption> (stoi(choice));

        if (option == AdminAccountMenuOption::CREATE_ACCOUNT) {
            _accountController->createAccount();
        }
        else if (option == AdminAccountMenuOption::CLOSE_ACCOUNT) {
            _accountController->closeAccount();
        }
        else if (option == AdminAccountMenuOption::LOGOUT) {
            _authController->logoutAction();
        }
        else if (option == AdminAccountMenuOption::BACK) {
            break;
        }
    }
}

void AdminMenu::runCardMenu() {
    while (_authController->getLoggedIn()) {
        MenuPrinter::printAdminCardMenu();
        string choice;
        getline(cin, choice);

        AdminCardMenuOption option = static_cast<AdminCardMenuOption> (stoi(choice));

        if (option == AdminCardMenuOption::CREATE_CARD) {
            _cardController->createCard();
        }
        else if (option == AdminCardMenuOption::DELETE_CARD) {
            _cardController->deleteCard();
        }
        else if (option == AdminCardMenuOption::BLOCK_CARD) {
            _cardController->blockCard();
        }
        else if (option == AdminCardMenuOption::UNBLOCK_CARD) {
            _cardController->unblockCard();
        }
        else if (option == AdminCardMenuOption::LOGOUT) {
            _authController->logoutAction();
        }
        else if (option == AdminCardMenuOption::BACK) {
            break;
        }
    }
}
