#include "Customer.h"
#include "../../infrastructure/utils/FileUtils.h"

#include <sstream>
#include <map>
#include <functional>


string Customer::serialize() const {
    std::ostringstream oss;

    oss << User::serialize();

    return oss.str();
}

void Customer::deserialize(const vector<string>& lines) {
    User::deserialize(lines);
}
