#ifndef _BUSINESS_ID_GENERATOR_H_
#define _BUSINESS_ID_GENERATOR_H_

#include <string>

enum class BusinessIdType {
    CUSTOMER,
    SAVING_ACCOUNT,
    CHECKING_ACCOUNT,
    CREDIT_ACCOUNT,
    DEBIT_CARD,
    CREDIT_CARD
};

class BusinessIdGenerator {
public:
    static std::string generate(
        BusinessIdType type,
        const std::string& branchCode = "VN"
    );

private:
    static std::string typeCode(BusinessIdType type);
    static std::string randomDigits(int length);
    static char checksum(const std::string& raw);
};


#endif