#include "SavingAccount.h"
#include "../../infrastructure/utils/TimeUtils.h"

#include <cmath>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <regex>
#include <map>
#include <functional>

void SavingAccount::accept(AccountVisitor& visitor) { 
    visitor.visit(*this); 
}

void SavingAccount::deposit(int amount) {
    updateBalance();
    _balance += amount;
}

void SavingAccount::withdraw(int amount) {
    updateBalance();
    _balance -= amount;
}

void SavingAccount::updateBalance() {
    // Chuyển _createdAt (string) -> time_t
    std::tm tm = {};
    std::istringstream iss(_createdAt);
    iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (iss.fail()) {
        // Nếu parse lỗi thì bỏ qua
        return;
    }
    time_t createdTime = std::mktime(&tm);

    // Lấy thời gian hiện tại
    time_t now = std::time(nullptr);

    // Tính số ngày chênh lệch
    double days = std::difftime(now, createdTime) / (60 * 60 * 24);

    if (days >= 1) {
        // Lãi suất kép: balance = balance * (1 + rate)^days 
        double newBalance = static_cast<double>(_balance) * std::pow(1.0 + _interestRate, days); 
        _balance = static_cast<int>(newBalance);

        // Cập nhật lại _createdAt thành thời điểm hiện tại
        _createdAt = TimeUtils::toString(now);
    }
}
    
int SavingAccount::getBalance() {
    updateBalance(); 
    return _balance; 
}

string SavingAccount::serialize() const {
    std::ostringstream oss;

    oss << "CheckingAccount\n";
    oss << "Id: " << _id << "\n";
    oss << "UserId: " << _userId << "\n";
    oss << "Balance: " << _balance << "\n";
    oss << "InterestRate: " << _interestRate << "\n";
    oss << "CreatedAt: " << _createdAt << "\n";
    oss << "Status: " << (_status == Status::ACTIVE ? "active" : "locked") << "\n";

    return oss.str();
}

void SavingAccount::deserialize(const vector<string>& lines) {
    static const std::regex pattern(R"(^(\w+)\s*:\s*(.*)$)");

    std::map<string, std::function<void(const string&)>> handlers = {
        {"Id", [this](const string& v) { _id = v; }},
        {"UserId", [this](const string& v) { _userId = v; }},
        {"Balance", [this](const string& v) { _balance = stoi(v); }},
        {"InterestRate", [this](const string& v) { _interestRate = stof(v); }},
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