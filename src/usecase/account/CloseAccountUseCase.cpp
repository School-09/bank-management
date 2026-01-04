#include "CloseAccountUseCase.h"

Result<void> CloseAccountUseCase::execute(
    const string& userId,
    const string& accountId,
    bool close
) {
    auto account = _accountRepo->findByAccountId(accountId);
    if (!account)
        return unexpected(ErrorCode::AccountNotFound);

    if (account->getUserId() != userId)
       return unexpected(ErrorCode::PermissionDenied);

    if (close) {
        // Đóng account
        account->deActivate();

        // Đóng card liên quan
        auto cards = _cardRepo->findByAccountId(accountId);
        for (auto card : cards) {
            card->lock();
            _cardRepo->save(card);
        }
    } else {
        // Mở account
        account->activate();

        // Mở card liên quan
        auto cards = _cardRepo->findByAccountId(accountId);
        for (auto card : cards) {
            card->unlock();
            _cardRepo->save(card);
        }
    }
    
    _accountRepo->save(account);
}
