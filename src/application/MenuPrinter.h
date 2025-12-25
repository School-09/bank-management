#ifndef _MENUPRINTER_H_
#define _MENUPRINTER_H_

#include <iostream>
using std::cout;

class MenuPrinter {
public:
    static void printAuthMenu();
    static void printResetPasswordStep2();

    static void printUserMenu();
    static void printAccountMenu();
    static void printTransactionMenu();
    static void printCardMenu();
    static void printAdminMenu();
};


#endif