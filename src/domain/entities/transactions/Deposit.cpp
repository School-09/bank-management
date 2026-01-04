#include "Deposit.h"
#include "../../../infrastructure/utils/IdUtils.h"

#include <sstream>
#include <regex>
#include <map>
#include <functional>

Deposit::Deposit(
    string userId, int amount,
    string toAccountId
) : Transaction(IdUtils::newTransactionId(), userId, amount),
    _toAccountId(toAccountId) {}

string Deposit::serialize() const {
    std::ostringstream oss;

    oss << "Deposit\n";
    oss << "Id: " << _id << "\n";
    oss << "UserId: " << _userId << "\n";
    oss << "ToAccount" << _toAccountId << "\n";
    oss << "Amount: " << std::to_string(_amount) << "\n";
    oss << "CreatedAt: " << _createdAt << "\n";

    return oss.str();
}

void Deposit::deserialize(const vector<string>& lines) {
    static const std::regex pattern(R"(^(\w+)\s*:\s*(.*)$)");

    std::map<string, std::function<void(const string&)>> handlers = {
        {"Id", [this](const string& val) { _id = val; }},
        {"UserId", [this](const string& val) { _userId = val; }},
        {"ToAccount", [this](const string& val) { _toAccountId = val; }},
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
