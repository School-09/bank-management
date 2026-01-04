#include "AuthController.h"
#include "../../domain/factories/BaseFactory.h"
#include "../../infrastructure/utils/StringUtils.h"
#include "../../domain/entities/users/User.h"

// ===============================
// REGISTER
// ===============================
void AuthController::registerAction() {
    // 1. Lấy Factory của User (Tự động instance singleton)
    auto& factory = BaseFactory<User>::instance();

    // 2. Lấy danh sách fields cần nhập
    std::vector<std::string> fields = factory.getFields("customer");
    std::vector<std::string> userInputs;

    auto username = ConsoleUI::inputString("username");
    auto email = ConsoleUI::inputString("your email");
    userInputs.push_back(username);
    userInputs.push_back(email);

    auto tmp = ConsoleUI::inputLists(fields);
    userInputs.insert(userInputs.end(), tmp.begin(), tmp.end());

    // 4. Dùng Utils ghép chuỗi (Xử lý trước khi gửi đi)
    std::string finalInf = StringUtils::join(userInputs);

    // 5. Gửi cho Usecase
    auto user = _registerUC->execute(username, email, finalInf);

    ConsoleUI::printNotice("Register success. User ID: " + user->getId());
}

// ===============================
// LOGIN
// ===============================
string AuthController::loginAction() {
    auto userInputs = ConsoleUI::inputLists({
        "username", "password"
    });

    _currentSession = _loginUC->login(userInputs[0], userInputs[1]);

    isLoggedIn = true;

    ConsoleUI::printNotice("Login success. Session ID: " + _currentSession.getSessionId());

    return _currentSession.getRole();
}

// ===============================
// LOGOUT
// ===============================
void AuthController::logoutAction() {
    if (!isLoggedIn) {
        ConsoleUI::printError("You are not logged in.");
        return;
    }

    _logoutUC->execute(_currentSession.getSessionId());

    isLoggedIn = false;

    ConsoleUI::printNotice("Logged out successfully.");
}

// ===============================
// RESET PASSWORD (PART 1)
// ===============================
void AuthController::requestResetPasswordAction() {
    string email = ConsoleUI::inputString("your email");

    ResetPasswordToken token = _resetUC->requestToken(email);

    ConsoleUI::printNotice(
        "Reset token created. Token ID: " + token.getTokenId() +
        "\n(It expires in 10 minutes.)"
    );
}

// ===============================
// RESET PASSWORD (PART 2)
// ===============================
void AuthController::confirmResetPasswordAction() {
    auto userInputs = ConsoleUI::inputLists({
        "token", "new password"
    });

    _resetUC->resetPassword(userInputs[0], userInputs[1]);

    ConsoleUI::printNotice("Password changed successfully.");
}
