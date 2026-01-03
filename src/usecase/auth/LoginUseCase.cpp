#include "LoginUseCase.h"
#include "../../infrastructure/utils/TimeUtils.h"

Session LoginUseCase::login(const string& username, const string& password) {
    shared_ptr<User> user = _userRepo->findByUsername(username);

    if (!user)
        throw std::runtime_error("User not found.");

    if (!user->verifyPassword(password))
        throw std::runtime_error("Invalid password.");

    Session session(user->getId());

    _sessionRepo->save(session);
    return session;
}