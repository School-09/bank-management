#include "ConsoleUI.h"

void ConsoleUI::intro() {
    cout << "\n";
    cout << "=====================================================\n";
    cout << "            WELCOME TO BANKING CORE SYSTEM\n";
    cout << "=====================================================\n";
    cout << "This application simulates core banking operations:\n";
    cout << " - User authentication (Admin / Customer)\n";
    cout << " - Account and Card management\n";
    cout << " - Secure transactions and payments\n";
    cout << "\n";
}

void ConsoleUI::outro() {
    cout << "\nChương trình đang kết thúc. Nhấn Enter để thoát...";
    cin.get();
    cout << "\n=== EXIT PROGRAM ===\n";
}

string ConsoleUI::inputString(const string& label) {
    cout << format("Enter {}: ", label);
    string s;
    getline(cin, s);
    return s;
}

vector<string> ConsoleUI::inputLists(const vector<string>& infos) {
    vector<string> results;
    for (auto info : infos) {
        cout << format("Enter {}: ", info);
        string s;
        getline(cin, s);
        results.push_back(s);
    }
    return results;
}

void ConsoleUI::printNotice(const string& message) {
    cout << format("[Notice] {}\n", message);
}

void ConsoleUI::printError(const string& err) {
    cout << format("[Error] {}\n", err);
}

void ConsoleUI::waitEnter() {
    cout << "Press ENTER to continue...";
    cin.ignore();
}