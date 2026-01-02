#ifndef _STRING_UTILS_H_
#define _STRING_UTILS_H_

#include <iostream>
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
};

#endif