#include "GetAccountUseCase.h"

vector<vector<string>> GetAccountUseCase::execute(const string& userId) {
    auto accounts = _accountRepo->findByUserId(userId);
    
    GetAccountVisitor visitor;
    
    for (auto& acc : accounts) {
        acc->accept(visitor);
    }

    return visitor.getResults();
}
