#include "ConsoleUI.h"

void ConsoleUI::intro(string message) {
    cout << message << "\n\n";
}

void ConsoleUI::outro() {
    cout << "\nChương trình đang kết thúc. Nhấn Enter để thoát...";
    cin.get();
}

string ConsoleUI::inputString(const string& label) {
    cout << label;
    string s;
    getline(cin, s);
    return s;
}

void ConsoleUI::print(const string& message) {
    cout << format("{}\n", message);
}

void ConsoleUI::showMessage(const string& msg) {
    cout << msg << "\n";
}

void ConsoleUI::showError(const string& err) {
    cout << "[ERROR] " << err << "\n";
}

void ConsoleUI::waitEnter() {
    cout << "Press ENTER to continue...";
    cin.ignore();
}