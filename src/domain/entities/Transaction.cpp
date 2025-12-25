#include "Transaction.h"

// ================= FACTORY =================

shared_ptr<Transaction> Transaction::createDeposit(
    const string& userId,
    const string& accountId,
    double amount
) {
    auto tx = std::make_shared<Transaction>();
    tx->_id = std::to_string(std::rand());
    tx->_userId = userId;
    tx->_toAccountId = accountId;
    tx->_amount = amount;
    tx->_type = "Deposit";
    tx->_createdAt = TimeUtil::toString(time(nullptr));
    return tx;
}

shared_ptr<Transaction> Transaction::createWithdraw(
    const string& userId,
    const string& accountId,
    double amount
) {
    auto tx = std::make_shared<Transaction>();
    tx->_id = std::to_string(std::rand());
    tx->_userId = userId;
    tx->_fromAccountId = accountId;
    tx->_amount = amount;
    tx->_type = "Withdraw";
    tx->_createdAt = TimeUtil::toString(time(nullptr));
    return tx;
}

shared_ptr<Transaction> Transaction::createTransfer(
    const string& userId,
    const string& fromId,
    const string& toId,
    double amount
) {
    auto tx = std::make_shared<Transaction>();
    tx->_id = std::to_string(std::rand());
    tx->_userId = userId;
    tx->_fromAccountId = fromId;
    tx->_toAccountId = toId;
    tx->_amount = amount;
    tx->_type = "Transfer";
    tx->_createdAt = TimeUtil::toString(time(nullptr));
    return tx;
}

// ================= SERIALIZATION =================

string Transaction::serialize() const {
    std::ostringstream oss;

    oss << "Id: " << _id << "\n";
    oss << "UserId: " << _userId << "\n";
    oss << "FromAccountId: " << _fromAccountId << "\n";
    oss << "ToAccountId: " << _toAccountId << "\n";
    oss << "Amount: " << std::to_string(_amount) << "\n";
    oss << "Type: " << _type << "\n";
    oss << "CreatedAt: " << _createdAt << "\n";

    return oss.str();
}

void Transaction::deserialize(const vector<string>& lines) {
    // 1. Định nghĩa các hành động (Action) cho mỗi Key
    std::map<string, std::function<void(const string&)>> handlers = {
        {"Id", [this](const string& val) { 
            _id = val; 
        }},
        {"UserId", [this](const string& val) { 
            _userId = val; 
        }},
        {"FromAccountId", [this](const string& val) { 
            _fromAccountId = val; 
        }},
        {"ToAccountId", [this](const string& val) { 
            _toAccountId = val; 
        }},
        {"Amount", [this](const string& val) { 
            _amount = stod(val); 
        }},
        {"Type", [this](const string& val) { 
            _type = val; 
        }},
        {"CreatedAt", [this](const string& val) { 
           _createdAt = val; 
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
