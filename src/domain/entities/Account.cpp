#include "Account.h"
#include "../../infrastructure/utils/FileUtils.h"

#include <sstream>
#include <map>
#include <functional>


void Account::increaseBalance(double amount) {
    _balance += amount;
}

void Account::decreaseBalance(double amount) {
    _balance -= amount;
}

string Account::serialize() const {
    std::ostringstream oss;

    oss << "Id: " << _id << "\n";
    oss << "UserId: " << _userId << "\n";
    oss << "Balance: " << _balance << "\n";
    oss << "Active: " << (_active ? "true" : "false") << "\n";
    oss << "CreatedAt: " << _createdAt << "\n";
    oss << "Type: " << getType() << "\n"; // visit

    return oss.str();
}

void Account::deserialize(const vector<string>& lines) {
    // 1. Định nghĩa các hành động (Action) cho mỗi Key
    std::map<string, std::function<void(const string&)>> handlers = {
        {"Id", [this](const string& val) { 
            _id = val; 
        }},
        {"UserId", [this](const string& val) { 
            _userId = val; 
        }},
        {"Balance", [this](const string& val) { 
            _balance = stod(val); 
        }},
        {"Active", [this](const string& val) { 
            _active = (val == "true" ? true : false); 
        }},
        {"CreatedAt", [this](const string& val) { 
            _createdAt = val; 
        }},
        {"Type", [this](const string& val) { 
            _type = (val == "SAVING" ? AccountType::SAVING : AccountType::CHECKING); 
        }}
    };

    // 2. Lặp qua các dòng và xử lý
    for (const string& line : lines) {
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