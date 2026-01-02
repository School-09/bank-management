#include "CreditCard.h"
#include "../../infrastructure/utils/IdUtils.h"

#include <regex>
#include <sstream>
#include <map>
#include <functional>

CreditCard::CreditCard(
    string id, string userId, string accountId
) : Card(IdUtils::newCreditCardId(), userId, accountId) {}

void CreditCard::accept(CardVisitor& visitor) { 
    visitor.visit(*this); 
}

string CreditCard::serialize() const {
    std::ostringstream oss;

    oss << "CreditCard\n";
    oss << Card::serialize();

    return oss.str();
}

void CreditCard::deserialize(const vector<string>& lines) {
    Card::deserialize(lines);
}
