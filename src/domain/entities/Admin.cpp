#include "Admin.h"
#include "../../infrastructure/utils/IdUtils.h"

#include <sstream>
#include <regex>
#include <map>
#include <functional>

Admin::Admin(
    string id,
    string username,
    string rawPassword,
    string fullName,
    string email,
    string phone
) : User(
    "00-00",
    username,
    rawPassword,
    fullName,
    email,
    phone) {}

void Admin::accept(UserVisitor& visitor) { 
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
