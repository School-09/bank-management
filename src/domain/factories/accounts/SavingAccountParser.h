#ifndef _SAVING_ACCOUNT_PARSER_H_
#define _SAVING_ACCOUNT_PARSER_H_

#include "../../entities/accounts/Account.h"
#include "../../entities/accounts/SavingAccount.h"

#include <string>
#include <memory>
#include <regex>

class SavingAccountParser {
public:
    static std::shared_ptr<Account> parseAndCreate(const std::string& info) {
        if (info == "") return std::make_shared<SavingAccount>();
        
        // Regex: "UserId|Balance"
        std::regex re(R"(([^|]+)\|([^|]+))");
        std::smatch match;
        if (std::regex_match(info, match, re)) {
            string userId = match[1];
            int balance = std::stoi(match[2]);

            return std::make_shared<SavingAccount>(
                userId, balance
            );
        }
        return std::make_shared<SavingAccount>();
    }
};

#endif