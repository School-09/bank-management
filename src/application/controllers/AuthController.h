#ifndef _AUTHCONTROLLER_H_
#define _AUTHCONTROLLER_H_

#include "../../usecase/auth/LoginUseCase.h"
#include "../../usecase/auth/LogoutUseCase.h"
#include "../../usecase/auth/RegisterUseCase.h"
#include "../../usecase/auth/ResetPasswordUseCase.h"
#include "../ui/MenuPrinter.h"
#include "../ui/ConsoleUI.h"

#include <string>
#include <memory>
using std::shared_ptr, std::make_shared;
using std::exception;

class AuthController {
private:
    shared_ptr<RegisterUseCase> _registerUC;
    shared_ptr<LoginUseCase> _loginUC;
    shared_ptr<LogoutUseCase> _logoutUC;
    shared_ptr<ResetPasswordUseCase> _resetUC;

    Session _currentSession;
    bool isLoggedIn = false;

public:
    AuthController(
        shared_ptr<RegisterUseCase> r,
        shared_ptr<LoginUseCase> l,
        shared_ptr<LogoutUseCase> lo,
        shared_ptr<ResetPasswordUseCase> rp
    ) : _registerUC(r),
        _loginUC(l),
        _logoutUC(lo),
        _resetUC(rp) {}

public:
    bool getLoggedIn() const { return isLoggedIn; }

    // ===============================
    // REGISTER
    // ===============================
    void registerAction();

    // ===============================
    // LOGIN
    // ===============================
    void loginAction();

    // ===============================
    // LOGOUT
    // ===============================
    void logoutAction();

    // ===============================
    // RESET PASSWORD (PART 1)
    // ===============================
    void requestResetPasswordAction();

    // ===============================
    // RESET PASSWORD (PART 2)
    // ===============================
    void confirmResetPasswordAction();

public:
    // Rule of Three
    ~AuthController() = default; // shared_ptr tự quản lý
    
    AuthController(const AuthController&) = default; // copy được
    AuthController& operator=(const AuthController&) = default; 
    
    AuthController(AuthController&&) = default; // move được
    AuthController& operator=(AuthController&&) = default;
};


#endif