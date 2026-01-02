#include "Customer.h"

#include <sstream>
#include <regex>
#include <map>
#include <functional>

void Customer::accept(UserVisitor& visitor) { 
    visitor.visit(*this); 
}

string Customer::serialize() const {
    std::ostringstream oss;

    oss << "Customer\n";
    oss << User::serialize();

    return oss.str();
}

void Customer::deserialize(const vector<string>& lines) {
    User::deserialize(lines);
}
