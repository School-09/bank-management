#include "AuthController.h"
#include "../../domain/factories/BaseFactory.h"
#include "../../infrastructure/utils/StringUtils.h"
#include "../../domain/entities/users/User.h"

// ===============================
// REGISTER
// ===============================
void AuthController::registerAction() {
    try {
        // 1. Lấy Factory của User (Tự động instance singleton)
        auto& factory = BaseFactory<User>::instance();

        // 2. Lấy danh sách fields cần nhập
        std::vector<std::string> fields = factory.getFields("customer");
        std::vector<std::string> userInputs;

        std::string email;
        std::cout << "Enter email: ";
        std::getline(std::cin, email);
        userInputs.push_back(email);

        std::string username;
        std::cout << "Enter username: ";
        std::getline(std::cin, username);
        userInputs.push_back(username);

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
        auto user = _registerUC->execute(username, email, finalInf);

        ConsoleUI::showMessage("Register success. User ID: " + user->getId());
    }
    catch (exception& ex) {
        ConsoleUI::showError(ex.what());
    }
}

// ===============================
// LOGIN
// ===============================
void AuthController::loginAction() {
    string username = ConsoleUI::inputString("Enter username: ");
    string password = ConsoleUI::inputString("Enter password: ");

    try {
        _currentSession = _loginUC->login(username, password);
        isLoggedIn = true;
        ConsoleUI::showMessage("Login success! Session ID: " + _currentSession.getSessionId());
    }
    catch (exception& ex) {
        ConsoleUI::showError(ex.what());
    }
}

// ===============================
// LOGOUT
// ===============================
void AuthController::logoutAction() {
    if (!isLoggedIn) {
        ConsoleUI::showError("You are not logged in.");
        return;
    }

    _logoutUC->execute(_currentSession.getSessionId());
    isLoggedIn = false;
    ConsoleUI::showMessage("Logged out successfully.");
}

// ===============================
// RESET PASSWORD (PART 1)
// ===============================
void AuthController::requestResetPasswordAction() {
    string email = ConsoleUI::inputString("Enter your email: ");

    try {
        ResetPasswordToken token = _resetUC->requestToken(email);
        ConsoleUI::showMessage(
            "Reset token created. Token ID: " + token.getTokenId() +
            "\n(It expires in 10 minutes.)"
        );
    }
    catch (exception& ex) {
        ConsoleUI::showError(ex.what());
    }
}

// ===============================
// RESET PASSWORD (PART 2)
// ===============================
void AuthController::confirmResetPasswordAction() {
    string tokenId = ConsoleUI::inputString("Enter token: ");
    string newPass = ConsoleUI::inputString("Enter new password: ");

    try {
        _resetUC->resetPassword(tokenId, newPass);
        ConsoleUI::showMessage("Password changed successfully.");
    }
    catch (exception& ex) {
        ConsoleUI::showError(ex.what());
    }
}
