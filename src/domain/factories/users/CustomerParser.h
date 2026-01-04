#ifndef _CUSTOMER_PARSER_H_
#define _CUSTOMER_PARSER_H_

#include "../../entities/users/User.h"
#include "../../entities/users/Customer.h"

#include <string>
#include <memory>
#include <regex>

class CustomerParser {
public:
    static std::shared_ptr<User> parseAndCreate(const std::string& info) {
        if (info == "") return std::make_shared<Customer>();
        
        // Regex: "UserName|FullName|Email|Phone|Password"
        std::regex re(R"(([^|]+)\|([^|]+)\|([^|]+)\|([^|]+)\|([^|]+))");
        std::smatch match;
        if (std::regex_match(info, match, re)) {
            string userName = match[1];
            string email = match[2];
            string fullName = match[3];
            string phone = match[4];
            string password = match[5];

            return std::make_shared<Customer>(
                userName, fullName, email, phone, password
            );
        }
        return std::make_shared<Customer>();
    }
};

#endif