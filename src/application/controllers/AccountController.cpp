#include "AccountController.h"

string AccountController::getCurrentUserId() const {
    Session s = _sessionRepo->getActiveSession();
    if (s.getUserId().empty())
        throw std::runtime_error("No active session");
    return s.getUserId();
}

void AccountController::showAccounts() {
    try {
        string userId = getCurrentUserId();

        vector<shared_ptr<Account>> accounts =
            _getAccountsUC->execute(userId);

        cout << "\n=== YOUR ACCOUNTS ===\n";

        if (accounts.empty())
            cout << "No accounts found.\n";

        for (shared_ptr<Account> acc : accounts) {
            cout << "ID: " << acc->getId() << "\n";
            cout << "Type: " << acc->getType() << "\n";
            cout << "Balance: " << acc->getBalance() << "\n";
            cout << "Status: "
                 << (acc->isActive() ? "ACTIVE" : "CLOSED") << "\n";
            cout << "--------------------\n";
        }
    }
    catch (std::exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void AccountController::createAccount() {
    try {
        string id, type, balance;
        string userId = getCurrentUserId();

        cout << "Enter account id: ";
        getline(cin, id);

        cout << "Account type (SAVING / CHECKING): ";
        getline(cin, type);

        cout << "Initial balance: ";
        getline(cin, balance);

        shared_ptr<Account> acc = _createAccountUC->execute(
            id, userId, balance, type
        );

        cout << "Account created successfully.\n";
    }
    catch (std::exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void AccountController::closeAccount() {
    try {
        string accountId;
        string userId = getCurrentUserId();

        cout << "Enter account id to close: ";
        getline(cin, accountId);

        _closeAccountUC->execute(accountId, userId);

        cout << "Account closed successfully.\n";
    }
    catch (std::exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}
