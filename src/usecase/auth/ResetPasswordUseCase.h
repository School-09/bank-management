#ifndef _RESET_PASSWORD_USECASE_H_
#define _RESET_PASSWORD_USECASE_H_

#include "../../domain/repositories/IUserRepository.h"
#include "../../domain/repositories/IResetPasswordRepository.h"


#include <ctime>
#include <stdexcept>
#include <memory>
#include <expected>
using std::expected, std::unexpected;
using std::shared_ptr, std::make_shared;

template <typename T>
using Result = std::expected<T, ErrorCode>;

class ResetPasswordUseCase {
private:
    shared_ptr<IUserRepository> _userRepo;
    shared_ptr<IResetPasswordRepository> _tokenRepo;

public:
    ResetPasswordUseCase(
        shared_ptr<IUserRepository> uRepo, 
        shared_ptr<IResetPasswordRepository> tRepo
    ) : _userRepo(uRepo),
        _tokenRepo(tRepo) {}

public:
    // STEP 1: User yêu cầu reset mật khẩu
    Result<ResetPasswordToken> requestToken(const string& email);

    // STEP 2: User nhập token để đổi mật khẩu
    Result<void> resetPassword(const string& tokenId, const string& newPassword);

public:
    // Rule of Three
    ~ResetPasswordUseCase() = default; // shared_ptr tự quản lý

    ResetPasswordUseCase(const ResetPasswordUseCase&) = default; // copy được
    ResetPasswordUseCase& operator=(const ResetPasswordUseCase&) = default; 
    
    ResetPasswordUseCase(ResetPasswordUseCase&&) = default; // move được
    ResetPasswordUseCase& operator=(ResetPasswordUseCase&&) = default;
};


#endif