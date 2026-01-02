#include "AccountController.h"
#include "../../infrastructure/formatters/TableFormatter.h"

string AccountController::getCurrentUserId() const {
    Session s = _sessionRepo->getActiveSession();
    if (s.getUserId().empty())
        throw std::runtime_error("No active session");
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
    
    // TODO: accounts trống ?

    for (auto& row : accounts) { 
        tf.addRow(row); 
    }

    std::cout << tf.render() << "\n";
}

void AccountController::createAccount() {
    try {
        string userId;
        cout << "Enter user Id: ";
        getline(cin, userId);

        string typeAcc;
        cout << "Account type (CHECKING / CREDIT / SAVING): ";
        getline(cin, typeAcc);

        auto acc = _createAccountUC->execute(
            userId, typeAcc
        );

        cout << "Account created successfully.\n";
    }
    catch (std::exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void AccountController::closeAccount() {
    try {  
        string userId;
        cout << "Enter user Id: ";
        getline(cin, userId);

        string accountId;
        cout << "Enter account id to close: ";
        getline(cin, accountId);

        _closeAccountUC->execute(accountId, userId, true);

        cout << "Account closed successfully.\n";
    }
    catch (std::exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void AccountController::openAccount() {
    try {  
        string userId;
        cout << "Enter user Id: ";
        getline(cin, userId);

        string accountId;
        cout << "Enter account id to open: ";
        getline(cin, accountId);

        _closeAccountUC->execute(accountId, userId, false);

        cout << "Account opened successfully.\n";
    }
    catch (std::exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}