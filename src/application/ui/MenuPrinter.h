#ifndef _MENU_PRINTER_H_
#define _MENU_PRINTER_H_

#include <string>
#include <vector>
using std::string;
using std::vector;

struct MenuItem {
    string key;
    string label;
};

class MenuPrinter {
public:    
    static void printMenu(
        const string& title, const vector<MenuItem>& items
    );

    static void printAuthMenu();
    static void printResetPasswordStep2();

    static void printAdminMenu();
    static void printAdminAccountMenu();
    static void printAdminCardMenu();

    static void printCustomerMenu();
    static void printCustomerAccountMenu();
    static void printCustomerTransactionMenu();
    static void printCustomerCardMenu();
};


#endif