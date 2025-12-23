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

void MenuPrinter::printUserMenu() {
    cout << "\n======= USER MENU ========\n";
    cout << "1. Create account\n";
    cout << "2. List my accounts\n";
    cout << "3. Close account\n";
    cout << "4. Logout\n";
    cout << "0. Back\n";
    cout << "==========================\n";
    cout << "Choose: ";
}

void MenuPrinter::printResetPasswordStep2() {
    cout << "\n====== RESET PASSWORD ======\n";
    cout << "1. Enter reset token\n";
    cout << "0. Back\n";
    cout << "============================\n";
    cout << "Choose: ";
}