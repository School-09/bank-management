#include "DebitCard.h"
#include "../../../infrastructure/utils/IdUtils.h"

#include <sstream>
#include <regex>
#include <map>
#include <functional>

DebitCard::DebitCard(
    string userId, string accountId
) : Card(IdUtils::newDebitCardId(), userId, accountId) {}

void DebitCard::accept(CardVisitor& visitor) { 
    visitor.visit(*this); 
}

string DebitCard::serialize() const {
    std::ostringstream oss;

    oss << "DebitCard\n";
    oss << Card::serialize();

    return oss.str();
}

void DebitCard::deserialize(const vector<string>& lines) {
    Card::deserialize(lines);
}
