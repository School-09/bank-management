#include "CreditAccount.h"
#include <stdexcept>

bool CreditAccount::canSpend(double amount) const {
    if (amount <= 0) return false;
    return _used + amount <= _creditLimit;
}

void CreditAccount::spend(double amount) {
    if (amount <= 0)
        throw std::runtime_error("Invalid spend amount");

    if (!canSpend(amount))
        throw std::runtime_error("Credit limit exceeded");

    _used += amount;
}

void CreditAccount::pay(double amount) {
    if (amount <= 0)
        throw std::runtime_error("Invalid payment amount");

    // Không cho dư âm (overpay)
    if (amount > _used)
        _used = 0;
    else
        _used -= amount;
}


string CreditAccount::serialize() const {
    std::ostringstream oss;

    oss << Account::serialize();
    oss << "CreditLimit: " << _creditLimit << "\n";
    oss << "Used: " << _used << "\n";

    return oss.str();
}

void CreditAccount::deserialize(const vector<string>& lines) {
    Account::deserialize(lines);

    std::map<string, std::function<void(const string&)>> handlers = {
        {"CreditLimit", [this](const string& val) { 
            _creditLimit = stod(val); 
        }},
        {"Used", [this](const string& val) { 
            _used = stod(val); 
        }}
    };

    for (const string& line : lines) { // TODO tối ưu, duyệt lại các chuỗi đã xử lí rồi -> chain of responsibility
        string key, val;
        if (!FileUtils::extract_key_value(line, key, val)) continue;

        // Tìm key trong map và thực thi handler tương ứng
        auto it = handlers.find(key);
        if (it != handlers.end()) {
            it->second(val); // Gọi hàm xử lý (handler)
        }
        // else: bỏ qua các key không hợp lệ
    }
}