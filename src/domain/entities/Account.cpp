#include "Account.h"
#include "../../infrastructure/utils/FileUtils.h"

#include <iomanip>
#include <sstream>
#include <regex>
#include <map>
#include <functional>

string Account::serialize() const {
    std::ostringstream oss;

    oss << "Id: " << _id << "\n";
    oss << "UserId: " << _userId << "\n";
    oss << "CreatedAt: " << _createdAt << "\n";
    oss << "Status: " << (_status == Status::ACTIVE ? "active" : "locked") << "\n";

    return oss.str();
}

void Account::deserialize(const vector<string>& lines) {
    static const std::regex pattern(R"(^(\w+)\s*:\s*(.*)$)");

    std::map<string, std::function<void(const string&)>> handlers = {
        {"Id", [this](const string& v) { _id = v; }},
        {"UserId", [this](const string& v) { _userId = v; }},
        {"CreatedAt", [this](const string& v) { _createdAt= v; }},
        {"Status", [this](const string& v) {
            _status = (v == "active") ? Status::ACTIVE : Status::LOCKED;
        }}
    };

    for (const string& line : lines) {
        std::smatch match;
        if (!std::regex_match(line, match, pattern))
            continue;

        const string& key = match[1];
        const string& value = match[2];

        auto it = handlers.find(key);
        if (it != handlers.end()) {
            it->second(value);
        }
    }
}