#include "SavingAccount.h"
#include "../../infrastructure/utils/FileUtils.h"

#include <map>
#include <functional>


string SavingAccount::serialize() const {
    std::ostringstream oss;

    oss << Account::serialize();
    oss << "InterestRate: " << _interestRate << "\n";

    return oss.str();
}

void SavingAccount::deserialize(const vector<string>& lines) {
    Account::deserialize(lines);

    std::map<string, std::function<void(const string&)>> handlers = {
        {"InterestRate", [this](const string& val) { 
            _interestRate = stod(val); 
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