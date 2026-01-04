#include "../BaseFactory.h"
#include "../../entities/cards/Card.h"
#include "DebitCardParser.h"
#include "CreditCardParser.h"

// Helper class để gọi hàm đăng ký trong constructor
template <typename T>
struct Registrar {
    Registrar(std::string type, typename BaseFactory<T>::CreatorFunc func, std::vector<std::string> fields) {
        BaseFactory<T>::instance().registerType(type, func, fields);
    }
};

// --- KHU VỰC ĐĂNG KÝ CÁC LOẠI CARD ---

// 1. Đăng ký Debit Card
static Registrar<Card> regDebit(
    "debit", 
    DebitCardParser::parseAndCreate, 
    {}
);

// 2. Đăng ký Credit Card
static Registrar<Card> regCredit(
    "credit", 
    CreditCardParser::parseAndCreate, 
    {}
);