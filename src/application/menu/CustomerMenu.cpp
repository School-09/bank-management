#include "CustomerMenu.h"
#include "../ui/MenuPrinter.h"

void CustomerMenu::run() {
    while (_authController->getLoggedIn()) {
        MenuPrinter::printCustomerMenu();
        string choice;
        getline(cin, choice);

        CustomerMenuOption option = static_cast<CustomerMenuOption> (stoi(choice));

        if (option == CustomerMenuOption::ACCOUNT_MANAGE) {
            runAccountMenu();
        }
        else if (option == CustomerMenuOption::TRANSACTION_MANAGE) {
            runTransactionMenu();
        }
        else if (option == CustomerMenuOption::CARD_MANAGE) {
            runCardMenu();
        }
        else if (option == CustomerMenuOption::LOGOUT) {
            _authController->logoutAction();
        }
        else if (option == CustomerMenuOption::BACK) {
            _authController->logoutAction();
            break;
        }
    }
}

void CustomerMenu::runAccountMenu() {
    while (_authController->getLoggedIn()) {
        MenuPrinter::printCustomerAccountMenu();
        string choice;
        getline(cin, choice);

        CustomerAccountMenuOption option = static_cast<CustomerAccountMenuOption> (stoi(choice));

        if (option == CustomerAccountMenuOption::LIST_ACCOUNTS) {
            _accountController->showAccounts();
        }
        else if (option == CustomerAccountMenuOption::LOGOUT) {
            _authController->logoutAction();
        }
        else if (option == CustomerAccountMenuOption::BACK) {
            break;
        }
    }
}

void CustomerMenu::runTransactionMenu() {
    while (_authController->getLoggedIn()) {
        MenuPrinter::printCustomerTransactionMenu();
        string choice;
        getline(cin, choice);

        CustomerTransactionMenuOption option = static_cast<CustomerTransactionMenuOption> (stoi(choice));

        if (option == CustomerTransactionMenuOption::DEPOSIT) {
            _transactionController->deposit();
        }
        else if (option == CustomerTransactionMenuOption::WITHDRAW) {
            _transactionController->withdraw();
        }
        else if (option == CustomerTransactionMenuOption::TRANSFER) {
            _transactionController->transfer();
        }
        else if (option == CustomerTransactionMenuOption::LOGOUT) {
            _authController->logoutAction();
        }
        else if (option == CustomerTransactionMenuOption::BACK) {
            break;
        }
    }
}

void CustomerMenu::runCardMenu() {
    while (_authController->getLoggedIn()) {
        MenuPrinter::printCustomerCardMenu();
        string choice;
        getline(cin, choice);

        CustomerCardMenuOption option = static_cast<CustomerCardMenuOption> (stoi(choice));

        if (option == CustomerCardMenuOption::LIST_CARDS) {
            _cardController->listCards();
        }
        else if (option == CustomerCardMenuOption::PAY_WITH_CARD) {
            _cardController->payWithCard();
        }
        else if (option == CustomerCardMenuOption::LOGOUT) {
            _authController->logoutAction();
        }
        else if (option == CustomerCardMenuOption::BACK) {
            break;
        }
    }
}
