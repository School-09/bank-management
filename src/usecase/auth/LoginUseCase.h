#ifndef _LOGIN_USECASE_H_
#define _LOGIN_USECASE_H_

#include "../../domain/repositories/IUserRepository.h"
#include "../../domain/repositories/ISessionRepository.h"


#include <stdexcept>
#include <ctime>
#include <memory>
#include <expected>
using std::expected, std::unexpected;
using std::shared_ptr, std::make_shared;

template <typename T>
using Result = std::expected<T, ErrorCode>;

class LoginUseCase {
private:
    shared_ptr<IUserRepository> _userRepo;
    shared_ptr<ISessionRepository> _sessionRepo;

public:
    LoginUseCase(
        shared_ptr<IUserRepository> userRepo, 
        shared_ptr<ISessionRepository> sessionRepo
    ) : _userRepo(userRepo), 
        _sessionRepo(sessionRepo) {}

public:
    Result<Session> login(const string& username, const string& password);

public:
    // Rule of Three
    ~LoginUseCase() = default; // shared_ptr tự quản lý

    LoginUseCase(const LoginUseCase&) = default; // copy được
    LoginUseCase& operator=(const LoginUseCase&) = default; 
    
    LoginUseCase(LoginUseCase&&) = default; // move được
    LoginUseCase& operator=(LoginUseCase&&) = default;
};


#endif