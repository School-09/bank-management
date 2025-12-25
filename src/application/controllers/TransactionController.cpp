#include "TransactionController.h"

string TransactionController::getCurrentUserId() const {
    Session s = _sessionRepo->getActiveSession();
    if (s.getUserId().empty())
        throw std::runtime_error("No active session");
    return s.getUserId();
}

void TransactionController::deposit() {
    string userId = getCurrentUserId();

    string accId;
    double amount;

    cout << "Account ID: ";
    getline(cin, accId);

    cout << "Amount: ";
    cin >> amount;

    cin.ignore();

    _depositUC->execute(
        userId,
        accId,
        amount
    );

    cout << "Deposit successful\n";
}

void TransactionController::withdraw() {
    string userId = getCurrentUserId();

    string accId;
    double amount;

    cout << "Account ID: ";
    getline(cin, accId);

    cout << "Amount: ";
    cin >> amount;

    cin.ignore();

    _withdrawUC->execute(
        userId,
        accId,
        amount
    );

    cout << "Withdraw successful\n";
}

void TransactionController::transfer() {
    string userId = getCurrentUserId();

    string fromAccId;
    string toAccId;
    double amount;

    cout << "From account ID: ";
    getline(cin, fromAccId);

    cout << "To account ID: ";
    getline(cin, toAccId);

    cout << "Amount: ";
    cin >> amount;

    cin.ignore();

    _transferUC->execute(
        userId,
        fromAccId,
        toAccId,
        amount
    );

    cout << "Transfer successful\n";
}