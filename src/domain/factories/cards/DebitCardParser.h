#ifndef _DEBIT_CARD_PARSER_H_
#define _DEBIT_CARD_PARSER_H_

#include "../../entities/cards/Card.h"
#include "../../entities/cards/DebitCard.h"

#include <string>
#include <memory>
#include <regex>

class DebitCardParser {
public:
    static std::shared_ptr<Card> parseAndCreate(const std::string& info) {
        if (info == "") return std::make_shared<DebitCard>();
        
        // Regex: "UserId|AccountId"
        std::regex re(R"(([^|]+)\|([^|]+))");
        std::smatch match;
        if (std::regex_match(info, match, re)) {
            string userId = match[1];
            string accountId = match[2];

            return std::make_shared<DebitCard>(
                userId, accountId
            );
        }
        throw std::invalid_argument("Invalid DebitCard data"); //TODO: throw
    }
};

#endif