#include "ListCardUseCase.h"

#include <stdexcept>


vector<shared_ptr<Card>> ListCardUseCase::execute(const string& userId) {
    if (userId.empty())
        throw std::runtime_error("Invalid userId");

    return _cardRepo->findByUserId(userId);
}
