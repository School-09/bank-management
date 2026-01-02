#ifndef _LOGOUT_USECASE_H_
#define _LOGOUT_USECASE_H_

#include "../../domain/repositories/ISessionRepository.h"

#include <memory>
using std::shared_ptr, std::make_shared;

class LogoutUseCase {
private:
    shared_ptr<ISessionRepository> _sessionRepo;

public:
    LogoutUseCase(shared_ptr<ISessionRepository> repo) : _sessionRepo(repo) {}

public:
    bool execute(const string& sessionId);

public:
    // Rule of Three
    ~LogoutUseCase() = default; // shared_ptr tự quản lý

    LogoutUseCase(const LogoutUseCase&) = default; // copy được
    LogoutUseCase& operator=(const LogoutUseCase&) = default; 
    
    LogoutUseCase(LogoutUseCase&&) = default; // move được
    LogoutUseCase& operator=(LogoutUseCase&&) = default;
};


#endif