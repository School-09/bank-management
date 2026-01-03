#include "../BaseFactory.h"
#include "../../entities/users/User.h"
#include "AdminParser.h"
#include "CustomerParser.h"

// Helper class để gọi hàm đăng ký trong constructor
template <typename T>
struct Registrar {
    Registrar(std::string type, typename BaseFactory<T>::CreatorFunc func, std::vector<std::string> fields) {
        BaseFactory<T>::instance().registerType(type, func, fields);
    }
};

// --- KHU VỰC ĐĂNG KÝ CÁC LOẠI User ---

// 1. Đăng ký Admin
static Registrar<User> regChecking(
    "admin", 
    AdminParser::parseAndCreate, 
    {"FullName", "Phone", "Password"}
);

// 2. Đăng ký Customer
static Registrar<User> regSaving(
    "customer", 
    CustomerParser::parseAndCreate, 
    {"FullName", "Phone", "Password"}
);