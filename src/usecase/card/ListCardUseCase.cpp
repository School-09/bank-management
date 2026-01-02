#include "ListCardUseCase.h"

#include <stdexcept>

vector<vector<string>> ListCardUseCase::execute(const string& userId) {
    if (userId.empty())
        throw std::runtime_error("Invalid userId");

    auto cards = _cardRepo->findByUserId(userId);

    GetCardVisitor visitor;

    for (auto& card : cards) {
        card->accept(visitor);
    }

    return visitor.getResults();
}
