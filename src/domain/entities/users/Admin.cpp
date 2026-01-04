#include "Admin.h"
#include "../../../infrastructure/utils/IdUtils.h"

#include <sstream>
#include <regex>
#include <map>
#include <functional>

Admin::Admin(
    string username,
    string fullName,
    string email,
    string phone,
    string rawPassword
) : User(
    "00-00",
    username,
    fullName,
    email,
    phone,
    rawPassword) {}

void Admin::accept(IUserVisitor& visitor) { 
    visitor.visit(*this); 
}

string Admin::serialize() const {
    std::ostringstream oss;

    oss << "Admin\n";
    oss << User::serialize();

    return oss.str();
}

void Admin::deserialize(const vector<string>& lines) {
    User::deserialize(lines);
}
