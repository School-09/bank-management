#include "Card.h"
#include "../../../infrastructure/utils/TimeUtils.h"

#include <ctime>
#include <cstdlib>
#include <regex>
#include <sstream>
#include <map>
#include <functional>

static std::string genCardNumber() {
    return "2026-" + std::to_string(1000 + std::rand() % 9000) +
           "-" + std::to_string(1000 + std::rand() % 9000) +
           "-" + std::to_string(1000 + std::rand() % 9000);
}

Card::Card(
    string id, string userId, string accountId
) : _id(id),
    _userId(userId),
    _accountId(accountId),
    _cardNumber(genCardNumber()),
    _createdAt(TimeUtils::toString(time(nullptr))),
    _expiredAt(TimeUtils::toString(time(nullptr) + 315360000)), // 10 năm
    _status(Status::ACTIVE) {}

string Card::serialize() const {
    std::ostringstream oss;

    oss << "Id: " << _id << "\n";
    oss << "UserId: " << _userId << "\n";
    oss << "AccountId: " << _accountId << "\n";
    oss << "CardNumber: " << _cardNumber << "\n";
    oss << "ExpiredAt: " << _expiredAt << "\n";
    oss << "Status: " << (_status == Status::ACTIVE ? "active" : "locked") << "\n";

    return oss.str();
}

void Card::deserialize(const vector<string>& lines) {
    static const std::regex pattern(R"(^(\w+)\s*:\s*(.*)$)");

    std::map<string, std::function<void(const string&)>> handlers = {
        {"Id", [this](const string& val) { _id = val; }},
        {"UserId", [this](const string& val) { _userId = val; }},
        {"AccountId", [this](const string& val) { _accountId = val; }},
        {"CardNumber", [this](const string& val) { _cardNumber = val; }},
        {"ExpiredAt", [this](const string& val) { _expiredAt = val; }},
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
