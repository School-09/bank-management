#include "TransactionController.h"
#include "../../infrastructure/utils/StringUtils.h"

string TransactionController::getCurrentUserId() const {
    Session s = _sessionRepo->getActiveSession();
    if (s.getUserId().empty())
        throw std::runtime_error("No active session");
    return s.getUserId();
}

void TransactionController::deposit() {
    std::vector<std::string> userInputs;

    string userId = getCurrentUserId();
    userInputs.push_back(userId);

    string toAccId;
    cout << "To Account ID: ";
    getline(cin, toAccId);
    userInputs.push_back(toAccId);

    string amount;
    cout << "Amount: ";
    cin >> amount;
    userInputs.push_back(amount);

    std::string finalInf = StringUtils::join(userInputs);

    cin.ignore();

    _depositUC->execute(
        userId,
        toAccId,
        stoi(amount),
        finalInf
    );

    cout << "Deposit successful\n";
}

void TransactionController::withdraw() {
    std::vector<std::string> userInputs;

    string userId = getCurrentUserId();
    userInputs.push_back(userId);

    string fromAccId;
    cout << "Account ID: ";
    getline(cin, fromAccId);
    userInputs.push_back(fromAccId);

    string amount;
    cout << "Amount: ";
    cin >> amount;
    userInputs.push_back(amount);

    std::string finalInf = StringUtils::join(userInputs);

    cin.ignore();

    _withdrawUC->execute(
        userId,
        fromAccId,
        stoi(amount),
        finalInf
    );

    cout << "Withdraw successful\n";
}

void TransactionController::transfer() {
    std::vector<std::string> userInputs;

    string userId = getCurrentUserId();
    userInputs.push_back(userId);

    string fromAccId;
    cout << "From account ID: ";
    getline(cin, fromAccId);
    userInputs.push_back(fromAccId);

    string toAccId;
    cout << "To account ID: ";
    getline(cin, toAccId);
    userInputs.push_back(toAccId);

    string amount;
    cout << "Amount: ";
    cin >> amount;
    userInputs.push_back(amount);

    std::string finalInf = StringUtils::join(userInputs);

    cin.ignore();

    _transferUC->execute(
        userId,
        fromAccId,
        toAccId,
        stoi(amount),
        finalInf
    );

    cout << "Transfer successful\n";
}