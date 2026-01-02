#include "LoginUseCase.h"
#include "../../infrastructure/utils/TimeUtils.h"

Session LoginUseCase::login(const string& username, const string& password) {
    shared_ptr<User> user = _userRepo->findByUsername(username);

    if (!user)
        throw std::runtime_error("User not found.");

    if (!user->verifyPassword(password))
        throw std::runtime_error("Invalid password.");

    time_t now = time(nullptr);
    time_t expired = now + 3600;

    Session session;
    session.setSessionId(std::to_string(rand()));
    session.setUserId(user->getId());
    session.setCreatedAt(TimeUtils::toString(now));
    session.setExpiredAt(TimeUtils::toString(expired));

    _sessionRepo->save(session);
    return session;
}