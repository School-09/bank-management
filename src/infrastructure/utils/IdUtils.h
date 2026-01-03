#ifndef _ID_UTILS_H_
#define _ID_UTILS_H_

#include "UUIDGenerator.h"
#include "BusinessIdGenerator.h"

class IdUtils {
public:
    static std::string newSessionId() {
        return UUIDGenerator::generateV4();
    }

    static std::string newTokenId() {
        return UUIDGenerator::generateV4();
    }

    static std::string newTransactionId() {
        return UUIDGenerator::generateV4();
    }

    static std::string newNotificationId() {
        return UUIDGenerator::generateV4();
    }

    static std::string newCustomerId() {
        return BusinessIdGenerator::generate(BusinessIdType::CUSTOMER);
    }

    static std::string newSavingAccountId() {
        return BusinessIdGenerator::generate(BusinessIdType::SAVING_ACCOUNT);
    }

    static std::string newCheckingAccountId() {
        return BusinessIdGenerator::generate(BusinessIdType::CHECKING_ACCOUNT);
    }

    static std::string newCreditAccountId() {
        return BusinessIdGenerator::generate(BusinessIdType::CREDIT_ACCOUNT);
    }

    static std::string newDebitCardId() {
        return BusinessIdGenerator::generate(BusinessIdType::DEBIT_CARD);
    }

    static std::string newCreditCardId() {
        return BusinessIdGenerator::generate(BusinessIdType::CREDIT_CARD);
    }
};


#endif