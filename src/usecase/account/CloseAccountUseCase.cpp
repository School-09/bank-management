#include "CloseAccountUseCase.h"

void CloseAccountUseCase::execute(
    const string& accountId,
    const string& userId
) {
    if (!_accountRepo->exists(accountId))
        throw std::runtime_error("Account not found");

   auto accounts = _accountRepo->findByUserId(userId);

    shared_ptr<Account> target = nullptr;

    for (auto acc : accounts) { // TODO: tìm kiếm tuần tự, có thể cải tiến bằng binary_search (yêu cầu id phải tăng dần)
        if (acc->getId() == accountId) {
            target = acc;
            break;
        }
    }
    
    if (!target) {
        throw std::runtime_error("Account not found or permission denied");
    }

    // 4. Đóng account
    target->deActivate();
    _accountRepo->save(target);
}
