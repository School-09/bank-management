#include "Customer.h"
#include "../../../infrastructure/utils/IdUtils.h"

#include <sstream>
#include <regex>
#include <map>
#include <functional>

Customer::Customer(
    string username,
    string fullName,
    string email,
    string phone,
    string rawPassword
) : User(
    IdUtils::newCustomerId(),
    username,
    fullName,
    email,
    phone,
    rawPassword) {}

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
