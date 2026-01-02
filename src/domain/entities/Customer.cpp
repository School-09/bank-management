#include "Customer.h"
#include "../../infrastructure/utils/IdUtils.h"

#include <sstream>
#include <regex>
#include <map>
#include <functional>

Customer::Customer(
    string id,
    string username,
    string rawPassword,
    string fullName,
    string email,
    string phone
) : User(
    IdUtils::newCustomerId(),
    username,
    rawPassword,
    fullName,
    email,
    phone) {}

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
