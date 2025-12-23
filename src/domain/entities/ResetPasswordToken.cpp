#include "ResetPasswordToken.h"

bool ResetPasswordToken::isExpired() const {
    if (_expiredAt.empty())
        return true;

    std::tm tm = {};
    std::istringstream iss(_expiredAt);

    iss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (iss.fail())
        return true;  // format sai → coi như hết hạn

    time_t expiredTime = std::mktime(&tm);
    time_t now = std::time(nullptr);

    return now > expiredTime;
}

string ResetPasswordToken::serialize() const {
    std::ostringstream oss;

    oss << "TokenId: " << _tokenId << "\n";
    oss << "UserId: " << _userId << "\n";
    oss << "CreatedAt: " << _createdAt << "\n";
    oss << "ExpiredAt: " << _expiredAt << "\n";
    oss << "Used: " << (_used ? "true" : "false") << "\n";

    return oss.str();
}

void ResetPasswordToken::deserialize(const vector<string>& lines) {
    // 1. Định nghĩa các hành động (Action) cho mỗi Key
    std::map<string, std::function<void(const string&)>> handlers = {
        {"TokenId", [this](const string& val) { 
            _tokenId = val; 
        }},
        {"UserId", [this](const string& val) { 
            _userId = val; 
        }},
        {"CreatedAt", [this](const string& val) { 
            _createdAt = val; 
        }},
        {"ExpiredAt", [this](const string& val) { 
            _expiredAt = val; 
        }},
        {"Used", [this](const string& val) { 
            _used = (val == "true" ? true : false); 
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
