#include "MenuPrinter.h"

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

void MenuPrinter::printUserMenu() {
    cout << "\n======= USER MENU ========\n";
    cout << "1. Account manage\n";
    cout << "2. Transaction manage\n";
    cout << "3. Card manage\n";
    cout << "4. Logout\n";
    cout << "0. Back\n";
    cout << "==========================\n";
    cout << "Choose: ";
}

void MenuPrinter::printAccountMenu() {
    cout << "\n======= ACCOUNT MANAGE ========\n";
    cout << "1. Create account\n";
    cout << "2. List my accounts\n";
    cout << "3. Close account\n";
    cout << "4. Logout\n";
    cout << "0. Back\n";
    cout << "==========================\n";
    cout << "Choose: ";
}

void MenuPrinter::printTransactionMenu() {
    cout << "\n======= TRANSACTION MANAGE ========\n";
    cout << "1. Deposit\n";
    cout << "2. Withdraw\n";
    cout << "3. Transfer\n";
    cout << "4. Logout\n";
    cout << "0. Back\n";
    cout << "==========================\n";
    cout << "Choose: ";
}

void MenuPrinter::printCardMenu() {
    cout << "\n======= CARD MANAGE ========\n";
    cout << "1. Create card\n";
    cout << "2. List my cards\n";
    cout << "3. Delete card\n";
    cout << "4. Block card\n";
    cout << "5. Unblock card\n";
    cout << "6. Pay with card\n";
    cout << "7. Logout\n";
    cout << "0. Back\n";
    cout << "==========================\n";
    cout << "Choose: ";
}

void MenuPrinter::printAdminMenu() {
    // cout << "\n======= USER MENU ========\n";
    // cout << "1. Create account\n";
    // cout << "2. List my accounts\n";
    // cout << "3. Close account\n";
    // cout << "4. Logout\n";
    // cout << "0. Back\n";
    // cout << "==========================\n";
    // cout << "Choose: ";
}