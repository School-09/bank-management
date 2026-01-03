#include "../BaseFactory.h"
#include "../../entities/transactions/Transaction.h"
#include "DepositParser.h"
#include "WithdrawParser.h"
#include "TransferParser.h"

// Helper class để gọi hàm đăng ký trong constructor
template <typename T>
struct Registrar {
    Registrar(std::string type, typename BaseFactory<T>::CreatorFunc func, std::vector<std::string> fields) {
        BaseFactory<T>::instance().registerType(type, func, fields);
    }
};

// --- KHU VỰC ĐĂNG KÝ CÁC LOẠI Transaction ---

// 1. Đăng ký Deposit
static Registrar<Transaction> regDeposit(
    "deposit", 
    DepositParser::parseAndCreate, 
    {}
);

// 2. Đăng ký Withdraw
static Registrar<Transaction> regWithdraw(
    "withdraw", 
    WithdrawParser::parseAndCreate, 
    {}
);

// 2. Đăng ký Transfer
static Registrar<Transaction> regTransfer(
    "transfer", 
    TransferParser::parseAndCreate, 
    {}
);