#ifndef _CREDIT_CARD_PARSER_H_
#define _CREDIT_CARD_PARSER_H_

#include "../../entities/cards/Card.h"
#include "../../entities/cards/CreditCard.h"

#include <string>
#include <memory>
#include <regex>

class CreditCardParser {
public:
    static std::shared_ptr<Card> parseAndCreate(const std::string& info) {
        if (info == "") return std::make_shared<CreditCard>();
        
        // Regex: "UserId|AccountId"
        std::regex re(R"(([^|]+)\|([^|]+))");
        std::smatch match;
        if (std::regex_match(info, match, re)) {
            string userId = match[1];
            string accountId = match[2];

            return std::make_shared<CreditCard>(
                userId, accountId
            );
        }
        return std::make_shared<CreditCard>();
    }
};

#endif