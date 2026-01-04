#include "LoginUseCase.h"
#include "visitors/LoginVisitor.h"
#include "../../infrastructure/utils/TimeUtils.h"

Session LoginUseCase::login(const string& username, const string& password) {
    shared_ptr<User> user = _userRepo->findByUsername(username);

    if (!user)
        throw std::runtime_error("User not found."); //TODO: throw

    if (!user->verifyPassword(password))
        throw std::runtime_error("Invalid password."); //TODO: throw

    LoginVisitor visitor;
    user->accept(visitor);
    string role = visitor.getResults();
    
    Session session(user->getId(), role);

    _sessionRepo->save(session);
    
    return session;
}