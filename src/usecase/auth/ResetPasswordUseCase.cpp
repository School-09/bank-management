#include "ResetPasswordUseCase.h"
#include "../../infrastructure/utils/TimeUtils.h"

// STEP 1: User yêu cầu reset mật khẩu
Result<ResetPasswordToken> ResetPasswordUseCase::requestToken(const string& email) {
    shared_ptr<User> user = _userRepo->findByEmail(email);
    if (!user)
        return unexpected(ErrorCode::EmailNotFound);

    ResetPasswordToken token(user->getId());

    _tokenRepo->save(token);

    return token;
}

// STEP 2: User nhập token để đổi mật khẩu
Result<void> ResetPasswordUseCase::resetPassword(const string& tokenId, const string& newPassword) {
    ResetPasswordToken token = _tokenRepo->findByTokenId(tokenId);

    if (token.getTokenId().empty())
        return unexpected(ErrorCode::InvalidToken);

    if (token.isExpired())
        return unexpected(ErrorCode::TokenExpired);

    shared_ptr<User> user = _userRepo->findById(token.getUserId());
    if (!user)
        return unexpected(ErrorCode::UserNotFound);

    user->setPassword(newPassword);
    
    _userRepo->save(user);

    _tokenRepo->remove(tokenId);
}