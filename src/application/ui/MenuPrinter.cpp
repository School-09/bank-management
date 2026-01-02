#include "MenuPrinter.h"
#include "ConsoleUI.h"

void MenuPrinter::printAuthMenu() {
    cout << "\n======= BANK SYSTEM =======\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Reset Password\n";
    cout << "0. Exit\n";
    cout << "===========================\n";
    cout << "Choose: ";
}

void MenuPrinter::printResetPasswordStep2() {
    cout << "\n====== RESET PASSWORD ======\n";
    cout << "1. Enter reset token\n";
    cout << "0. Back\n";
    cout << "============================\n";
    cout << "Choose: ";
}

void MenuPrinter::printAdminMenu() {
    cout << "\n======= ADMIN MENU ========\n";
    cout << "1. Account manage\n";
    cout << "2. Card manage\n";
    cout << "3. Logout\n";
    cout << "0. Back\n";
    cout << "==========================\n";
    cout << "Choose: ";
}

void MenuPrinter::printAdminAccountMenu() {
    cout << "\n======= ACCOUNT MANAGE ========\n";
    cout << "1. Create account\n";
    cout << "2. Open account\n";
    cout << "3. Close account\n";
    cout << "4. Logout\n";
    cout << "0. Back\n";
    cout << "==========================\n";
    cout << "Choose: ";
}

void MenuPrinter::printAdminCardMenu() {
    cout << "\n======= CARD MANAGE ========\n";
    cout << "1. Create card\n";
    cout << "2. Delete card\n";
    cout << "3. Block card\n";
    cout << "4. Unblock card\n";
    cout << "5. Logout\n";
    cout << "0. Back\n";
    cout << "==========================\n";
    cout << "Choose: ";
}

void MenuPrinter::printCustomerMenu() {
    cout << "\n======= CUSTOMER MENU ========\n";
    cout << "1. Account manage\n";
    cout << "2. Transaction manage\n";
    cout << "3. Card manage\n";
    cout << "4. Logout\n";
    cout << "0. Back\n";
    cout << "==========================\n";
    cout << "Choose: ";
}

void MenuPrinter::printCustomerAccountMenu() {
    cout << "\n======= ACCOUNT MANAGE ========\n";
    cout << "1. List my accounts\n";
    cout << "2. Logout\n";
    cout << "0. Back\n";
    cout << "==========================\n";
    cout << "Choose: ";
}

void MenuPrinter::printCustomerTransactionMenu() {
    cout << "\n======= TRANSACTION MANAGE ========\n";
    cout << "1. Deposit\n";
    cout << "2. Withdraw\n";
    cout << "3. Transfer\n";
    cout << "4. Logout\n";
    cout << "0. Back\n";
    cout << "==========================\n";
    cout << "Choose: ";
}

void MenuPrinter::printCustomerCardMenu() {
    cout << "\n======= CARD MANAGE ========\n";
    cout << "1. List my cards\n";
    cout << "2. Pay with card\n";
    cout << "3. Logout\n";
    cout << "0. Back\n";
    cout << "==========================\n";
    cout << "Choose: ";
}
