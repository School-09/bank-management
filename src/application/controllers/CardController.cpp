#include "CardController.h"
#include "../../infrastructure/formatters/TableFormatter.h"
#include "../../domain/factories/BaseFactory.h"
#include "../../infrastructure/utils/StringUtils.h"
#include "../../domain/entities/cards/Card.h"

string CardController::getCurrentUserId() const {
    Session s = _sessionRepo->getActiveSession();
    if (s.getUserId().empty())
        throw std::runtime_error("No active session");
    return s.getUserId();
}

void CardController::createCard() {
    try {
        string typeCard;
        cout << "Card type (Debit / Credit): ";
        getline(cin, typeCard);

        string type = StringUtils::normalizeString(typeCard);

        // 1. Lấy Factory của Card (Tự động instance singleton)
        auto& factory = BaseFactory<Card>::instance();

        // 2. Lấy danh sách fields cần nhập
        std::vector<std::string> fields = factory.getFields(type);
        std::vector<std::string> userInputs;

        string userId;
        cout << "Enter userId: ";
        getline(cin, userId);
        userInputs.push_back(userId);

        string accountId;
        cout << "Enter account Id: ";
        getline(cin, accountId);
        userInputs.push_back(accountId);

        // 3. Loop nhập liệu
        std::cin.ignore(); 
        for (const auto& field : fields) {
            std::string val;
            std::cout << "Enter " << field << ": ";
            std::getline(std::cin, val);
            userInputs.push_back(val);
        }

        // 4. Dùng Utils ghép chuỗi (Xử lý trước khi gửi đi)
        std::string finalInf = StringUtils::join(userInputs);

        // 5. Gửi cho Usecase
        _createUC->execute(userId, accountId, type, finalInf);

        cout << "Card created successfully.\n";
    }
    catch (std::exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
    // catch (const exception& e) {
    //     ConsoleUI::error(e.what());
    // }
}

void CardController::listCards() {
    TableFormatter tf;
    tf.setHeaders({
        "STT", "Loại thẻ", "ID thẻ", "ID người dùng", "ID tài khoản liên kết"
        "Số thẻ", "Ngày tạo", "Ngày hết hạn", "Tình trạng"
    });
    tf.setColumnFormats({ 
        ColumnFormat(Alignment::Center, 0), 
        ColumnFormat(Alignment::Left, 0), 
        ColumnFormat(Alignment::Left, 0), 
        ColumnFormat(Alignment::Left, 0), 
        ColumnFormat(Alignment::Left, 0), 
        ColumnFormat(Alignment::Left, 0), 
        ColumnFormat(Alignment::Left, 0), 
        ColumnFormat(Alignment::Left, 0), 
        ColumnFormat(Alignment::Left, 0)
    });

    string userId = getCurrentUserId();

    auto cards = _listUC->execute(userId);

    if (cards.empty()) {
        cout << "No accounts found.\n";
        return;
    }

    for (auto& row : cards) { 
        tf.addRow(row); 
    }

    std::cout << tf.render() << "\n";
}

void CardController::deleteCard() {
    try {
        string userId;
        cout << "Enter user Id: ";
        getline(cin, userId);

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
        string userId;
        cout << "Enter user Id: ";
        getline(cin, userId);

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
        string userId;
        cout << "Enter user Id: ";
        getline(cin, userId);

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

        int amount = std::stoi(amountStr);
        _paymentUC->execute(userId, cardId, amount);

        ConsoleUI::print("Payment successful");
    }
    catch (std::exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}
