#include "CheckingAccount.h"
#include "../../infrastructure/utils/FileUtils.h"

#include <sstream>
#include <map>
#include <functional>


string CheckingAccount::serialize() const {
    std::ostringstream oss;

    oss << Account::serialize();
    oss << "OverdraftLimit: " << _overdraftLimit << "\n";

    return oss.str();
}

void CheckingAccount::deserialize(const vector<string>& lines) {
    Account::deserialize(lines);

    std::map<string, std::function<void(const string&)>> handlers = {
        {"OverdraftLimit", [this](const string& val) { 
            _overdraftLimit = stod(val); 
        }}
    };

    for (const string& line : lines) { // TODO tối ưu, duyệt lại các chuỗi đã xử lí rồi -> chain of responsibility
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