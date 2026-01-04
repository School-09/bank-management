#include "Session.h"
#include "../../infrastructure/utils/TimeUtils.h"
#include "../../infrastructure/utils/IdUtils.h"

#include <ctime>
#include <sstream>
#include <regex>
#include <map>
#include <functional>

Session::Session(
    string userId, string role
) : _userId(userId),
    _role(role),
    _sessionId(IdUtils::newSessionId()),
    _createdAt(TimeUtils::toString(time(nullptr))),
    _expiredAt(TimeUtils::toString(time(nullptr) + 3600)) {}

bool Session::isExpired() const {
    if (_expiredAt.empty()) return true;

    std::tm tm = {};
    std::istringstream ss(_expiredAt);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (ss.fail()) return true;  // format sai → coi như hết hạn

    time_t expired = std::mktime(&tm);
    time_t now = std::time(nullptr);

    return now > expired;
}

string Session::serialize() const {
    std::ostringstream oss;

    oss << "SessionId: " << _sessionId << "\n";
    oss << "UserId: " << _userId << "\n";
    oss << "Role: " << _role << "\n";
    oss << "CreatedAt: " << _createdAt << "\n";
    oss << "ExpiredAt: " << _expiredAt << "\n";

    return oss.str();
}

void Session::deserialize(const vector<string>& lines) {
    static const std::regex pattern(R"(^(\w+)\s*:\s*(.*)$)");

    std::map<string, std::function<void(const string&)>> handlers = {
        {"SessionId", [this](const string& v) { _sessionId = v; }},
        {"UserId", [this](const string& v) { _userId = v; }},
        {"Role", [this](const string& v) { _role = v; }},
        {"CreatedAt", [this](const string& v) { _createdAt = v; }},
        {"ExpiredAt", [this](const string& v) { _expiredAt = v; }}
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
