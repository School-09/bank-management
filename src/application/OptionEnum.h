#ifndef _OPTIONENUM_H_
#define _OPTIONENUM_H_

enum class AuthMenuOption{
    REGISTER = 1,
    LOGIN = 2,
    RESET_PASSWORD = 3,
    EXIT = 0
};

enum class ResetPasswordMenuOption{
    ENTER_RESET_TOKEN = 1,
    BACK = 0
};

enum class UserMenuOption{
    ACCOUNT_MANAGE = 1,
    TRANSACTION_MANAGE = 2,
    CARD_MANAGE = 3,
    LOGOUT = 4,
    BACK = 0
};

enum class AccountMenuOption{
    CREATE_ACCOUNT = 1,
    LIST_ACCOUNTS = 2,
    CLOSE_ACCOUNT = 3,
    LOGOUT = 4,
    BACK = 0
};

enum class TransactionMenuOption{
    DEPOSIT = 1,
    WITHDRAW = 2,
    TRANSFER = 3,
    LOGOUT = 4,
    BACK = 0
};

enum class CardMenuOption{
    CREATE_CARD = 1,
    LIST_CARDS = 2,
    CLOSE_CARD = 3,
    LOGOUT = 4,
    BACK = 0
};

#endif