#include "CheckingAccount.h"
#include "../../../infrastructure/utils/IdUtils.h"

#include <iostream>
#include <sstream>
#include <regex>
#include <map>
#include <functional>

CheckingAccount::CheckingAccount(
    string userId, int balance
) : Account(IdUtils::newCheckingAccountId(), userId),
    _balance(balance) {}

void CheckingAccount::accept(IAccountVisitor& visitor) { 
    visitor.visit(*this); 
}

void CheckingAccount::deposit(int amount) {
    _balance += amount;
}

void CheckingAccount::withdraw(int amount) {
    _balance -= amount;
}

string CheckingAccount::serialize() const {
    std::ostringstream oss;

    oss << "Checking\n";
    oss << "Id: " << _id << "\n";
    oss << "UserId: " << _userId << "\n";
    oss << "Balance: " << _balance << "\n";
    oss << "CreatedAt: " << _createdAt << "\n";
    oss << "Status: " << (_status == Status::ACTIVE ? "active" : "locked") << "\n";

    return oss.str();
}

void CheckingAccount::deserialize(const vector<string>& lines) {
    static const std::regex pattern(R"(^(\w+)\s*:\s*(.*)$)");

    std::map<string, std::function<void(const string&)>> handlers = {
        {"Id", [this](const string& v) { _id = v; }},
        {"UserId", [this](const string& v) { _userId = v; }},
        {"Balance", [this](const string& v) { _balance = stoi(v); }},
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