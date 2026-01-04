#ifndef _CREDIT_ACCOUNT_PARSER_H_
#define _CREDIT_ACCOUNT_PARSER_H_

#include "../../entities/accounts/Account.h"
#include "../../entities/accounts/CreditAccount.h"

#include <string>
#include <memory>
#include <regex>

class CreditAccountParser {
public:
    static std::shared_ptr<Account> parseAndCreate(const std::string& info) {
        if (info == "") return std::make_shared<CreditAccount>();
        
        // Regex: "UserId|CreditLimit"
        std::regex re(R"(([^|]+)\|([^|]+))");
        std::smatch match;
        if (std::regex_match(info, match, re)) {
            string userId = match[1];
            int creditLimit = std::stoi(match[2]);

            return std::make_shared<CreditAccount>(
                userId, creditLimit
            );
        }
        throw std::invalid_argument("Invalid CreditAccount data"); //TODO: throw
    }
};

#endif