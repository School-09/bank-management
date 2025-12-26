#include "Card.h"
#include <ctime>
#include <cstdlib>

static std::string genId(const std::string& prefix) {
    return prefix + "_" + std::to_string(std::rand());
}

static std::string genCardNumber() {
    return "9704-" + std::to_string(1000 + std::rand() % 9000) +
           "-" + std::to_string(1000 + std::rand() % 9000) +
           "-" + std::to_string(1000 + std::rand() % 9000);
}

static std::string genCVV() {
    return std::to_string(100 + std::rand() % 900);
}

static std::string genExpiredAt() {
    return "12/29"; // demo
}

Card::Card() {
    _id = genId("card");
    _cardNumber = genCardNumber();
    _cvv = genCVV();
    _expiredAt = genExpiredAt();
    _blocked = false;
}

string Card::serialize() const {
    std::ostringstream oss;

    oss << "Id: " << _id << "\n";
    oss << "UserId: " << _userId << "\n";
    oss << "AccountId: " << _accountId << "\n";
    oss << "CardNumber: " << _cardNumber << "\n";
    oss << "ExpiredAt: " << _expiredAt << "\n";
    oss << "CVV: " << _cvv << "\n";
    oss << "Blocked: " << (_blocked ? "true" : "false") << "\n";

    return oss.str();
}

void Card::deserialize(const vector<string>& lines) {
    // 1. Định nghĩa các hành động (Action) cho mỗi Key
    std::map<string, std::function<void(const string&)>> handlers = {
        {"Id", [this](const string& val) { 
            _id = val; 
        }},
        {"UserId", [this](const string& val) { 
            _userId = val; 
        }},
        {"AccountId", [this](const string& val) { 
            _accountId = val; 
        }},
        {"CardNumber", [this](const string& val) { 
            _cardNumber = val; 
        }},
        {"ExpiredAt", [this](const string& val) { 
            _expiredAt = val; 
        }},
        {"CVV", [this](const string& val) { 
            _cvv = val;
        }},
        {"Blocked", [this](const string& val) { 
            (val == "true" ? _blocked = 1 : 0);
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
