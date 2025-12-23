#include "AuthController.h"

// ===============================
// REGISTER
// ===============================
void AuthController::registerAction() {
    string username = ConsoleUI::inputString("Enter username: ");
    string email = ConsoleUI::inputString("Enter email: ");
    string fullName = ConsoleUI::inputString("Enter full name: ");
    string phone = ConsoleUI::inputString("Enter phone: ");
    string password = ConsoleUI::inputString("Enter password: ");

    try {
        shared_ptr<User> user = _registerUC->execute(username, password, fullName, email, phone, "Customer");
        ConsoleUI::showMessage("Register success. User ID: " + user->getId());
    }
    catch (exception& ex) {
        ConsoleUI::showError(ex.what());
    }
}

// ===============================
// LOGIN
// ===============================
void AuthController::loginAction() {  // TODO nên trả về bool
    string username = ConsoleUI::inputString("Enter username: ");
    string password = ConsoleUI::inputString("Enter password: ");

    try {
        currentSession = _loginUC->login(username, password);
        isLoggedIn = true;
        ConsoleUI::showMessage("Login success! Session ID: " + currentSession.getSessionId());
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

    _logoutUC->execute(currentSession.getSessionId());
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
