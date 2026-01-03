#include "CloseAccountUseCase.h"

void CloseAccountUseCase::execute(
    const string& accountId,
    const string& userId,
    bool close
) {
    auto account = _accountRepo->findByAccountId(accountId);
    if (!account)
        throw std::runtime_error("account not found");

    if (account->getUserId() != userId)
        throw std::runtime_error("Permission denied");

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
