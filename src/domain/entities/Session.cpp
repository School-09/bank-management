#include "Session.h"

string Session::serialize() const {
    std::ostringstream oss;

    oss << "SessionId: " << _sessionId << "\n";
    oss << "UserId: " << _userId << "\n";
    oss << "CreatedAt: " << _createdAt << "\n";
    oss << "ExpiredAt: " << _expiredAt << "\n";

    return oss.str();
}

void Session::deserialize(const vector<string>& lines) {
    // 1. Định nghĩa các hành động (Action) cho mỗi Key
    std::map<string, std::function<void(const string&)>> handlers = {
        {"SessionId", [this](const string& val) { 
            _sessionId = val; 
        }},
        {"UserId", [this](const string& val) { 
            _userId = val; 
        }},
        {"CreatedAt", [this](const string& val) { 
            _createdAt = val; 
        }},
        {"ExpiredAt", [this](const string& val) { 
            _expiredAt = val; 
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

bool Session::isExpired() const {
    if (_expiredAt.empty()) return true;

    std::tm tm = {};
    std::istringstream ss(_expiredAt);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

    time_t expired = std::mktime(&tm);
    return std::time(nullptr) > expired;
}