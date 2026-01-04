#include "CardController.h"
#include "../../infrastructure/formatters/TableFormatter.h"
#include "../../domain/factories/BaseFactory.h"
#include "../../infrastructure/utils/StringUtils.h"
#include "../../domain/entities/cards/Card.h"
#include "../../infrastructure/utils/ErrorMapper.h"

string CardController::getCurrentUserId() const {
    Session s = _sessionRepo->getActiveSession();
    if (s.getUserId().empty())
        throw std::runtime_error("No active session");
    return s.getUserId();
}

void CardController::createCard() {
    auto cardType = ConsoleUI::inputString(
        "card type (Debit / Credit)"
    );

    string type = StringUtils::normalizeString(cardType);

    // 1. Lấy Factory của Card (Tự động instance singleton)
    auto& factory = BaseFactory<Card>::instance();

    // 2. Lấy danh sách fields cần nhập
    std::vector<std::string> fields = factory.getFields(type);
    std::vector<std::string> userInputs;

    auto userId = ConsoleUI::inputString("userId");
    auto accountId = ConsoleUI::inputString("accountId");
    userInputs.push_back(userId);
    userInputs.push_back(accountId);

    auto tmp = ConsoleUI::inputLists(fields);
    userInputs.insert(userInputs.end(), tmp.begin(), tmp.end());

    // 4. Dùng Utils ghép chuỗi (Xử lý trước khi gửi đi)
    std::string finalInf = StringUtils::join(userInputs);

    // 5. Gửi cho Usecase
    auto result = _createUC->execute(userId, accountId, type, finalInf);

    if (!result) {
        ConsoleUI::printError(ErrorMapper::errorMessage(result.error()));
        return;
    }

    ConsoleUI::printNotice("Card created successfully.");
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
        ConsoleUI::printNotice("No cards found.\n");
        return;
    }

    for (auto& row : cards) { 
        tf.addRow(row); 
    }

    std::cout << tf.render() << "\n";
}

void CardController::deleteCard() {
    auto userInputs = ConsoleUI::inputLists({
        "userId", "card id"
    });

    auto result = _deleteUC->execute(userInputs[0], userInputs[1]);

    if (!result) {
        ConsoleUI::printError(ErrorMapper::errorMessage(result.error()));
        return;
    }

    ConsoleUI::printNotice("Card deleted");
}

void CardController::blockCard() {
    auto userInputs = ConsoleUI::inputLists({
        "userId", "card id to block"
    });

    auto result = _blockUC->execute(userInputs[0], userInputs[1], true);

    if (!result) {
        ConsoleUI::printError(ErrorMapper::errorMessage(result.error()));
        return;
    }

    ConsoleUI::printNotice("Card blocked");
}

void CardController::unblockCard() {
    auto userInputs = ConsoleUI::inputLists({
        "userId", "card id to unblock"
    });

    auto result = _blockUC->execute(userInputs[0], userInputs[1], false);

    if (!result) {
        ConsoleUI::printError(ErrorMapper::errorMessage(result.error()));
        return;
    }

    ConsoleUI::printNotice("Card unblocked");
}

void CardController::payWithCard() {
    string userId = getCurrentUserId();

    auto userInputs = ConsoleUI::inputLists({
        "card id", "amount"
    });

    auto result = _paymentUC->execute(userId, userInputs[0], stoi(userInputs[1]));

    if (!result) {
        ConsoleUI::printError(ErrorMapper::errorMessage(result.error()));
        return;
    }

    ConsoleUI::printNotice("Payment successful");
}
