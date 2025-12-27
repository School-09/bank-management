#include "GetAccountUseCase.h"


vector<shared_ptr<Account>> GetAccountUseCase::execute(const string& userId) {
    return _repo->findByUserId(userId);
}
