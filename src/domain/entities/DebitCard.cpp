#include "DebitCard.h"

#include <iomanip>
#include <sstream>
#include <map>
#include <functional>


string DebitCard::serialize() const {
    std::ostringstream oss;
    oss << Card::serialize();
    oss << "Type: " << "DebitCard" << "\n";
    return oss.str();
}

void DebitCard::deserialize(const vector<string>& lines) {
    Card::deserialize(lines);
}
