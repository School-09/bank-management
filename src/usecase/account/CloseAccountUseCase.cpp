#include "CloseAccountUseCase.h"


void CloseAccountUseCase::execute(
    const string& accountId,
    const string& userId
) {
    if (!_repo->exists(accountId))
        throw std::runtime_error("Account not found");

   vector<shared_ptr<Account>> accounts = _repo->findByUserId(userId);

    shared_ptr<Account> target = nullptr;

    for (shared_ptr<Account> acc : accounts) {
        if (acc->getId() == accountId) {
            target = acc;
            break;
        }
    }
    
    if (!target) {
        throw std::runtime_error("Account not found or permission denied");
    }

    // 4. Đóng account
    target->deactivate();
    _repo->save(target);
}
