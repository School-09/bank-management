#ifndef _TRANSFER_PARSER_H_
#define _TRANSFER_PARSER_H_

#include "../../entities/transactions/Transaction.h"
#include "../../entities/transactions/Transfer.h"

#include <string>
#include <memory>
#include <regex>

class TransferParser {
public:
    static std::shared_ptr<Transaction> parseAndCreate(const std::string& info) {
        if (info == "") return std::make_shared<Transfer>();
        
        // Regex: "UserId|FromAccountId|ToAccountId|Amount"
        std::regex re(R"(([^|]+)\|([^|]+)\|([^|]+)\|([^|]+))");
        std::smatch match;
        if (std::regex_match(info, match, re)) {
            string userId = match[1];
            string fromAccountId = match[2];
            string toAccountId = match[3];
            int amount = std::stoi(match[4]);

            return std::make_shared<Transfer>(
                userId, amount, fromAccountId, toAccountId
            );
        }
        throw std::invalid_argument("Invalid Transfer data"); //TODO: throw
    }
};

#endif