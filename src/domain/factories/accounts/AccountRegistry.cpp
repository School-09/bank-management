#include "../BaseFactory.h"
#include "../../entities/accounts/Account.h"
#include "CheckingAccountParser.h"
#include "SavingAccountParser.h"
#include "CreditAccountParser.h"

// Helper class để gọi hàm đăng ký trong constructor
template <typename T>
struct Registrar {
    Registrar(std::string type, typename BaseFactory<T>::CreatorFunc func, std::vector<std::string> fields) {
        BaseFactory<T>::instance().registerType(type, func, fields);
    }
};

// --- KHU VỰC ĐĂNG KÝ CÁC LOẠI ACCOUNT ---

// 1. Đăng ký Checking Account
static Registrar<Account> regChecking(
    "checking", 
    CheckingAccountParser::parseAndCreate, 
    {"Balance"}
);

// 2. Đăng ký Saving Account
static Registrar<Account> regSaving(
    "saving", 
    SavingAccountParser::parseAndCreate, 
    {"Balance"}
);

// 2. Đăng ký Credit Account (Ví dụ)
static Registrar<Account> regCredit(
    "credit", 
    CreditAccountParser::parseAndCreate, 
    {"CreditLimit"}
);