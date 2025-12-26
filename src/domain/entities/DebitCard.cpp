#include "DebitCard.h"
#include <sstream>

string DebitCard::serialize() const {
    std::ostringstream oss;
    oss << Card::serialize();
    oss << "Type: " << "DEBIT" << "\n";
    return oss.str();
}

void DebitCard::deserialize(const vector<string>& lines) {
    Card::deserialize(lines);
}
