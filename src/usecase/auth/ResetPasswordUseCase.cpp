#include "ResetPasswordUseCase.h"

// STEP 1: User yêu cầu reset mật khẩu
ResetPasswordToken ResetPasswordUseCase::requestToken(const string& email) {
    shared_ptr<User> user = _userRepo->findByEmail(email);
    if (!user)
        throw std::runtime_error("User email not found.");

    time_t now = time(nullptr);
    time_t expired = now + 600;

    ResetPasswordToken token;
    token.setTokenId(std::to_string(rand())); // TODO sinh id
    token.setUserId(user->getId());
    token.setCreatedAt(TimeUtil::toString(now));
    token.setExpiredAt(TimeUtil::toString(expired));

    _tokenRepo->save(token);
    return token;
}

// STEP 2: User nhập token để đổi mật khẩu
void ResetPasswordUseCase::resetPassword(const string& tokenId, const string& newPassword) {
    ResetPasswordToken token = _tokenRepo->findById(tokenId);

    if (token.getTokenId().empty())
        throw std::runtime_error("Invalid token.");

    if (token.isExpired())
        throw std::runtime_error("Token expired.");

    shared_ptr<User> user = _userRepo->findById(token.getUserId());
    if (!user)
        throw std::runtime_error("User not found.");

    user->setPassword(newPassword);
    _userRepo->save(user);

    _tokenRepo->remove(tokenId);
}