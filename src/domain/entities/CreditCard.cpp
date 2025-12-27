#include "CreditCard.h"

#include <iomanip>
#include <sstream>
#include <map>
#include <functional>


string CreditCard::serialize() const {
    std::ostringstream oss;
    oss << Card::serialize();
    oss << "Type: " << "CreditCard" << "\n";
    return oss.str();
}

void CreditCard::deserialize(const vector<string>& lines) {
    Card::deserialize(lines);
}
