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

        if (!in.is_open()) {
            throw std::runtime_error("Không thể mở file: " + path); //TODO: throw
        }

        string s;
        while (getline(in, s)) {
            lines.push_back(s);
        }

        return lines;
    }

    static void writeText(const string& path, const string& content) {
        ofstream out(path);
        out << content;
    }
};

#endif