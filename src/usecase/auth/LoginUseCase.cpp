#include "LoginUseCase.h"
#include "visitors/LoginVisitor.h"
#include "../../infrastructure/utils/TimeUtils.h"

Result<Session> LoginUseCase::login(const string& username, const string& password) {
    shared_ptr<User> user = _userRepo->findByUsername(username);

    if (!user)
        return unexpected(ErrorCode::UserNotFound);

    if (!user->verifyPassword(password))
        return unexpected(ErrorCode::InvalidPassword);

    LoginVisitor visitor;
    user->accept(visitor);
    string role = visitor.getResults();
    
    Session session(user->getId(), role);

    _sessionRepo->save(session);
    
    return session;
}