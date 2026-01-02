#include "CreditAccount.h"

#include <sstream>
#include <map>
#include <regex>
#include <functional>
#include <stdexcept>

void CreditAccount::accept(AccountVisitor& visitor) { 
    visitor.visit(*this); 
}

void CreditAccount::deposit(int amount) { // pay
    if (amount <= 0)
        throw std::runtime_error("Invalid payment amount");

    // Không cho dư âm (overpay)
    if (amount > _used)
        _used = 0;
    else
        _used -= amount;
}

void CreditAccount::withdraw(int amount) { // spend
    if (amount <= 0)
        throw std::runtime_error("Invalid spend amount");

    _used += amount;
}

string CreditAccount::serialize() const {
    std::ostringstream oss;

    oss << "CreditAccount\n";
    oss << "Id: " << _id << "\n";
    oss << "UserId: " << _userId << "\n";
    oss << "CreditLimit: " << _creditLimit << "\n";
    oss << "Used: " << _used << "\n";
    oss << "CreatedAt: " << _createdAt << "\n";
    oss << "Status: " << (_status == Status::ACTIVE ? "active" : "locked") << "\n";

    return oss.str();
}

void CreditAccount::deserialize(const vector<string>& lines) {
    static const std::regex pattern(R"(^(\w+)\s*:\s*(.*)$)");

    std::map<string, std::function<void(const string&)>> handlers = {
        {"Id", [this](const string& v) { _id = v; }},
        {"UserId", [this](const string& v) { _userId = v; }},
        {"CreditLimit", [this](const string& v) { _creditLimit = stoi(v); }},
        {"Used", [this](const string& v) { _used = stoi(v); }},
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