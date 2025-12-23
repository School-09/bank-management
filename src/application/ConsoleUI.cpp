#include "ConsoleUI.h"

string ConsoleUI::inputString(const string& label) {
    cout << label;
    string s;
    getline(cin, s);
    return s;
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