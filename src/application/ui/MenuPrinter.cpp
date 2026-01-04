#include "MenuPrinter.h"
#include "ConsoleUI.h"

#include <iostream>
#include <iomanip>
using std::cout;

std::string centerText(const std::string& text, int width) {
    if ((int)text.size() >= width)
        return text.substr(0, width);

    int padding = width - text.size();
    int left = padding / 2;
    int right = padding - left;

    return std::string(left, ' ') + text + std::string(right, ' ');
}

void MenuPrinter::printMenu(
    const string& title,
    const vector<MenuItem>& items
) {
    const int width = 30;

    cout << "\n╔" << string(width, '=') << "╗\n";
    cout << "║" << centerText(title, width) << "║\n";
    cout << "╠" << string(width, '=') << "╣\n";

    for (const auto& item : items) {
        cout << "║ [ " << item.key << " ] "
             << std::setw(width - 7)
             << std::left << item.label
             << "║\n";
    }

    cout << "╚" << string(width, '=') << "╝\n";
    cout << "➜ Choose: ";
}

void MenuPrinter::printAuthMenu() {
    printMenu(
        "AUTHENTICATION",
        {
            {"1", "Register"},
            {"2", "Login"},
            {"3", "Reset Password"},
            {"0", "Exit"}
        }
    );
}

void MenuPrinter::printResetPasswordStep2() {
    printMenu(
        "RESET PASSWORD",
        {
            {"1", "Enter reset token"},
            {"0", "Back"}
        }
    );
}

void MenuPrinter::printAdminMenu() {
    printMenu(
        "ADMIN MENU",
        {
            {"1", "Account manage"},
            {"2", "Card manage"},
            {"3", "Logout"},
            {"0", "Back"}
        }
    );
}

void MenuPrinter::printAdminAccountMenu() {
    printMenu(
        "ACCOUNT MANAGE",
        {
            {"1", "Create account"},
            {"2", "Open account"},
            {"3", "Close account"},
            {"4", "Logout"},
            {"0", "Back"}
        }
    );
}

void MenuPrinter::printAdminCardMenu() {
    printMenu(
        "CARD MANAGE",
        {
            {"1", "Create card"},
            {"2", "Delete card"},
            {"3", "Block card"},
            {"4", "Unblock card"},
            {"5", "Logout"},
            {"0", "Back"}
        }
    );
}

void MenuPrinter::printCustomerMenu() {
    printMenu(
        "CUSTOMER MENU",
        {
            {"1", "Account manage"},
            {"2", "Transaction manage"},
            {"3", "Card manage"},
            {"4", "Logout"},
            {"0", "Back"}
        }
    );
}

void MenuPrinter::printCustomerAccountMenu() {
    printMenu(
        "ACCOUNT MANAGE",
        {
            {"1", "List my accounts"},
            {"2", "Logout"},
            {"0", "Back"}
        }
    );
}

void MenuPrinter::printCustomerTransactionMenu() {
    printMenu(
        "TRANSACTION MANAGE",
        {
            {"1", "Deposit"},
            {"2", "Withdraw"},
            {"3", "Transfer"},
            {"4", "Logout"},
            {"0", "Back"}
        }
    );
}

void MenuPrinter::printCustomerCardMenu() {
    printMenu(
        "CARD MANAGE",
        {
            {"1", "List my cards"},
            {"2", "Pay with card"},
            {"3", "Logout"},
            {"0", "Back"}
        }
    );
}
