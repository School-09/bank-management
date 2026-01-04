#include "TransactionController.h"
#include "../../infrastructure/utils/StringUtils.h"

string TransactionController::getCurrentUserId() const {
    Session s = _sessionRepo->getActiveSession();
    if (s.getUserId().empty())
        throw std::runtime_error("No active session"); //TODO: throw
    return s.getUserId();
}

void TransactionController::deposit() {
    std::vector<std::string> userInputs;

    string userId = getCurrentUserId();
    auto toAccId = ConsoleUI::inputString("account id to deposit");
    auto amount = ConsoleUI::inputString("amount");

    userInputs.push_back(userId);
    userInputs.push_back(toAccId);
    userInputs.push_back(amount);

    std::string finalInf = StringUtils::join(userInputs);

    _depositUC->execute(
        userId,
        toAccId,
        stoi(amount),
        finalInf
    );

    ConsoleUI::printNotice("Deposit successful");
}

void TransactionController::withdraw() {
    std::vector<std::string> userInputs;

    string userId = getCurrentUserId();
    auto fromAccId = ConsoleUI::inputString("account id to withdraw");
    auto amount = ConsoleUI::inputString("amount");

    userInputs.push_back(userId);
    userInputs.push_back(fromAccId);
    userInputs.push_back(amount);

    std::string finalInf = StringUtils::join(userInputs);

    _withdrawUC->execute(
        userId,
        fromAccId,
        stoi(amount),
        finalInf
    );

    ConsoleUI::printNotice("Withdraw successful");
}

void TransactionController::transfer() {
    std::vector<std::string> userInputs;

    string userId = getCurrentUserId();
    auto fromAccId = ConsoleUI::inputString("account id transfer from");
    auto toAccId = ConsoleUI::inputString("account id transfer to");
    auto amount = ConsoleUI::inputString("amount");

    userInputs.push_back(userId);
    userInputs.push_back(fromAccId);
    userInputs.push_back(toAccId);
    userInputs.push_back(amount);

    std::string finalInf = StringUtils::join(userInputs);

    _transferUC->execute(
        userId,
        fromAccId,
        toAccId,
        stoi(amount),
        finalInf
    );

    ConsoleUI::printNotice("Transfer successful");
}