#include "Notification.h"

shared_ptr<Notification> Notification::create(
    const string& userId,
    const string& message
) {
    auto nf = std::make_shared<Notification>();
    nf->_id = std::to_string(std::rand());
    nf->_userId = userId;
    nf->_message = message;
    nf->_createdAt = TimeUtil::toString(time(nullptr));
    nf->_read = false;
    return nf;
}

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
    // 1. Định nghĩa các hành động (Action) cho mỗi Key
    std::map<string, std::function<void(const string&)>> handlers = {
        {"Id", [this](const string& val) { 
            _id = val; 
        }},
        {"UserId", [this](const string& val) { 
            _userId = val; 
        }},
        {"Message", [this](const string& val) { 
            _message = val; 
        }},
        {"CreatedAt", [this](const string& val) { 
            _createdAt = val; 
        }},
        {"Read", [this](const string& val) { 
            _read = (val == "true"); 
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