#ifndef _CONSOLEUI_H_
#define _CONSOLEUI_H_

#include <iostream>
#include <string>
using std::cin, std::cout;
using std::string;

class ConsoleUI {
public:
    static string inputString(const string& label);
    static void showMessage(const string& msg);
    static void showError(const string& err);
    static void waitEnter();
};

#endif