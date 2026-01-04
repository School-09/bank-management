#include "AccountController.h"
#include "../../infrastructure/formatters/TableFormatter.h"
#include "../../domain/factories/BaseFactory.h"
#include "../../infrastructure/utils/StringUtils.h"
#include "../../domain/entities/accounts/Account.h"
#include "../../infrastructure/utils/ErrorMapper.h"

string AccountController::getCurrentUserId() const {
    Session s = _sessionRepo->getActiveSession();
    return s.getUserId();
}

void AccountController::showAccounts() {
    TableFormatter tf;
    tf.setHeaders({
        "STT", "Loại tài khoản", "ID tài khoản", "ID người dùng", 
        "Thông tin tài khoản", "Ngày tạo", "Tình trạng"
    });
    tf.setColumnFormats({ 
        ColumnFormat(Alignment::Center, 0), 
        ColumnFormat(Alignment::Left, 0), 
        ColumnFormat(Alignment::Left, 0), 
        ColumnFormat(Alignment::Left, 0), 
        ColumnFormat(Alignment::Left, 0), 
        ColumnFormat(Alignment::Left, 0), 
        ColumnFormat(Alignment::Left, 0)
    });

    string userId = getCurrentUserId();

    auto accounts = _getAccountsUC->execute(userId);

    if (accounts.empty()) {
        ConsoleUI::printNotice("No accounts found.\n");
        return;
    }

    for (auto& row : accounts) { 
        tf.addRow(row); 
    }

    std::cout << tf.render() << "\n";
}

void AccountController::createAccount() {
    auto accountType = ConsoleUI::inputString(
        "account type (Checking / Saving / Credit)"
    );

    string type = StringUtils::normalizeString(accountType);

    // 1. Lấy Factory của Account (Tự động instance singleton)
    auto& factory = BaseFactory<Account>::instance();

    // 2. Lấy danh sách fields cần nhập
    std::vector<std::string> fields = factory.getFields(type);
    vector<string> userInputs;

    auto userId = ConsoleUI::inputString("userId");
    userInputs.push_back(userId);

    auto tmp = ConsoleUI::inputLists(fields);
    userInputs.insert(userInputs.end(), tmp.begin(), tmp.end());

    // 4. Dùng Utils ghép chuỗi (Xử lý trước khi gửi đi)
    std::string finalInf = StringUtils::join(userInputs);

    // 5. Gửi cho Usecase
    auto result = _createAccountUC->execute(userId, type, finalInf);

    if (!result) {
        ConsoleUI::printError(ErrorMapper::errorMessage(result.error()));
        return;
    }

    ConsoleUI::printNotice("Account created successfully.");
}

void AccountController::closeAccount() {
    auto userInputs = ConsoleUI::inputLists({
        "userId", "accountId to close"
    });

    auto result = _closeAccountUC->execute(userInputs[0], userInputs[1], true);

    if (!result) {
        ConsoleUI::printError(ErrorMapper::errorMessage(result.error()));
        return;
    }

    ConsoleUI::printNotice("Account closed successfully.");
}

void AccountController::openAccount() { 
    auto userInputs = ConsoleUI::inputLists({
        "userId", "accountId to open"
    });

    auto result = _closeAccountUC->execute(userInputs[0], userInputs[1], false);

    if (!result) {
        ConsoleUI::printError(ErrorMapper::errorMessage(result.error()));
        return;
    }

    ConsoleUI::printNotice("Account opened successfully.");
}