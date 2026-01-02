#ifndef _I_USER_MENU_H_
#define _I_USER_MENU_H_

class IUserMenu {
public:
    virtual ~IUserMenu() = default;
    virtual void run() = 0;
};

#endif