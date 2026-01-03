#ifndef _STRING_UTILS_H_
#define _STRING_UTILS_H_

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
using std::string;

class StringUtils {
public:
    static string normalizeString(const string& input) {
        string result = input;
        std::transform(result.begin(), result.end(), result.begin(),
                    [](unsigned char c){ return std::tolower(c); });
        return result;
    }
    // Ghép vector các input thành 1 chuỗi ngăn cách bởi delimiter
    static std::string join(const std::vector<std::string>& inputs, const std::string& delimiter = "|") {
        std::ostringstream oss;
        for (size_t i = 0; i < inputs.size(); ++i) {
            oss << inputs[i];
            if (i != inputs.size() - 1) {
                oss << delimiter;
            }
        }
        return oss.str();
    }
};

#endif