#ifndef _FILE_UTILS_H_
#define _FILE_UTILS_H_

#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
using std::ifstream, std::ofstream;
using std::string;
using std::vector;

class FileUtils {
public:
    static vector<string> readLines(const string& path) {
        vector<string> lines;
        ifstream in(path);

        //if (!in.is_open()) continue;

        string s;

        while (getline(in, s)) lines.push_back(s);

        // in.close()
        return lines;
    }

    static void writeText(const string& path, const string& content) {
        ofstream out(path);
        out << content;
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