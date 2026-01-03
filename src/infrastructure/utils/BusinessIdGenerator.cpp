#include "BusinessIdGenerator.h"
#include <random>
#include <numeric>

std::string BusinessIdGenerator::generate(
    BusinessIdType type,
    const std::string& branchCode
) {
    std::string body =
        branchCode + "-" +
        typeCode(type) + "-" +
        randomDigits(5);

    char check = checksum(body);
    return body + "-" + check;
}

std::string BusinessIdGenerator::typeCode(BusinessIdType type) {
    switch (type) {
        case BusinessIdType::CUSTOMER:         return "CUS";
        case BusinessIdType::SAVING_ACCOUNT:   return "SAV";
        case BusinessIdType::CHECKING_ACCOUNT: return "CHK";
        case BusinessIdType::CREDIT_ACCOUNT:   return "CRD";
        case BusinessIdType::DEBIT_CARD:       return "DBC";
        case BusinessIdType::CREDIT_CARD:      return "CRC";
    }
    return "UNK";
}

std::string BusinessIdGenerator::randomDigits(int length) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 9);

    std::string s;
    for (int i = 0; i < length; ++i)
        s += char('0' + dis(gen));

    return s;
}

char BusinessIdGenerator::checksum(const std::string& raw) {
    int sum = 0;
    for (char c : raw) {
        if (std::isdigit(c))
            sum += c - '0';
        else
            sum += c;
    }
    return 'A' + (sum % 26);
}
