#include "CardController.h"

string CardController::getCurrentUserId() const {
    Session s = _sessionRepo->getActiveSession();
    if (s.getUserId().empty())
        throw std::runtime_error("No active session");
    return s.getUserId();
}

void CardController::createCard() {
    try {
        string userId = getCurrentUserId();

        string accountId, type;

        cout << "Enter account Id: ";
        getline(cin, accountId);

        cout << "Card type (DEBIT / CREDIT): ";
        getline(cin, type);

        _createUC->execute(userId, accountId, type);

        cout << "Card created successfully.\n";
        //ConsoleUI::success("Card created successfully");
    }
    catch (std::exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
    // catch (const exception& e) {
    //     ConsoleUI::error(e.what());
    // }
}

void CardController::listCards() {
    try {
        string userId = getCurrentUserId();
        auto cards = _listUC->execute(userId);

        if (cards.empty()) {
            cout << "No accounts found.\n";
            //ConsoleUI::print("No cards found");
            return;
        }

        for (const auto& card : cards) {
            cout << "Information card\n"; // polymorphism
            cout << "--------------------\n";
            //ConsoleUI::print("--------------------");
        }
    }
    catch (std::exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void CardController::deleteCard() {
    try {
        string userId = getCurrentUserId();

        string cardId;
        ConsoleUI::print("Enter card id: ");
        getline(cin, cardId);

        _deleteUC->execute(userId, cardId);
        ConsoleUI::print("Card deleted");
    }
    catch (std::exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void CardController::blockCard() {
    try {
        string userId = getCurrentUserId();

        string cardId;
        ConsoleUI::print("Enter card id: ");
        getline(cin, cardId);

        _blockUC->execute(userId, cardId, true);
        ConsoleUI::print("Card blocked");
    }
    catch (std::exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void CardController::unblockCard() {
    try {
        string userId = getCurrentUserId();

        string cardId;
        ConsoleUI::print("Enter card id: ");
        getline(cin, cardId);

        _blockUC->execute(userId, cardId, false);
        ConsoleUI::print("Card unblocked");
    }
    catch (std::exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void CardController::payWithCard() {
    try {
        string userId = getCurrentUserId();

        string cardId, amountStr;
        ConsoleUI::print("Enter card id: ");
        getline(cin, cardId);

        ConsoleUI::print("Enter amount: ");
        getline(cin, amountStr);

        double amount = std::stod(amountStr);
        _paymentUC->execute(userId, cardId, amount);

        ConsoleUI::print("Payment successful");
    }
    catch (std::exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}
