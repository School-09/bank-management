#ifndef _MENU_PRINTER_H_
#define _MENU_PRINTER_H_

#include <iostream>
using std::cout;

class MenuPrinter {
public:
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