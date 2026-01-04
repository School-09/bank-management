#include "Withdraw.h"
#include "../../../infrastructure/utils/IdUtils.h"

#include <sstream>
#include <regex>
#include <map>
#include <functional>

Withdraw::Withdraw(
    string userId, int amount,
    string fromAccountId
) : Transaction(IdUtils::newTransactionId(), userId, amount),
    _fromAccountId(fromAccountId) {}

string Withdraw::serialize() const {
    std::ostringstream oss;

    oss << "Withdraw\n";
    oss << "Id: " << _id << "\n";
    oss << "UserId: " << _userId << "\n";
    oss << "FromAccount" << _fromAccountId << "\n";
    oss << "Amount: " << std::to_string(_amount) << "\n";
    oss << "CreatedAt: " << _createdAt << "\n";

    return oss.str();
}

void Withdraw::deserialize(const vector<string>& lines) {
    static const std::regex pattern(R"(^(\w+)\s*:\s*(.*)$)");

    std::map<string, std::function<void(const string&)>> handlers = {
        {"Id", [this](const string& val) { _id = val; }},
        {"UserId", [this](const string& val) { _userId = val; }},
        {"FromAccount", [this](const string& val) { _fromAccountId = val; }},
        {"Amount", [this](const string& val) { _amount = stod(val); }},
        {"CreatedAt", [this](const string& val) { _createdAt = val; }}
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