#include "ResetPasswordToken.h"

#include <ctime>
#include <sstream>
#include <regex>
#include <map>
#include <functional>
#include <filesystem>

bool ResetPasswordToken::isExpired() const {
    if (_expiredAt.empty()) return true;

    std::tm tm = {};
    std::istringstream ss(_expiredAt);

    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (ss.fail()) return true;  // format sai → coi như hết hạn

    time_t expired = std::mktime(&tm);
    time_t now = std::time(nullptr);

    return now > expired;
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
    static const std::regex pattern(R"(^(\w+)\s*:\s*(.*)$)");

    std::map<string, std::function<void(const string&)>> handlers = {
        {"TokenId", [this](const string& val) { _tokenId = val; }},
        {"UserId", [this](const string& val) { _userId = val; }},
        {"CreatedAt", [this](const string& val) { _createdAt = val; }},
        {"ExpiredAt", [this](const string& val) { _expiredAt = val; }},
        {"Used", [this](const string& val) { _used = (val == "true" ? true : false); }}
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
