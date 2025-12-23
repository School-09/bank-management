#ifndef _OPTIONENUM_H_
#define _OPTIONENUM_H_

enum class AuthMenuOption{
    REGISTER = 1,
    LOGIN = 2,
    RESET_PASSWORD = 3,
    EXIT = 0
};

enum class UserMenuOption{
    CREATE_ACCOUNT = 1,
    LIST_ACCOUNTS = 2,
    CLOSE_ACCOUNT = 3,
    LOGOUT = 4,
    BACK = 0
};

enum class ResetPasswordOption{
    ENTER_RESET_TOKEN = 1,
    BACK = 0
};

#endif