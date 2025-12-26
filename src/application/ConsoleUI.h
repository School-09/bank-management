#ifndef _CONSOLEUI_H_
#define _CONSOLEUI_H_

#include <iostream>
#include <string>
#include <format>
using std::cin, std::cout;
using std::string;
using std::format;

class ConsoleUI {
public:
    static string inputString(const string& label);
    static void print(const string& message);
    static void showMessage(const string& msg);
    static void showError(const string& err);
    static void waitEnter();
};

#endif