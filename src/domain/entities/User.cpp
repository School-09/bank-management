#include "User.h"
#include "../../infrastructure/utils/FileUtils.h"

#include <iomanip>
#include <sstream>
#include <map>
#include <functional>


static string hashPassword(const string& raw) {
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
    oss << "Status: " << (_status == Status::ACTIVE ? "Unlock" : "Lock") << "\n";
    oss << "Role: " << getType() << "\n"; 

    return oss.str();
}

void User::deserialize(const vector<string>& lines) {
    // 1. Định nghĩa các hành động (Action) cho mỗi Key
    std::map<string, std::function<void(const string&)>> handlers = {
        {"Id", [this](const string& val) { 
            _id = val; 
        }},
        {"Username", [this](const string& val) { 
            _username = val; 
        }},
        {"PasswordHash", [this](const string& val) { 
            _passwordHash = val; 
        }},
        {"FullName", [this](const string& val) { 
            _fullName = val; 
        }},
        {"Email", [this](const string& val) { 
            _email = val; 
        }},
        {"Phone", [this](const string& val) { 
            _phone = val; 
        }},
        {"Status", [this](const string& val) { 
            if (val == "Unlock") _status = Status::ACTIVE;
            else _status = Status::LOCKED; 
        }},
        {"Role", [this](const string& val) { 
            if (val == "Customer") _role = Role::CUSTOMER;
            else _role = Role::ADMIN; // Giả sử chỉ có 2 loại
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
