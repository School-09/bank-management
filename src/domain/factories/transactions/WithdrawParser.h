#ifndef _WITHDRAW_PARSER_H_
#define _WITHDRAW_PARSER_H_

#include "../../entities/transactions/Transaction.h"
#include "../../entities/transactions/Withdraw.h"

#include <string>
#include <memory>
#include <regex>

class WithdrawParser {
public:
    static std::shared_ptr<Transaction> parseAndCreate(const std::string& info) {
        if (info == "") return std::make_shared<Withdraw>();
        
        // Regex: "UserId|FromAccountId|Amount"
        std::regex re(R"(([^|]+)\|([^|]+)\|([^|]+))");
        std::smatch match;
        if (std::regex_match(info, match, re)) {
            string userId = match[1];
            string fromAccountId = match[2];
            int amount = std::stoi(match[3]);

            return std::make_shared<Withdraw>(
                userId, amount, fromAccountId
            );
        }
        throw std::invalid_argument("Invalid Withdraw data"); //TODO: throw
    }
};

#endif