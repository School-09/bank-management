#include "Notification.h"
#include "../../infrastructure/utils/TimeUtils.h"
#include "../../infrastructure/utils/IdUtils.h"

#include <sstream>
#include <regex>
#include <map>
#include <functional>

Notification::Notification(
    string userId, string message
) : _id(IdUtils::newNotificationId()),
    _userId(userId),
    _message(message),
    _createdAt(TimeUtils::toString(time(nullptr))),
    _read(false) {}

string Notification::serialize() const {
    std::ostringstream oss;

    oss << "Id: " << _id << "\n";
    oss << "UserId: " << _userId << "\n";
    oss << "Message: " << _message << "\n";
    oss << "CreatedAt: " << _createdAt << "\n";
    oss << "Read: " << std::to_string(_read) << "\n";

    return oss.str();
}

void Notification::deserialize(const vector<string>& lines) {
    static const std::regex pattern(R"(^(\w+)\s*:\s*(.*)$)");

    std::map<string, std::function<void(const string&)>> handlers = {
        {"Id", [this](const string& val) { _id = val; }},
        {"UserId", [this](const string& val) { _userId = val; }},
        {"Message", [this](const string& val) { _message = val; }},
        {"CreatedAt", [this](const string& val) { _createdAt = val; }},
        {"Read", [this](const string& val) { _read = (val == "true"); }}
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