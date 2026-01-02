#include "User.h"

#include <iomanip>
#include <sstream>
#include <regex>
#include <map>
#include <functional>

User::User(
    string id,
    string username,
    string rawPassword,
    string fullName,
    string email,
    string phone
) : _id(id),
    _username(username),
    _passwordHash(hashPassword(rawPassword)),
    _fullName(fullName),
    _email(email),
    _phone(phone) {}

static string hashPassword(const string& raw) { // TODO: hash rồi thì ko nhớ pass để test
    const uint64_t FNV_prime = 1099511628211u;
    const uint64_t offset_basis = 1469598103934665603u;

    uint64_t hash = offset_basis;
    for (char c : raw) {
        hash ^= static_cast<unsigned char>(c);
        hash *= FNV_prime;
    }

    // chuyển thành chuỗi hex
    std::string result;
    for (int i = 0; i < 8; i++) {
        unsigned char byte = (hash >> (i * 8)) & 0xff;
        char buf[3];
        sprintf(buf, "%02x", byte);
        result.insert(0, buf);
    }
    return result;
}

void User::setPassword(const string& rawPassword) {
    _passwordHash = hashPassword(rawPassword);
}

bool User::verifyPassword(const string& rawPassword) const {
    return _passwordHash == hashPassword(rawPassword);
}

string User::serialize() const {
    std::ostringstream oss;

    oss << "Id: " << _id << "\n";
    oss << "Username: " << _username << "\n";
    oss << "PasswordHash: " << _passwordHash << "\n";
    oss << "FullName: " << _fullName << "\n";
    oss << "Email: " << _email << "\n";
    oss << "Phone: " << _phone << "\n";
    oss << "Status: " << (_status == Status::ACTIVE ? "active" : "locked") << "\n";

    return oss.str();
}

void User::deserialize(const vector<string>& lines) {
    static const std::regex pattern(R"(^(\w+)\s*:\s*(.*)$)");

    std::map<string, std::function<void(const string&)>> handlers = {
        {"Id", [this](const string& v) { _id = v; }},
        {"Username", [this](const string& v) { _username = v; }},
        {"PasswordHash", [this](const string& v) { _passwordHash = v; }},
        {"FullName", [this](const string& v) { _fullName = v; }},
        {"Email", [this](const string& v) { _email = v; }},
        {"Phone", [this](const string& v) { _phone = v; }},
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
