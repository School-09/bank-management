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

    // Hàm hỗ trợ để cắt Key và Value
    static bool extract_key_value(const string& line, string& key, string& val) {
        auto pos = line.find(":");
        if (pos == string::npos) return false;
        
        // Cắt Key (bỏ các khoảng trắng nếu có)
        key = line.substr(0, pos);
        // Cắt Value (bắt đầu từ pos + 2 để bỏ ": ")
        val = line.substr(pos + 2); 
        
        // Xóa khoảng trắng thừa (trim) cho key và value nếu cần, nhưng tạm thời bỏ qua để giữ đơn giản
        return true;
    }
};

#endif