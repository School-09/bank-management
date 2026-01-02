#include "Admin.h"

#include <sstream>
#include <regex>
#include <map>
#include <functional>

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
