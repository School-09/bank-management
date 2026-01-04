#ifndef _DEPOSIT_PARSER_H_
#define _DEPOSIT_PARSER_H_

#include "../../entities/transactions/Transaction.h"
#include "../../entities/transactions/Deposit.h"

#include <string>
#include <memory>
#include <regex>

class DepositParser {
public:
    static std::shared_ptr<Transaction> parseAndCreate(const std::string& info) {
        if (info == "") return std::make_shared<Deposit>();
        
        // Regex: "UserId|ToAccountId|Amount"
        std::regex re(R"(([^|]+)\|([^|]+)\|([^|]+))");
        std::smatch match;
        if (std::regex_match(info, match, re)) {
            string userId = match[1];
            string toAccountId = match[2];
            int amount = std::stoi(match[3]);

            return std::make_shared<Deposit>(
                userId, amount, toAccountId
            );
        }
        return std::make_shared<Deposit>();
    }
};

#endif