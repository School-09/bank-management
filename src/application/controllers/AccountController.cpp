#include "AccountController.h"
#include "../../infrastructure/formatters/TableFormatter.h"
#include "../../domain/factories/BaseFactory.h"
#include "../../infrastructure/utils/StringUtils.h"
#include "../../domain/entities/accounts/Account.h"

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
    string typeAcc;
    cout << "Enter Account Type (Checking / Saving / Credit): ";
    getline(cin, typeAcc);

    string type = StringUtils::normalizeString(typeAcc);

    try {
        // 1. Lấy Factory của Account (Tự động instance singleton)
        auto& factory = BaseFactory<Account>::instance();

        // 2. Lấy danh sách fields cần nhập
        std::vector<std::string> fields = factory.getFields(type);
        std::vector<std::string> userInputs;

        string userId;
        cout << "Enter user Id: ";
        getline(cin, userId);
        userInputs.push_back(userId);

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
        _createAccountUC->execute(userId, type, finalInf);
        
        std::cout << "Created successfully!\n";

    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
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