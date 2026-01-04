#ifndef _CONSOLE_UI_H_
#define _CONSOLE_UI_H_

#include <iostream>
#include <string>
#include <vector>
#include <format>
using std::cin, std::cout;
using std::string;
using std::vector;
using std::format;

class ConsoleUI {
public:
    static void intro();
    static void outro();

    static string inputString(const string& label);
    static vector<string> inputLists(const vector<string>& infos);

    static void printNotice(const string& message);
    static void printError(const string& err);
    
    static void waitEnter();
};

#endif