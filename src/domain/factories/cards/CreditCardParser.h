#ifndef _CREDIT_CARD_PARSER_H_
#define _CREDIT_CARD_PARSER_H_

#include "../../entities/cards/Card.h"
#include "../../entities/cards/CreditCard.h"

#include <string>
#include <memory>
#include <regex>

class CreditCardParser {
public:
    static std::shared_ptr<Card> parseAndCreate(const std::string& inf) {
        if (inf == "") return std::make_shared<CreditCard>();
        
        // Regex: "UserId|AccountId"
        std::regex re(R"(([^|]+)\|([^|]+))");
        std::smatch match;
        if (std::regex_match(inf, match, re)) {
            string userId = match[1];
            string accountId = match[2];

            return std::make_shared<CreditCard>(
                userId, accountId
            );
        }
        throw std::invalid_argument("Invalid CreditCard data");
    }
};

#endif